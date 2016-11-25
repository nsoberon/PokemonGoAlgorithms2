#include "Juego.h"

Juego::Juego(){

}

Juego::~Juego(){
    this->EliminarJuego();
}

void Juego::EliminarJuego(){

}

void Juego::crearJuego(Mapa m){
    this->mapaJuego = m;
    this->cantidadFilas = m.maximaLatitud() + 1;
    this->cantidadColumnas = m.maximaLongitud() + 1;
    this->jugadoresPokemonsMapa = aed2::Arreglo<Juego::JugadorPokemonEnMapa>((this->cantidadFilas + 1) * (this->cantidadColumnas + 1));
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
    //assert(this->puedoAgregarPokemon(c));
    aed2::Nat valor = 0;
    if(this->pokemonsCantidades.Definido(p)){
        valor = this->pokemonsCantidades.Obtener(p);
    }
    this->pokemonsCantidades.Definir(p, valor + 1);
    ColaPrior<Juego::JugadorEsperando> heapEsperandoCaptura = ColaPrior<Juego::JugadorEsperando>();
    heapEsperandoCaptura.Vacia();
    Juego::DatosPokemonSalvaje datosPoke = Juego::DatosPokemonSalvaje(p, c, heapEsperandoCaptura, this->posicionesPokemons.AgregarRapido(c));
    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador datosNuevos = this->pokemonsSalvajes.AgregarAtras(datosPoke);
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].pokemon = &datosNuevos.Siguiente();
        //this->jugadoresPokemonsMapa[e].pokemon = datosPoke;
    }else{
        //Juego::JugadorPokemonEnMapa* datos = new Juego::JugadorPokemonEnMapa(NULL, datosPoke);
        Juego::JugadorPokemonEnMapa datos = Juego::JugadorPokemonEnMapa(aed2::Conj<Juego::DatosJugador*>(), &datosNuevos.Siguiente());
        this->jugadoresPokemonsMapa.Definir(e, datos);
    }
    /* EL PROBLEMA ESTA ACA, CUANDO CREO LA LISTA ESA SE ME ROMPE TODO, ES COMO SI LA TRAE POR REFERENCIA
     * Y CUANDO LLAMA AL DESTRUCTOR Q SALE DE LA FUNCION, SE ME DESTRUYE EL DICCIONARIO QUE TIENE LOS POKEMONSD EL JUGADOR
     * POR OTRO LADO YA ESTA HECHA LA FUNCION CONS, PERO NO SE QUE ONDA
    */

    aed2::Lista<Juego::DatosJugador> jugadoresCercanos = this->jugadoresADistancia(2,c);
    aed2::Lista<Juego::DatosJugador>::const_Iterador itCercanos = jugadoresCercanos.CrearIt();
    while(itCercanos.HaySiguiente()){        
        Juego::JugadorEsperando jugEsp = Juego::JugadorEsperando(itCercanos.Siguiente().id, itCercanos.Siguiente().cantidadPokemonsAtrapados);
        this->jugadoresVector[itCercanos.Siguiente().id].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugEsp);
        itCercanos.Avanzar();     
    }
    this->cantidadTotalPokemons ++;
}

aed2::Nat Juego::agregarJugador(){
    aed2::Nat id = this->jugadoresVector.Longitud();
    aed2::Conj<aed2::Nat>::Iterador itReferencia = this->jugadoresConjunto.AgregarRapido(id);
    Juego::DatosJugador datosJ = Juego::DatosJugador(id, itReferencia);
    this->jugadoresVector.AgregarAtras(datosJ);
    return id;
}

void Juego::conectarse(Jugador j, Coordenada c){
    //assert(this->jugadoresConjunto.Pertenece(j) && !this->estaConectado(j) && this->mapa().posExistente(c));
    this->jugadoresVector[j].posicion = c;
    this->jugadoresVector[j].conectado= true;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[e].jugadores.AgregarRapido(&this->jugadoresVector[j]);
    }else{
        aed2::Conj<Juego::DatosJugador*> nuevoConj = aed2::Conj<Juego::DatosJugador*>();
        Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(nuevoConj, NULL);
        this->jugadoresPokemonsMapa.Definir(e, nuevoJug);
        this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[e].jugadores.AgregarRapido(&this->jugadoresVector[j]);

    }
    if(this->hayPokemonCercano(c)){
        Coordenada posPoke = this->posPokemonCercano(c);
        aed2::Nat latP = posPoke.latitud();
        aed2::Nat lonP = posPoke.longitud();
        aed2::Nat eP = latP * this->cantidadColumnas + lonP;
        this->jugadoresPokemonsMapa[eP].pokemon->cantidadMovimientos = 0;
        Juego::JugadorEsperando jugN = Juego::JugadorEsperando(this->jugadoresVector[j].id, this->jugadoresVector[j].cantidadPokemonsAtrapados);
        this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[eP].pokemon->jugadoresEsperando.Encolar(jugN);
    }
}

void Juego::desconectarse(Jugador j){
    //assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    this->jugadoresVector[j].conectado = false;
    Coordenada c = this->jugadoresVector[j].posicion;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        if(this->jugadoresVector[j].referenciaMapa.Siguiente()->esperandoParaCapturar.HaySiguiente()){
            this->jugadoresVector[j].referenciaMapa.Siguiente()->esperandoParaCapturar.EliminarSiguiente();
        }
        /*if(this->jugadoresPokemonsMapa[e].jugadores.esperandoParaCapturar.HaySiguiente()){
            this->jugadoresPokemonsMapa[e].jugadores.esperandoParaCapturar.EliminarSiguiente();
        }*/
        /*Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(NULL, this->jugadoresPokemonsMapa[e].pokemon);
        this->jugadoresPokemonsMapa.Definir(e, nuevoJug);*/
        this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
    }
}

void Juego::moverse(Jugador j, Coordenada c){
    //assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j) && this->mapa().coordenadas().Pertenece(c));
    Coordenada posicionActual = this->jugadoresVector[j].posicion;
    //aed2::Nat lat = posicionActual.latitud();
    //aed2::Nat lon = posicionActual.longitud();
    //aed2::Nat e = lat * this->cantidadColumnas + lon;
    Coordenada posicionNueva = c;
    if((!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) > 100) && this->jugadoresVector[j].sanciones >= 4){
        this->jugadoresVector[j].sanciones ++;
        this->jugadoresVector[j].banneado = true;
        this->jugadoresVector[j].referenciaConjunto.EliminarSiguiente();
        DiccString<aed2::Nat>::Iterador pokemonsAtrapadosDe = this->jugadoresVector[j].pokemonsCapturados.CrearIt();
        while(pokemonsAtrapadosDe.HaySiguiente()){
            aed2::Nat cantidad = this->pokemonsCantidades.Obtener(pokemonsAtrapadosDe.Siguiente().clave);
            this->pokemonsCantidades.Definir(pokemonsAtrapadosDe.Siguiente().clave, cantidad - pokemonsAtrapadosDe.Siguiente().significado);
            this->cantidadTotalPokemons = this->cantidadTotalPokemons - pokemonsAtrapadosDe.Siguiente().significado;
            //this->jugadoresVector[j].cantidadPokemonsAtrapados = this->jugadoresVector[j].cantidadPokemonsAtrapados - pokemonsAtrapadosDe.Siguiente().significado;
            pokemonsAtrapadosDe.Avanzar();
        }
        this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
        //this->jugadoresPokemonsMapa[e].jugador = NULL;
    }else if(!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) > 100){
        this->jugadoresVector[j].sanciones ++;
    }else{
        this->jugadoresVector[j].posicion = c;
        aed2::Nat latN = c.latitud();
        aed2::Nat lonN = c.longitud();
        aed2::Nat eN = latN * this->cantidadColumnas + lonN;
        if(this->jugadoresPokemonsMapa.Definido(eN)){
            this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
            this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[eN].jugadores.AgregarRapido(&this->jugadoresVector[j]);
            /*this->jugadoresPokemonsMapa[eN].jugador = this->jugadoresPokemonsMapa[e].jugador;
            this->jugadoresPokemonsMapa[e].jugador = NULL;*/
        }else{
            /*Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(this->jugadoresPokemonsMapa[e].jugador, NULL);
            this->jugadoresPokemonsMapa.Definir(eN, nuevoJug);
            this->jugadoresPokemonsMapa[e].jugador = NULL;*/
            Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(aed2::Conj<Juego::DatosJugador*>(), NULL);
            this->jugadoresPokemonsMapa.Definir(eN, nuevoJug);
            this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
            this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[eN].jugadores.AgregarRapido(&this->jugadoresVector[j]);
        }
        if(this->hayPokemonCercano(posicionActual)){
            Coordenada pokemonCercanoPosicionActual = this->posPokemonCercano(posicionActual);
            if(this->hayPokemonCercano(posicionNueva)){
                Coordenada pokemonCercanoPosicionNueva= this->posPokemonCercano(posicionNueva);
                if(pokemonCercanoPosicionActual != pokemonCercanoPosicionNueva){
                    aed2::Nat lat = pokemonCercanoPosicionNueva.latitud();
                    aed2::Nat lon = pokemonCercanoPosicionNueva.longitud();
                    aed2::Nat e = lat * this->cantidadColumnas + lon;
                    this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos = 0;
                    this->jugadoresVector[j].esperandoParaCapturar.EliminarSiguiente();
                    Juego::JugadorEsperando jugNuevo = Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
                    this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugNuevo);
                    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                    while(itPosPoke.HaySiguiente()){
                        if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                            itPosPoke.Siguiente().cantidadMovimientos ++;
                        }
                        itPosPoke.Avanzar();
                    }
                }else{
                    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                    while(itPosPoke.HaySiguiente()){
                        if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                            itPosPoke.Siguiente().cantidadMovimientos ++;
                        }
                        itPosPoke.Avanzar();
                    }
                }
            }else{
                this->jugadoresVector[j].esperandoParaCapturar.EliminarSiguiente();
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
            Juego::JugadorEsperando jugNuevo = Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
            this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugNuevo);
            aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
            while(itPosPoke.HaySiguiente()){
                if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                    itPosPoke.Siguiente().cantidadMovimientos ++;
                }
                itPosPoke.Avanzar();
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
                bool seAtrapo = false;
                if(itPosPoke.Siguiente().cantidadMovimientos >= 10 && itPosPoke.Siguiente().jugadoresEsperando.Tamanio() > 0){
                    if(this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definido(itPosPoke.Siguiente().pokemon)){
                        aed2::Nat cant = this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Obtener(itPosPoke.Siguiente().pokemon);
                        this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, cant + 1);
                    }else{
                        this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, 1);
                    }
                    this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].cantidadPokemonsAtrapados ++;
                    Coordenada pokemonABorrarMapa = this->posPokemonCercano(this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].posicion);
                    aed2::Nat lat = pokemonABorrarMapa.latitud();
                    aed2::Nat lon = pokemonABorrarMapa.longitud();
                    aed2::Nat e = lat * this->cantidadColumnas + lon;
                    this->jugadoresPokemonsMapa[e].pokemon->referenciaPosiciones.EliminarSiguiente();
                    this->jugadoresPokemonsMapa[e].pokemon = NULL;
                    itPosPoke.Avanzar();
                    itPosPoke.EliminarAnterior();
                    seAtrapo = true;
                }
                if(!seAtrapo){
                    itPosPoke.Avanzar();
                }
            }
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
    //assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].conectado;
}

aed2::Nat Juego::sanciones(Jugador j) const{
    //assert(this->jugadoresConjunto.Pertenece(j));
    return this->jugadoresVector[j].sanciones;
}

Coordenada Juego::posicion(Jugador j) const{
    //assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    return this->jugadoresVector[j].posicion;
}

DiccString<aed2::Nat>::const_Iterador Juego::pokemons(Jugador j) const{
    //assert(this->jugadoresConjunto.Pertenece(j));
    DiccString<aed2::Nat>::const_Iterador itPoke = this->jugadoresVector[j].pokemonsCapturados.CrearIt();
    return itPoke;
}

aed2::Conj<Jugador> Juego::expulsados() const{
    aed2::Conj<Jugador> exp;
    for(aed2::Nat i = 0; i < this->jugadoresVector.Longitud(); i++){
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
    //assert(this->posicionesPokemons.Pertenece(c));
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    return this->jugadoresPokemonsMapa[e].pokemon->pokemon;
}

aed2::Nat Juego::cantidadMovimientosParaCapturar(Coordenada c) const{
    //assert(this->posicionesPokemons.Pertenece(c));
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    return this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos;
}

bool Juego::puedoAgregarPokemon(Coordenada c) const{
    bool res = this->mapa().posExistente(c);
    aed2::Conj<Coordenada>::const_Iterador itCoors = this->posicionesPokemons.CrearIt();
    while(itCoors.HaySiguiente()){
        if(c.distEuclidea(itCoors.Siguiente()) <= 25){
            res = false;
        }
        itCoors.Avanzar();
    }
    return res;
}

bool Juego::hayPokemonCercano(Coordenada c) const{
    return this->pokemonsADistancia(2,c).Longitud() > 0;
}

Coordenada Juego::posPokemonCercano(Coordenada c) const{
    //assert(this->hayPokemonCercano(c));
    return this->pokemonsADistancia(2,c).Primero();
}

aed2::Conj<Jugador> Juego::entrenadoresPosibles(Coordenada c) const{
    //assert(this->hayPokemonCercano(c));
    aed2::Conj<Jugador> res;
    Coordenada pos = this->posPokemonCercano(c);
    aed2::Nat posPoke = pos.latitud() * this->cantidadColumnas + pos.longitud();
    ColaPrior<Juego::JugadorEsperando>::const_Iterador itJugEsp = this->jugadoresPokemonsMapa[posPoke].pokemon->jugadoresEsperando.CrearIt();
    while(itJugEsp.HaySiguiente()){
        res.Agregar(itJugEsp.Siguiente().jugador);
        itJugEsp.Avanzar();
    }
    return res;
}

aed2::Nat Juego::indiceRareza(Pokemon p) const{
    //assert(this->pokemonsCantidades.Definido(p));
    return 100 - (100 * this->cantMismaEspecie(p) / this->cantPokemonsTotales());
}

aed2::Nat Juego::cantPokemonsTotales() const{
    return this->cantidadTotalPokemons;
}

aed2::Nat Juego::cantMismaEspecie(Pokemon p) const{
    return this->pokemonsCantidades.Obtener(p);
}

aed2::Lista<Juego::DatosJugador> Juego::jugadoresADistancia(aed2::Nat d, Coordenada c) const{
    aed2::Lista<Juego::DatosJugador> res = aed2::Lista<Juego::DatosJugador>();
    for(aed2::Nat i = 0; i < this->jugadoresVector.Longitud(); i++){
        if(!this->jugadoresVector[i].banneado && this->jugadoresVector[i].conectado){
            if(c.distEuclidea(this->jugadoresVector[i].posicion) <= d*d){
                Juego::DatosJugador nuevoJug = Juego::DatosJugador();
                nuevoJug = this->jugadoresVector[i];
                res.AgregarAtras(nuevoJug);
            }
        }
    }
    return res;
}

aed2::Lista<Coordenada> Juego::pokemonsADistancia(aed2::Nat d, Coordenada c) const{
    aed2::Lista<Coordenada> res = aed2::Lista<Coordenada>();
    aed2::Conj<Coordenada>::const_Iterador itCoors = this->posicionesPokemons.CrearIt();
    while(itCoors.HaySiguiente()){
        if(c.distEuclidea(itCoors.Siguiente()) <= d*d){
            Coordenada nueva = itCoors.Siguiente();
            res.AgregarAtras(nueva);
        }
        itCoors.Avanzar();
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

