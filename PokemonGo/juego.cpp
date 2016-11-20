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
        Juego::JugadorEsperando* jugEsp = new Juego::JugadorEsperando(jug.id, jug.cantidadPokemonsAtrapados);
        heapEsperandoCaptura.Encolar(*jugEsp);
        itCercanos.Avanzar();
    }
    Juego::DatosPokemonSalvaje* datosPoke = new Juego::DatosPokemonSalvaje(p, c, heapEsperandoCaptura);
    this->pokemonsSalvajes.AgregarAtras(*datosPoke);
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].pokemon = datosPoke;
    }else{
        Juego::JugadorPokemonEnMapa* datos = new Juego::JugadorPokemonEnMapa(NULL, datosPoke);
        this->jugadoresPokemonsMapa.Definir(e, *datos);
    }
    this->posicionesPokemons.AgregarRapido(c);
    this->cantidadTotalPokemons ++;
}

aed2::Nat Juego::agregarJugador(){
    aed2::Nat id = this->jugadoresVector.Longitud();
    aed2::Conj<aed2::Nat>::Iterador itReferencia = this->jugadoresConjunto.AgregarRapido(id);
    Juego::DatosJugador* datosJ = new Juego::DatosJugador(id, itReferencia);
    this->jugadoresVector.AgregarAtras(*datosJ);
    return id;
}

void Juego::conectarse(Jugador j, Coordenada c){
    assert(this->jugadoresConjunto.Pertenece(j) && !this->estaConectado(j) && this->mapa().posExistente(c));
    this->jugadoresVector[j].posicion = c;
    this->jugadoresVector[j].conectado= true;
    Juego::DatosJugador jug = this->jugadoresVector[j];
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].jugador = &this->jugadoresVector[j];
    }else{
        Juego::JugadorPokemonEnMapa* nuevoJug = new Juego::JugadorPokemonEnMapa(&this->jugadoresVector[j], NULL);
        this->jugadoresPokemonsMapa.Definir(e, *nuevoJug);
    }
    if(this->hayPokemonCercano(c)){
        Coordenada posPoke = this->pokemonsADistancia(2,c).Primero();
        aed2::Nat latP = posPoke.latitud();
        aed2::Nat lonP = posPoke.longitud();
        aed2::Nat eP = latP * this->cantidadColumnas + lonP;
        Juego::JugadorPokemonEnMapa nico = this->jugadoresPokemonsMapa[eP];
        this->jugadoresPokemonsMapa[eP].pokemon->cantidadMovimientos = 0;
        Juego::JugadorEsperando* jugN = new Juego::JugadorEsperando(jug.id, jug.cantidadPokemonsAtrapados);
        ColaPrior<Juego::JugadorEsperando>::Iterador itEsperando = this->jugadoresPokemonsMapa[eP].pokemon->jugadoresEsperando.Encolar(*jugN);
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
            this->jugadoresPokemonsMapa[e].jugador->esperandoParaCapturar.EliminarSiguiente();
        }
        Juego::JugadorPokemonEnMapa* nuevoJug = new Juego::JugadorPokemonEnMapa(NULL, this->jugadoresPokemonsMapa[e].pokemon);
        this->jugadoresPokemonsMapa.Definir(e, *nuevoJug);
    }
}

void Juego::moverse(Jugador j, Coordenada c){
    assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j) && this->mapa().coordenadas().Pertenece(c));
    Coordenada posicionActual = this->jugadoresVector[j].posicion;
    Coordenada posicionNueva = c;
    if((!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) >= 100) && this->jugadoresVector[j].sanciones == 4){
        this->jugadoresVector[j].banneado = true;
        this->jugadoresVector[j].referenciaConjunto.EliminarSiguiente();
        DiccString<aed2::Nat>::Iterador pokemonsAtrapadosDe = this->jugadoresVector[j].pokemonsCapturados.CrearIt();
        while(pokemonsAtrapadosDe.HaySiguiente()){
            aed2::Nat cantidad = this->pokemonsCantidades.Obtener(pokemonsAtrapadosDe.Siguiente().clave);
            this->pokemonsCantidades.Definir(pokemonsAtrapadosDe.Siguiente().clave, cantidad - 1);
            pokemonsAtrapadosDe.Avanzar();
        }
    }else if(!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) <= 100){
        this->jugadoresVector[j].sanciones ++;
    }
    this->jugadoresVector[j].posicion = c;
    if(this->hayPokemonCercano(posicionActual)){
        Coordenada pokemonCercanoPosicionActual = this->posPokemonCercano(posicionActual);
        if(this->hayPokemonCercano(posicionNueva)){
            Coordenada pokemonCercanoPosicionNueva= this->posPokemonCercano(posicionNueva);
            if(pokemonCercanoPosicionActual != pokemonCercanoPosicionNueva){
                aed2::Nat lat = pokemonCercanoPosicionNueva.latitud();
                aed2::Nat lon = pokemonCercanoPosicionNueva.longitud();
                aed2::Nat e = lat * this->cantidadColumnas + lon;
                this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos = 0;
                ColaPrior<Juego::JugadorEsperando>::Iterador itJugadorABorrar = this->jugadoresVector[j].esperandoParaCapturar;
                itJugadorABorrar.EliminarSiguiente();
                Juego::JugadorEsperando* jugNuevo = new Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
                this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(*jugNuevo);
                aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                while(itPosPoke.HaySiguiente()){
                    if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                        itPosPoke.Siguiente().cantidadMovimientos ++;
                        itPosPoke.Avanzar();
                    }
                }
            }
            }else{
            ColaPrior<Juego::JugadorEsperando>::Iterador itJugadorABorrar = this->jugadoresVector[j].esperandoParaCapturar;
            itJugadorABorrar.EliminarSiguiente();
            aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
            while(itPosPoke.HaySiguiente()){
                itPosPoke.Siguiente().cantidadMovimientos ++;
                itPosPoke.Avanzar();
            }
        }
    }else if(this->hayPokemonCercano(posicionNueva)){
        Coordenada pokemonCercanoPosicionNueva= this->posPokemonCercano(posicionNueva);
        aed2::Nat lat = pokemonCercanoPosicionNueva.latitud();
        aed2::Nat lon = pokemonCercanoPosicionNueva.longitud();
        aed2::Nat e = lat * this->cantidadColumnas + lon;
        this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos = 0;
        aed2::Conj<aed2::Nat>::Iterador itJugadorABorrar = this->jugadoresVector[j].referenciaConjunto;
        itJugadorABorrar.EliminarSiguiente();
        Juego::JugadorEsperando* jugNuevo = new Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
        this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(*jugNuevo);
        aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
        while(itPosPoke.HaySiguiente()){
            if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                itPosPoke.Siguiente().cantidadMovimientos ++;
                itPosPoke.Avanzar();
            }
        }
    }else{
        aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
        while(itPosPoke.HaySiguiente()){
                itPosPoke.Siguiente().cantidadMovimientos ++;
                itPosPoke.Avanzar();
        }
    }
    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
    while(itPosPoke.HaySiguiente()){
            if(itPosPoke.Siguiente().cantidadMovimientos >= 10){
                Jugador jug = itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador;
                if(this->jugadoresVector[jug].pokemonsCapturados.Definido(itPosPoke.Siguiente().pokemon)){
                    aed2::Nat cant = this->jugadoresVector[jug].pokemonsCapturados.Obtener(itPosPoke.Siguiente().pokemon);
                    this->jugadoresVector[jug].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, cant + 1);
                }else{
                    this->jugadoresVector[jug].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, 1);
                }
                this->jugadoresVector[jug].cantidadPokemonsAtrapados ++;
                itPosPoke.EliminarSiguiente();
                Coordenada pokemonABorrarMapa = this->posPokemonCercano(this->jugadoresVector[jug].posicion);
                aed2::Nat lat = pokemonABorrarMapa.latitud();
                aed2::Nat lon = pokemonABorrarMapa.longitud();
                aed2::Nat e = lat * this->cantidadColumnas + lon;
                this->jugadoresPokemonsMapa[e].pokemon = NULL;
            }
            itPosPoke.Avanzar();
    }



}

Mapa Juego::mapa() const{
    return this->mapaJuego;
}

aed2::Conj<Jugador>::const_Iterador Juego::jugadores() const{
    aed2::Conj<Jugador>::const_Iterador res = this->jugadoresConjunto.CrearIt();
    return res;
}

bool Juego::estaConectado(Jugador j) const{
    assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].conectado;
}

aed2::Nat Juego::sanciones(Jugador j) const{
    assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].sanciones;
}

Coordenada Juego::posicion(Jugador j) const{
    assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    return this->jugadoresVector[j].posicion;
}

DiccString<aed2::Nat>::const_Iterador Juego::pokemons(Jugador j) const{
    assert(this->jugadoresConjunto.Pertenece(j));
    DiccString<aed2::Nat>::const_Iterador itPoke = this->jugadoresVector[j].pokemonsCapturados.CrearIt();
    return itPoke;
}

aed2::Conj<Jugador> Juego::expulsados() const{
    aed2::Conj<Jugador> exp;
    for(int i = 0; i < this->jugadoresVector.Longitud(); i++){
        if(this->jugadoresVector[i].banneado){
            exp.AgregarRapido(i);
        }
    }
    return exp;
}

aed2::Conj<Coordenada> Juego::posConPokemons() const{
    return this->posicionesPokemons;
}

Pokemon Juego::pokemonsEnPos(Coordenada c) const{
    assert(this->posicionesPokemons.Pertenece(c));
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    return this->jugadoresPokemonsMapa[e].pokemon->pokemon;
}

aed2::Nat Juego::cantidadMovimientosParaCapturar(Coordenada c) const{
    assert(this->posicionesPokemons.Pertenece(c));
    if(this->hayPokemonCercano(c)){
        Coordenada posPokeCercano = this->posPokemonCercano(c);
        aed2::Nat lat = posPokeCercano.latitud();
        aed2::Nat lon = posPokeCercano.longitud();
        aed2::Nat e = lat * this->cantidadColumnas + lon;
        return this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos;
    }

}

bool Juego::puedoAgregarPokemon(Coordenada c) const{
    return this->mapa().posExistente(c) && !this->hayPokemonCercano(c);
}

bool Juego::hayPokemonCercano(Coordenada c) const{
    bool res = this->pokemonsADistancia(4,c).Longitud() > 0;
    return res;
}

Coordenada Juego::posPokemonCercano(Coordenada c) const{
    assert(this->hayPokemonCercano(c));
    return this->pokemonsADistancia(4, c).Primero();
}

aed2::Conj<Jugador> Juego::entrenadoresPosibles(Coordenada c) const{
    assert(this->hayPokemonCercano(c));
    aed2::Conj<Jugador> res;
    Coordenada pos = this->posPokemonCercano(c);
    aed2::Nat posPoke = pos.latitud() * this->cantidadColumnas + pos.longitud();
    ColaPrior<Juego::JugadorEsperando> jugEsp = this->jugadoresPokemonsMapa[posPoke].pokemon->jugadoresEsperando;
    ColaPrior<Juego::JugadorEsperando>::const_Iterador itJugEsp = jugEsp.CrearIt();
    while(itJugEsp.HaySiguiente()){
        res.Agregar(itJugEsp.Siguiente().jugador);
        itJugEsp.Avanzar();
    }
    return res;
}

aed2::Nat Juego::indiceRareza(Pokemon p) const{
    assert(this->pokemonsCantidades.Definido(p));
    return 100 - (100 * this->cantMismaEspecie(p) / this->cantPokemonsTotales());
}

aed2::Nat Juego::cantPokemonsTotales() const{
    return this->cantidadTotalPokemons;
}

aed2::Nat Juego::cantMismaEspecie(Pokemon p) const{
    return this->pokemonsCantidades.Obtener(p);
}

aed2::Lista<Juego::DatosJugador> Juego::jugadoresADistancia(aed2::Nat d, Coordenada c) const{
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

aed2::Lista<Coordenada> Juego::pokemonsADistancia(aed2::Nat d, Coordenada c) const{
    aed2::Lista<Coordenada> res;
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
    aed2::Nat desdeColAnterior = desdeCol;
    Coordenada coorOrigen;
    coorOrigen.crearCoor(lat, lon);
    while(desdeFila <= hastaFila){
        while(desdeCol <= hastaCol){
            Coordenada coorDestino;
            coorDestino.crearCoor(desdeFila, desdeCol);
            if(coorOrigen.distEuclidea(coorDestino) <= d*d){
                aed2::Nat e = desdeFila * this->cantidadColumnas + desdeCol;
                if(this->jugadoresPokemonsMapa.Definido(e) && this->jugadoresPokemonsMapa[e].pokemon != NULL){
                    res.AgregarAtras(coorDestino);
                }
            }
            desdeCol ++;
        }
        desdeCol = desdeColAnterior;
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
