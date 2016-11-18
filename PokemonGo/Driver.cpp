#include "Driver.h"
#include "Mapa.h"
#include "Juego.h"
#include "Coordenada.h"

// Instanciar un mapa y un juego 

Driver::Driver(const Conj< Coordenada > & cs)
{
    Mapa m;
    Conj<Coordenada>::const_Iterador itCoor = cs.CrearIt();
    while(itCoor.HaySiguiente()){
        m.agregarCoor(itCoor.Siguiente());
    }
    Juego j;
    j.crearJuego(m);
    this->juegoDriver = j;
}

Driver::~Driver()
{

}

void Driver::agregarPokemon(const Pokemon & p, const Coordenada & c)
{
    this->juegoDriver.agregarPokemon(p, c);
}


/* Agrega un nuevo jugador, asignandole el id correspondiente.
 * Esta función deberá cambiar su aridad respecto del TAD devolviendo:
 * el id del jugador agregado. */
Jugador Driver::agregarJugador(){
    return this->juegoDriver.agregarJugador();
}

/* Al jugador pasado por parametro, lo conecta en la coordenada indicada.
 * Requiere que el jugador este en el juego desconectado y
 * que la Coordenada pasada este en el mapa. */
void Driver::conectarse(const Jugador & j, const Coordenada & c){
    this->juegoDriver.conectarse(j,c);
}

/* Al jugador pasado por parametro, lo desconecta.
 * Requiere que el jugador este en el juego conectado. */
void Driver::desconectarse(const Jugador & j){
    this->juegoDriver.desconectarse(j);
}

/* Al jugador pasado por parametro, lo intenta mover hacia la coordenada indicada.
 * Requiere que el jugador este en el juego conectado y
 * que la Coordenada pasada este en el mapa. */
void Driver::moverse(const Jugador & j, const Coordenada & c){
    this->juegoDriver.moverse(j,c);
}

/* Devuelve todas las coordenadas que posee el mapa del Juego. */
Conj< Coordenada > Driver::mapa() const{
    return this->juegoDriver.mapa().coordenadas();
}

/* Indica si hay un camino posible entre dos coordenadas
*  Requiere que las coordenadas existan en el mapa */
bool Driver::hayCamino(const Coordenada & c1, const Coordenada & c2) const{
    return this->juegoDriver.mapa().hayCamino(c1,c2);
}

/* Indica si una coordenada existe o no en el mapa */
bool Driver::posExistente(const Coordenada & c) const{
    return this->juegoDriver.mapa().posExistente(c);
}

/* Devuelve los jugadores que fueron insertados en el juego y no fueron eliminados. */
Conj< Jugador > Driver::jugadores() const{
    Conj<aed2::Nat>::const_Iterador itJug = this->juegoDriver.jugadores();
    Conj<Jugador> res;
    while(itJug.HaySiguiente()){
        res.AgregarRapido(itJug.Siguiente());
        itJug.Avanzar();
    }
    return res;
}

/* Dado el jugador pasado como parametro, retorna si esta conectado o no.
 * Requiere que el jugador este entre jugadores() del juego. */
bool Driver::estaConectado(const Jugador & j) const{
    return this->juegoDriver.estaConectado(j);
}

/* Dado el jugador pasado como parametro, devuelve la cantidad de sanciones que recibio.
 * Requiere que el jugador este entre jugadores() del juego. */
Nat Driver::sanciones(const Jugador & j) const{
    return this->juegoDriver.sanciones(j);
}

/* Dado el jugador pasado como parametro, devuelve la coordenada donde se ubica.
 * Requiere que el jugador este entre jugadores() del juego y este conectado. */
Coordenada Driver::posicion(const Jugador & j) const{
    return this->juegoDriver.posicion(j);
}

/* Dado el jugador pasado como parametro, devuelve un MultiConjunto con los
 * pokemons que capturo.
 * Requiere que el jugador este entre jugadores() del juego. */
Dicc< Pokemon , Nat > Driver::pokemons(const Jugador & j) const{
    DiccString<aed2::Nat>::const_Iterador itDicc = this->juegoDriver.pokemons(j);
    Dicc<Pokemon, Nat> res;
    while(itDicc.HaySiguiente()){
        res.Definir(itDicc.Siguiente().clave, itDicc.Siguiente().significado);
        itDicc.Avanzar();
    }
    return res;
}

/* Devuelve los jugadores que fueron expulsados del juego. */
Conj< Jugador > Driver::expulsados() const{
    return this->juegoDriver.expulsados();
}


/* Devuelve todas las coordenadaes del mapa que tienen un pokemon en ella. */
Conj< Coordenada > Driver::posConPokemons() const{
    return this->juegoDriver.posConPokemons();
}

/* Dada una coordenada del mapa, devuelve al pokemon situado en ella.
 * Es requisito que la coordenada exista en el mapa y que exista un pokemon alli. */
Pokemon Driver::pokemonEnPos(const Coordenada & c) const{
    return this->juegoDriver.pokemonsEnPos(c);
}

/* Dada una coordenada, devuelve el valor del contador de movimientos fuera del rango.
* Es requisito que en la coordenada pasada como parametro haya un pokemon. */
Nat Driver::cantMovimientosParaCaptura(const Coordenada & c) const{
    this->juegoDriver.cantidadMovimientosParaCapturar(c);
}

/* Dada una coordenada cualquiera, indica si la coordenada existe en el mapa y
 * que hay un pokemon a distancia menor o igual a 5. */

bool Driver::puedoAgregarPokemon(const Coordenada & c) const{
    this->juegoDriver.puedoAgregarPokemon(c);
}

/* Devuelve si hay un pokemon a distancia menor o igual a 2
 * de la Coordenada pasada como parametro. */
bool Driver::hayPokemonCercano(const Coordenada & c) const{
    this->juegoDriver.hayPokemonCercano(c);
}

/* Dada una Coordenada, devuelve la coordenada del pokemon cercano.
 * Requiere que haya un pokemon a distancia menor o igual a 2. */
Coordenada Driver::posPokemonCercano(const Coordenada & c) const{
    return this->juegoDriver.posPokemonCercano(c);
}

/* Devuelve todos los jugadores que esten a distancia menor o igual a 2 de
 * la coordenada indicada, que tengan un camino hasta ella.
 * Requiere que haya un pokemon a distancia menor o igual a 2 de la Coordenada. */
Conj<Jugador> Driver::entrenadoresPosibles(const Coordenada & c) const{
    return this->juegoDriver.entrenadoresPosibles(c);
}

/* Devuelve el indice de rarez del pokemon pasado como parametro.
 * Requiere que haya al menos un pokemon de la especie en el juego. */
Nat Driver::indiceRareza(const Pokemon & p) const{
    this->juegoDriver.indiceRareza(p);
}

/* Devuelve la cantidad de pokemons totales en el juego. */
Nat Driver::cantPokemonsTotales() const{
    return this->juegoDriver.cantPokemonsTotales();
}

/* Indica cuantos pokemons de la especie de unPokemon hay en pokemons. */
Nat Driver::cantMismaEspecie(const Pokemon & p) const{
    return this->cantMismaEspecie(p);
}
