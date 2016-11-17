#include "Juego.h"

Juego::Juego(){

}

Juego::~Juego(){

}

void Juego::crearJuego(Mapa m){
    this->mapaJuego = m;
    this->cantidadFilas = m.maximaLatitud();
    this->cantidadColumnas = m.maximaLongitud();
    aed2::Arreglo<Juego::JugadorPokemonEnMapa> mapaJugadoresPokemons;
    this->jugadoresPokemonsMapa = mapaJugadoresPokemons;
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
        Juego::JugadorPokemonEnMapa* datos = new Juego::JugadorPokemonEnMapa(NULL, &datosPoke );
        this->jugadoresPokemonsMapa.Definir(e, *datos);
    }
    this->posicionesPokemons.AgregarRapido(c);
    this->cantidadTotalPokemons ++;
}

void Juego::agregarJugador(){
    aed2::Nat id = this->jugadoresVector.Longitud();
    aed2::Conj<aed2::Nat>::Iterador itReferencia = this->jugadoresConjunto.AgregarRapido(id);
    Juego::DatosJugador datosJ = Juego::DatosJugador(id,itReferencia);
    this->jugadoresVector.AgregarAtras(datosJ);
}

void Juego::conectarse(Jugador j, Coordenada c){
    this->jugadoresVector[j].conectado = true;
}

void Juego::desconectarse(Jugador j){
    this->jugadoresVector[j].conectado = false;
}

void Juego::moverse(Jugador j, Coordenada c){

}

Mapa Juego::mapa(){
    return this->mapaJuego;
}

aed2::Conj<Jugador>::Iterador Juego::jugadores(){
    aed2::Conj<Jugador>::Iterador res = this->jugadoresConjunto.CrearIt();
    return res;
}

bool Juego::estaConectado(Jugador j){
    return this->jugadoresVector[j].conectado;
}

aed2::Nat Juego::sanciones(Jugador j){
    return this->jugadoresVector[j].sanciones;
}

Coordenada Juego::posicion(Jugador j){
    return this->jugadoresVector[j].posicion;
}

DiccString<aed2::Nat>::Iterador Juego::pokemons(Jugador j){
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

}

bool Juego::puedoAgregarPokemon(Coordenada c){

}

bool Juego::hayPokemonCercano(Coordenada c){

}

Coordenada Juego::posPokemonCercano(Coordenada c){

}

aed2::Conj<Jugador> Juego::entrenadoresPosibles(Coordenada c, aed2::Conj<Jugador> cj){

}

aed2::Nat Juego::indiceRareza(Pokemon p){

}

aed2::Nat Juego::cantPokemonsTotales(){

}

aed2::Nat Juego::cantMismaEspecie(Pokemon p){

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
