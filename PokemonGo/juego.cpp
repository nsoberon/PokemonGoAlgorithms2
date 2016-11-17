#include "Juego.h"

Juego::Juego(){

}

Juego::~Juego(){

}

void Juego::crearJuego(Mapa m){
    this->mapaJuego = m;
    this->cantidadFilas = m.maximaLatitud();
    this->cantidadColumnas = m.maximaLongitud();
    aed2::Arreglo<Juego::JugadorPokemonEnMapa>* mapaJugadoresPokemons = new aed2::Arreglo<Juego::JugadorPokemonEnMapa>((this->cantidadFilas + 1) * (this->cantidadColumnas + 1));
    this->jugadoresPokemonsMapa = *mapaJugadoresPokemons;
    aed2::Vector<Juego::DatosJugador> jugVec;
    this->jugadoresVector = jugVec;
    aed2::Conj<aed2::Nat> jugConj;
    this->jugadoresConjunto = jugConj;
    aed2::Conj<Coordenada> posPoke;
    this->posicionesPokemons = posPoke;
    DiccString<aed2::Nat> pokeCant;
    this->pokemonsCantidades = pokeCant;
    aed2::Lista<Juego::DatosPokemonSalvaje> pokeSalv;
    this->pokemonsSalvajes = pokeSalv;
    this->cantidadTotalPokemons = 0;
}

void Juego::agregarPokemon(Pokemon p, Coordenada c){
    assert(this->puedoAgregarPokemon(c));
    aed2::Nat valor = 0;
    if(this->pokemonsCantidades.Definido(p)){
        valor = this->pokemonsCantidades.Obtener(p);
    }
    this->pokemonsCantidades.Definir(p, valor + 1);
    aed2::Lista<Juego::DatosJugador> jugadoresCercanos = this->jugadoresADistancia(2,c);
    aed2::Lista<Juego::DatosJugador>::Iterador itCercanos = jugadoresCercanos.CrearIt();
    ColaPrior<Juego::JugadorEsperando> heapEsperandoCaptura;
    heapEsperandoCaptura.Vacia();
    while(itCercanos.HaySiguiente()){
        Juego::DatosJugador jug = itCercanos.Siguiente();
        Juego::JugadorEsperando jugEsp;
        jugEsp.crearJugadorEsperando(jug.id, jug.cantidadPokemonsAtrapados);
        heapEsperandoCaptura.Encolar(jugEsp);
        itCercanos.Avanzar();
    }
    Juego::DatosPokemonSalvaje datosPoke;
    datosPoke.crearDatosPokeSalv(p, c, heapEsperandoCaptura);
    this->pokemonsSalvajes.AgregarAtras(datosPoke);
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].pokemon = &datosPoke;
    }else{
        Juego::JugadorPokemonEnMapa datos;
        datos.crearJugadorEnMapa(NULL, &datosPoke);
        this->jugadoresPokemonsMapa.Definir(e, datos);
    }
    this->posicionesPokemons.AgregarRapido(c);
    this->cantidadTotalPokemons ++;
}

void Juego::agregarJugador(){
    aed2::Nat id = this->jugadoresVector.Longitud();
    aed2::Conj<aed2::Nat>::Iterador itReferencia = this->jugadoresConjunto.AgregarRapido(id);
    Juego::DatosJugador datosJ;
    datosJ.crearDatosJugador(id, itReferencia);
    this->jugadoresVector.AgregarAtras(datosJ);
}

void Juego::conectarse(Jugador j, Coordenada c){
    assert(this->jugadoresConjunto.Pertenece(j) && !this->estaConectado(j) && this->mapa().posExistente(c));
    Juego::DatosJugador jug = this->jugadoresVector[j];
    this->jugadoresVector[j].posicion = c;
    this->jugadoresVector[j].conectado= true;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].jugador = &this->jugadoresVector[j];
    }else{
        Juego::JugadorPokemonEnMapa nuevoJug;
        nuevoJug.crearJugadorEnMapa(&this->jugadoresVector[j], NULL);
        this->jugadoresPokemonsMapa.Definir(e, nuevoJug);
    }
    if(this->hayPokemonCercano(c)){
        Juego::DatosPokemonSalvaje poke = this->pokemonsADistancia(2,c).Primero();
        poke.cantidadMovimientos = 0;
        Juego::JugadorEsperando jugN;
        jugN.crearJugadorEsperando(jug.id, jug.cantidadPokemonsAtrapados);
        ColaPrior<Juego::JugadorEsperando>::Iterador itEsperando = poke.jugadoresEsperando.Encolar(jugN);
        jug.esperandoParaCapturar = itEsperando;
    }
}

void Juego::desconectarse(Jugador j){
    assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    this->jugadoresVector[j].conectado = false;
    Coordenada c = this->jugadoresVector[j].posicion;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        if(this->jugadoresPokemonsMapa[e].jugador->esperandoParaCapturar.HaySiguiente()){
            //this->jugadoresPokemonsMapa[e].jugador->esperandoParaCapturar.EliminarSiguiente();
        }
        Juego::JugadorPokemonEnMapa nuevoJug;
        nuevoJug.crearJugadorEnMapa(NULL, this->jugadoresPokemonsMapa[e].pokemon);
        this->jugadoresPokemonsMapa.Definir(e, nuevoJug);
    }
}

void Juego::moverse(Jugador j, Coordenada c){
    assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j) && this->mapa().coordenadas().Pertenece(c));
    Coordenada posicionActual = this->jugadoresVector[j].posicion;
    if((!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) >= 100) && this->jugadoresVector[j].sanciones == 4){
        this->jugadoresVector[j].banneado = true;
        this->jugadoresVector[j].referenciaConjunto.EliminarSiguiente();
        DiccString<aed2::Nat>::Iterador pokemonsAtrapadosDe;
        pokemonsAtrapadosDe.crearIt(this->jugadoresVector[j].pokemonsCapturados);
        while(pokemonsAtrapadosDe.haySiguiente()){
            //aed2::Nat cantidad = this->pokemonsCantidades.Obtener(pokemonsAtrapadosDe.siguiente());
            //this->pokemonsCantidades.Definir(pokemonsAtrapadosDe.siguiente(), cantidad - 1);
            pokemonsAtrapadosDe.avanzar();
        }
    }else if(!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) <= 100){
        this->jugadoresVector[j].sanciones ++;
    }
    this->jugadoresVector[j].posicion = c;
    //VOY PR LA LINEA 14


}

Mapa Juego::mapa(){
    return this->mapaJuego;
}

aed2::Conj<Jugador>::Iterador Juego::jugadores(){
    aed2::Conj<Jugador>::Iterador res = this->jugadoresConjunto.CrearIt();
    return res;
}

bool Juego::estaConectado(Jugador j){
    assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].conectado;
}

aed2::Nat Juego::sanciones(Jugador j){
    assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].sanciones;
}

Coordenada Juego::posicion(Jugador j){
    assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    return this->jugadoresVector[j].posicion;
}

DiccString<aed2::Nat>::Iterador Juego::pokemons(Jugador j){
    assert(this->jugadoresConjunto.Pertenece(j));
    DiccString<aed2::Nat>::Iterador itPoke;
    itPoke.crearIt(this->jugadoresVector[j].pokemonsCapturados);
    return itPoke;
}

aed2::Conj<Jugador> Juego::expulsados(){
    aed2::Conj<Jugador> exp;
    for(int i = 0; i < this->jugadoresVector.Longitud(); i++){
        if(this->jugadoresVector[i].banneado){
            exp.AgregarRapido(i);
        }
    }
    return exp;
}

aed2::Conj<Coordenada> Juego::posConPokemons(){

    return this->posicionesPokemons;
}

Pokemon Juego::pokemonsEnPos(Coordenada c){
    assert(this->posicionesPokemons.Pertenece(c));
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    return this->jugadoresPokemonsMapa[e].pokemon->pokemon;
}

aed2::Nat Juego::cantidadMovimientosParaCapturar(Coordenada c){
    assert(this->posicionesPokemons.Pertenece(c));
    if(this->hayPokemonCercano(c)){
        Coordenada posPokeCercano = this->posPokemonCercano(c);
        aed2::Nat lat = posPokeCercano.latitud();
        aed2::Nat lon = posPokeCercano.longitud();
        aed2::Nat e = lat * this->cantidadColumnas + lon;
        return this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos;
    }

}

bool Juego::puedoAgregarPokemon(Coordenada c){
    return this->mapa().posExistente(c) && !this->hayPokemonCercano(c);
}

bool Juego::hayPokemonCercano(Coordenada c){
    return this->pokemonsADistancia(4,c).Longitud() > 0;
}

Coordenada Juego::posPokemonCercano(Coordenada c){
    assert(this->hayPokemonCercano(c));
    return this->pokemonsADistancia(4, c).Primero().posicion;
}

aed2::Conj<Jugador> Juego::entrenadoresPosibles(Coordenada c, aed2::Conj<Jugador> cj){
    assert(this->hayPokemonCercano(c)); // falta agregar que cj esta incluido en los jugadores conectados
    aed2::Conj<Jugador> res;
    Coordenada pos = this->posPokemonCercano(c);
    aed2::Nat posPoke = pos.latitud() * this->cantidadColumnas + pos.longitud();
    ColaPrior<Juego::JugadorEsperando> jugEsp = this->jugadoresPokemonsMapa[posPoke].pokemon->jugadoresEsperando;
    ColaPrior<Juego::JugadorEsperando>::Iterador itJug;
    // itJug.CrearIterador(jugEsp);
    // FALTA HACER SIGUIENTE Y AVANZAR DEL ITERADOR DE COLA DE PRIORIDAD
    // VER BIEN ESTA FUNCION
}

aed2::Nat Juego::indiceRareza(Pokemon p){
    assert(this->pokemonsCantidades.Definido(p));
    return 100 - (100 * this->cantMismaEspecie(p) / this->cantPokemonsTotales());
}

aed2::Nat Juego::cantPokemonsTotales(){
    return this->cantidadTotalPokemons;
}

aed2::Nat Juego::cantMismaEspecie(Pokemon p){
    return this->pokemonsCantidades.Obtener(p);
}

aed2::Lista<Juego::DatosJugador> Juego::jugadoresADistancia(aed2::Nat d, Coordenada c){
    aed2::Lista<Juego::DatosJugador> res;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat desdeFila;
    aed2::Nat desdeCol;
    aed2::Nat hastaFila;
    aed2::Nat hastaCol;
    if(lat < d){
        desdeFila = 0;
    }else{
        desdeFila = lat - d;
    }
    if(lon < d){
        desdeCol = 0;
    }else{
        desdeCol = lon-d;
    }
    if(lat + d > this->cantidadFilas){
        hastaFila = this->cantidadFilas - 1;
    }else{
        hastaFila = lat + d;
    }
    if(lon + d > this->cantidadColumnas){
        hastaCol = this->cantidadColumnas - 1;
    }else{
        hastaCol = lon + d;
    }
    Coordenada coorOrigen;
    coorOrigen.crearCoor(lat, lon);
    while(desdeFila <= hastaFila){
        while(desdeCol <= hastaCol){
            Coordenada coorDestino;
            coorDestino.crearCoor(desdeFila, desdeCol);
            if(coorOrigen.distEuclidea(coorDestino) <= d*d){
                aed2::Nat e = desdeFila * this->cantidadColumnas + desdeCol;
                if(this->jugadoresPokemonsMapa.Definido(e) && this->jugadoresPokemonsMapa[e].jugador != NULL){
                    res.AgregarAtras(*this->jugadoresPokemonsMapa[e].jugador);
                }
            }
            desdeCol ++;
        }
        desdeFila ++;
    }
    return res;
}

aed2::Lista<Juego::DatosPokemonSalvaje> Juego::pokemonsADistancia(aed2::Nat d, Coordenada c){
    aed2::Lista<Juego::DatosPokemonSalvaje> res;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat desdeFila;
    aed2::Nat desdeCol;
    aed2::Nat hastaFila;
    aed2::Nat hastaCol;
    if(lat < d){
        desdeFila = 0;
    }else{
        desdeFila = lat - d;
    }
    if(lon < d){
        desdeCol = 0;
    }else{
        desdeCol = lon-d;
    }
    if(lat + d > this->cantidadFilas){
        hastaFila = this->cantidadFilas - 1;
    }else{
        hastaFila = lat + d;
    }
    if(lon + d > this->cantidadColumnas){
        hastaCol = this->cantidadColumnas - 1;
    }else{
        hastaCol = lon + d;
    }
    Coordenada coorOrigen;
    coorOrigen.crearCoor(lat, lon);
    while(desdeFila <= hastaFila){
        while(desdeCol <= hastaCol){
            Coordenada coorDestino;
            coorDestino.crearCoor(desdeFila, desdeCol);
            if(coorOrigen.distEuclidea(coorDestino) <= d*d){
                aed2::Nat e = desdeFila * this->cantidadColumnas + desdeCol;
                if(this->jugadoresPokemonsMapa.Definido(e) && this->jugadoresPokemonsMapa[e].pokemon != NULL){
                    res.AgregarAtras(*this->jugadoresPokemonsMapa[e].pokemon);
                }
            }
            desdeCol ++;
        }
        desdeFila ++;
    }
    return res;
}

aed2::Conj<Jugador> Juego::expulsadosAux(aed2::Vector<Juego::DatosJugador> j){
    aed2::Conj<Jugador> res;
    aed2::Nat i = 0;
    while(i < j.Longitud()){
        if(j[i].banneado){
            res.AgregarRapido(i);
        }
        i ++;
    }
    return res;
}

aed2::Conj<Jugador> Juego::jugadoresAux(aed2::Vector<Juego::DatosJugador> j){
    aed2::Conj<Jugador> res;
    aed2::Nat i = 0;
    while(i < j.Longitud()){
        if(!j[i].banneado){
            res.AgregarRapido(i);
        }
        i ++;
    }
    return res;
}
