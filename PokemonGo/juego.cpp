#include "Juego.h"

Juego::Juego(){

}

Juego::~Juego(){
    this->EliminarJuego();
}

void Juego::EliminarJuego(){

}

void Juego::crearJuego(Mapa m){
    // Inicializa un juego vacio
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
    // Mira si existe algun pokemon del mismo tipo en el juego
    if(this->pokemonsCantidades.Definido(p)){
        valor = this->pokemonsCantidades.Obtener(p);
    }
    // Define en el diccionario de pokemons salvajes, el pokemon agregado, y la cantidad correspondiente en el juego
    this->pokemonsCantidades.Definir(p, valor + 1);
    // Crea la cola de prioridad de los entrenadores posibles para capturarlo
    ColaPrior<Juego::JugadorEsperando> heapEsperandoCaptura = ColaPrior<Juego::JugadorEsperando>();
    heapEsperandoCaptura.Vacia();
    // Agrega el pokemon al vector que representa las posiciones del mapa
    Juego::DatosPokemonSalvaje datosPoke = Juego::DatosPokemonSalvaje(p, c, heapEsperandoCaptura, this->posicionesPokemons.AgregarRapido(c));
    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador datosNuevos = this->pokemonsSalvajes.AgregarAtras(datosPoke);
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresPokemonsMapa[e].pokemon = &datosNuevos.Siguiente();
    }else{
        Juego::JugadorPokemonEnMapa datos = Juego::JugadorPokemonEnMapa(aed2::Conj<Juego::DatosJugador*>(), &datosNuevos.Siguiente());
        this->jugadoresPokemonsMapa.Definir(e, datos);
    }
    // Se fija si hay jugadores cercanos al pokemon agregado
    aed2::Lista<Juego::DatosJugador> jugadoresCercanos = this->jugadoresADistancia(2,c);
    aed2::Lista<Juego::DatosJugador>::const_Iterador itCercanos = jugadoresCercanos.CrearIt();
    // Recorre los jugadores cercanos y los va encolando en la cola de prioridad de entrenadores para capturar al pokemon
    while(itCercanos.HaySiguiente()){
        Juego::JugadorEsperando jugEsp = Juego::JugadorEsperando(itCercanos.Siguiente().id, itCercanos.Siguiente().cantidadPokemonsAtrapados);
        this->jugadoresVector[itCercanos.Siguiente().id].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugEsp);
        itCercanos.Avanzar();     
    }
    // Aumenta en uno la cantidad de pokemons total del juego
    this->cantidadTotalPokemons ++;
}

aed2::Nat Juego::agregarJugador(){
    aed2::Nat id = this->jugadoresVector.Longitud();
    // Agrega el jugador al conjunto de jugadores del juego
    aed2::Conj<aed2::Nat>::Iterador itReferencia = this->jugadoresConjunto.AgregarRapido(id);
    // Agrega el jugador al vector de jugadores del juego
    Juego::DatosJugador datosJ = Juego::DatosJugador(id, itReferencia);
    this->jugadoresVector.AgregarAtras(datosJ);
    return id;
}

void Juego::conectarse(Jugador j, Coordenada c){
    //assert(this->jugadoresConjunto.Pertenece(j) && !this->estaConectado(j) && this->mapa().posExistente(c));
    // Modifica la posicion actual del jugador que se conecta
    this->jugadoresVector[j].posicion = c;
    // Pone el flag de conectado del jugador en true
    this->jugadoresVector[j].conectado= true;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    // Se fija si en la posicion que se conecta el jugador, hay jugadores y lo coloca en el mapa
    if(this->jugadoresPokemonsMapa.Definido(e)){
        this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[e].jugadores.AgregarRapido(&this->jugadoresVector[j]);
    }else{
        aed2::Conj<Juego::DatosJugador*> nuevoConj = aed2::Conj<Juego::DatosJugador*>();
        Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(nuevoConj, NULL);
        this->jugadoresPokemonsMapa.Definir(e, nuevoJug);
        this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[e].jugadores.AgregarRapido(&this->jugadoresVector[j]);

    }
    // Mira si hay pokemon cercano al jugador que se conecta
    if(this->hayPokemonCercano(c)){
        Coordenada posPoke = this->posPokemonCercano(c);
        aed2::Nat latP = posPoke.latitud();
        aed2::Nat lonP = posPoke.longitud();
        aed2::Nat eP = latP * this->cantidadColumnas + lonP;
        // Vuelve los movimientos exteriores del pokemon cercano a 0
        this->jugadoresPokemonsMapa[eP].pokemon->cantidadMovimientos = 0;
        // Encola al jugador en la cola de prioridad del pokemon cercano
        Juego::JugadorEsperando jugN = Juego::JugadorEsperando(this->jugadoresVector[j].id, this->jugadoresVector[j].cantidadPokemonsAtrapados);
        this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[eP].pokemon->jugadoresEsperando.Encolar(jugN);
    }
}

void Juego::desconectarse(Jugador j){
    //assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j));
    // Pone el flag de conectado del jugador en false
    this->jugadoresVector[j].conectado = false;
    // Elimina al jugador del mapa del juego
    Coordenada c = this->jugadoresVector[j].posicion;
    aed2::Nat lat = c.latitud();
    aed2::Nat lon = c.longitud();
    aed2::Nat e = lat * this->cantidadColumnas + lon;
    if(this->jugadoresPokemonsMapa.Definido(e)){
        if(this->jugadoresVector[j].referenciaMapa.Siguiente()->esperandoParaCapturar.HaySiguiente()){
            this->jugadoresVector[j].referenciaMapa.Siguiente()->esperandoParaCapturar.EliminarSiguiente();
        }
        this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
    }
}

void Juego::moverse(Jugador j, Coordenada c){
    //assert(this->jugadoresConjunto.Pertenece(j) && this->estaConectado(j) && this->mapa().coordenadas().Pertenece(c));
    Coordenada posicionActual = this->jugadoresVector[j].posicion;
    Coordenada posicionNueva = c;
    // Se fija si el jugador realiza un movimiento invalido, y ya tiene acumuladas 4 sanciones
    if((!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) > 100) && this->jugadoresVector[j].sanciones >= 4){
        this->jugadoresVector[j].sanciones ++;
        // Pone el flag de banneado del jugador en true
        this->jugadoresVector[j].banneado = true;
        // Elimina al jugador que se va a bannear del conjunto de jugadores del juego
        this->jugadoresVector[j].referenciaConjunto.EliminarSiguiente();
        DiccString<aed2::Nat>::Iterador pokemonsAtrapadosDe = this->jugadoresVector[j].pokemonsCapturados.CrearIt();
        // Recorre todos los pokemons atrapados por el jugador, y los elimina del juego
        // Recorre el diccstring que tiene los datos de los pokemons del juego, y va disminuyendo las cantidades de los atrapados por el jugador
        while(pokemonsAtrapadosDe.HaySiguiente()){
            aed2::Nat cantidad = this->pokemonsCantidades.Obtener(pokemonsAtrapadosDe.Siguiente().clave);
            this->pokemonsCantidades.Definir(pokemonsAtrapadosDe.Siguiente().clave, cantidad - pokemonsAtrapadosDe.Siguiente().significado);
            this->cantidadTotalPokemons = this->cantidadTotalPokemons - pokemonsAtrapadosDe.Siguiente().significado;
            pokemonsAtrapadosDe.Avanzar();
        }
        // Elimina al jugador del mapa
        this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
    // Se fija si el movimiento es invalido pero no acumula 4 sanciones
    }else if(!this->mapa().hayCamino(posicionActual, c) || posicionActual.distEuclidea(c) > 100){
        // Sanciona al jugador
        this->jugadoresVector[j].sanciones ++;
    }else{
        // En caso de que no haya que sancionarlo mueve al jugador
        // Asigna la nueva posicion
        this->jugadoresVector[j].posicion = c;
        aed2::Nat latN = c.latitud();
        aed2::Nat lonN = c.longitud();
        aed2::Nat eN = latN * this->cantidadColumnas + lonN;
        // Agrega al jugador al mapa del juego
        if(this->jugadoresPokemonsMapa.Definido(eN)){
            this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
            this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[eN].jugadores.AgregarRapido(&this->jugadoresVector[j]);
        }else{
            Juego::JugadorPokemonEnMapa nuevoJug = Juego::JugadorPokemonEnMapa(aed2::Conj<Juego::DatosJugador*>(), NULL);
            this->jugadoresPokemonsMapa.Definir(eN, nuevoJug);
            this->jugadoresVector[j].referenciaMapa.EliminarSiguiente();
            this->jugadoresVector[j].referenciaMapa = this->jugadoresPokemonsMapa[eN].jugadores.AgregarRapido(&this->jugadoresVector[j]);
        }
        // Se fija si hay pokemon cercano a la posicion anterior a moverse
        if(this->hayPokemonCercano(posicionActual)){
            Coordenada pokemonCercanoPosicionActual = this->posPokemonCercano(posicionActual);
            // Se fija si hay pokemon cercano a la nueva posicion
            if(this->hayPokemonCercano(posicionNueva)){
                Coordenada pokemonCercanoPosicionNueva= this->posPokemonCercano(posicionNueva);
                // Si los pokemons de la posicion anterior y la actual son distintos
                if(pokemonCercanoPosicionActual != pokemonCercanoPosicionNueva){
                    aed2::Nat lat = pokemonCercanoPosicionNueva.latitud();
                    aed2::Nat lon = pokemonCercanoPosicionNueva.longitud();
                    aed2::Nat e = lat * this->cantidadColumnas + lon;
                    // Pone en 0 los movmientos del pokemon de la nueva posicion
                    this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos = 0;
                    // Elimina al jugador de la cola de prioridad del pokemon de la posicion anterior
                    this->jugadoresVector[j].esperandoParaCapturar.EliminarSiguiente();
                    // Encola al jugador en la cola de prioridad del pokemon de la nueva posicion
                    Juego::JugadorEsperando jugNuevo = Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
                    this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugNuevo);
                    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                    // Recorre todos los pokemons salvajes, y aumenta en uno los movimientos de los que son distintos al pokemon
                    // de la nueva posicion
                    while(itPosPoke.HaySiguiente()){
                        if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                            itPosPoke.Siguiente().cantidadMovimientos ++;
                        }
                        itPosPoke.Avanzar();
                    }
                }else{
                    // Si el pokemon de la posicion anterior y el de la posicion nueva son iguales
                    // Recorre todas las posiciones de los pokemons salvajes, y suma uno a la cantidad de movimientos
                    // de los que son distintos al pokemon cercano al jugador
                    aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                    while(itPosPoke.HaySiguiente()){
                        if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                            itPosPoke.Siguiente().cantidadMovimientos ++;
                        }
                        itPosPoke.Avanzar();
                    }
                }
            }else{
                // Si no hay pokemon en la nueva posicion
                // Elimina al jugador de la cola de prioridad del pokemon de la posicion anterior
                this->jugadoresVector[j].esperandoParaCapturar.EliminarSiguiente();
                // Suma uno a los movimientos de todos los pokemons salvajes
                aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
                while(itPosPoke.HaySiguiente()){
                    itPosPoke.Siguiente().cantidadMovimientos ++;
                    itPosPoke.Avanzar();
                }
            }
        }else if(this->hayPokemonCercano(posicionNueva)){
            // Si no hay pokemon en la posicion anterior pero si en la nueva posicion
            Coordenada pokemonCercanoPosicionNueva= this->posPokemonCercano(posicionNueva);
            aed2::Nat lat = pokemonCercanoPosicionNueva.latitud();
            aed2::Nat lon = pokemonCercanoPosicionNueva.longitud();
            aed2::Nat e = lat * this->cantidadColumnas + lon;
            // Pone en 0 los movimientos del pokemon de la nueva posicion
            this->jugadoresPokemonsMapa[e].pokemon->cantidadMovimientos = 0;
            // Encola al jugador en la cola de prioridad el pokemon de la nueva posicion
            Juego::JugadorEsperando jugNuevo = Juego::JugadorEsperando(j, this->jugadoresVector[j].cantidadPokemonsAtrapados);
            this->jugadoresVector[j].esperandoParaCapturar = this->jugadoresPokemonsMapa[e].pokemon->jugadoresEsperando.Encolar(jugNuevo);
            // Recorre todos los pokemons salvajes y le aumenta uno a la cantidad de movimientos de los que son distintos
            // del pokemon de la nueva posicion
            aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
            while(itPosPoke.HaySiguiente()){
                if(itPosPoke.Siguiente().posicion != pokemonCercanoPosicionNueva){
                    itPosPoke.Siguiente().cantidadMovimientos ++;
                }
                itPosPoke.Avanzar();
            }
        }else{
            // Si no hay pokemon en la posicion anterior y tampoco en la nueva posicion
            // Aumenta en uno la cantidad de movimientos de todos los pokemons salvajes
            aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
            while(itPosPoke.HaySiguiente()){
                    itPosPoke.Siguiente().cantidadMovimientos ++;
                    itPosPoke.Avanzar();
            }
        }
        // Recorre todos los pokemons salvajes para ver si alguno esta en condiciones de ser capturado
        aed2::Lista<Juego::DatosPokemonSalvaje>::Iterador itPosPoke = this->pokemonsSalvajes.CrearIt();
        while(itPosPoke.HaySiguiente()){
                bool seAtrapo = false;
                // Si el pokemon se atrapa
                if(itPosPoke.Siguiente().cantidadMovimientos >= 10 && itPosPoke.Siguiente().jugadoresEsperando.Tamanio() > 0){
                    // Se agrega el pokemon a los pokemons capturados del jugador mas prioritario de la cola de prioridad
                    // del pokemon que se atrapa
                    if(this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definido(itPosPoke.Siguiente().pokemon)){
                        aed2::Nat cant = this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Obtener(itPosPoke.Siguiente().pokemon);
                        this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, cant + 1);
                    }else{
                        this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].pokemonsCapturados.Definir(itPosPoke.Siguiente().pokemon, 1);
                    }
                    // Aumenta en uno la cantidad de pokemons atrapados del jugador que atrapa el pokemon
                    this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].cantidadPokemonsAtrapados ++;
                    Coordenada pokemonABorrarMapa = this->posPokemonCercano(this->jugadoresVector[itPosPoke.Siguiente().jugadoresEsperando.Proximo().jugador].posicion);
                    aed2::Nat lat = pokemonABorrarMapa.latitud();
                    aed2::Nat lon = pokemonABorrarMapa.longitud();
                    aed2::Nat e = lat * this->cantidadColumnas + lon;
                    // Elimina al pokemon atrapado del mapa del juego
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
    bool res = this->mapaJuego.posExistente(c);
    res = res & this->pokemonsADistancia(5,c).Longitud() == 0;
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
    aed2::Nat desdeColAnterior = desdeCol;
    Coordenada coorOrigen;
    coorOrigen.crearCoor(lat, lon);
    while(desdeFila <= hastaFila){
        while(desdeCol <= hastaCol){
            Coordenada coorDestino;
            coorDestino.crearCoor(desdeFila, desdeCol);
            if(coorOrigen.distEuclidea(coorDestino) <= d*d){
                aed2::Nat e = desdeFila * this->cantidadColumnas + desdeCol;
                if(this->jugadoresPokemonsMapa.Definido(e) && this->jugadoresPokemonsMapa[e].jugadores.Cardinal() > 0){
                    aed2::Conj<Juego::DatosJugador*>::const_Iterador itJugadores = this->jugadoresPokemonsMapa[e].jugadores.CrearIt();
                    while(itJugadores.HaySiguiente()){
                        res.AgregarAtras(*itJugadores.Siguiente());
                        itJugadores.Avanzar();
                    }
                }
            }
            desdeCol ++;
        }
        desdeCol = desdeColAnterior;
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

