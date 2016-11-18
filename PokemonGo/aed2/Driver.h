#ifndef DRIVER_H_
#define DRIVER_H_

#include "aed2/Conj.h"
#include "aed2/Dicc.h"
#include "aed2/TiposBasicos.h"
#include "TiposJuego.h"

using namespace aed2;

class Driver {

	public:

	/* Inicializa un juego con un mapa fijo. */
	Driver(const Conj< Coordenada > & cs);
	
	/* Destruye el contenido del juego, liberando la memoria dinámica alocada. */
	~Driver();

	/* Agrega el pokemon pasado por parametro en su coordenada al juego. */
	void agregarPokemon(const Pokemon & p, const Coordenada & c);

	/* Agrega un nuevo jugador, asignandole el id correspondiente. 
	 * Esta función deberá cambiar su aridad respecto del TAD devolviendo: 
	 * el id del jugador agregado. */	
	Jugador agregarJugador();

	/* Al jugador pasado por parametro, lo conecta en la coordenada indicada.
	 * Requiere que el jugador este en el juego desconectado y 
	 * que la Coordenada pasada este en el mapa. */
	void conectarse(const Jugador & j, const Coordenada & c);

	/* Al jugador pasado por parametro, lo desconecta.
	 * Requiere que el jugador este en el juego conectado. */
	void desconectarse(const Jugador & j);

	/* Al jugador pasado por parametro, lo intenta mover hacia la coordenada indicada.
	 * Requiere que el jugador este en el juego conectado y 
	 * que la Coordenada pasada este en el mapa. */
	void moverse(const Jugador & j, const Coordenada & c);

	/* Devuelve todas las coordenadas que posee el mapa del Juego. */
	Conj< Coordenada > mapa() const;

	/* Indica si hay un camino posible entre dos coordenadas 
	*  Requiere que las coordenadas existan en el mapa */
	bool hayCamino(const Coordenada & c1, const Coordenada & c2) const;
	
	/* Indica si una coordenada existe o no en el mapa */
	bool posExistente(const Coordenada & c) const;

	/* Devuelve los jugadores que fueron insertados en el juego y no fueron eliminados. */
	Conj< Jugador > jugadores() const;

	/* Dado el jugador pasado como parametro, retorna si esta conectado o no.
	 * Requiere que el jugador este entre jugadores() del juego. */
	bool estaConectado(const Jugador & j) const;

	/* Dado el jugador pasado como parametro, devuelve la cantidad de sanciones que recibio.
	 * Requiere que el jugador este entre jugadores() del juego. */
	Nat sanciones(const Jugador & j) const;

	/* Dado el jugador pasado como parametro, devuelve la coordenada donde se ubica.
	 * Requiere que el jugador este entre jugadores() del juego y este conectado. */
	Coordenada posicion(const Jugador & j) const;

	/* Dado el jugador pasado como parametro, devuelve un MultiConjunto con los
	 * pokemons que capturo.
	 * Requiere que el jugador este entre jugadores() del juego. */
	Dicc< Pokemon , Nat > pokemons(const Jugador & j) const;

	/* Devuelve los jugadores que fueron expulsados del juego. */
	Conj< Jugador > expulsados() const;

	/* Devuelve todas las coordenadaes del mapa que tienen un pokemon en ella. */
	Conj< Coordenada > posConPokemons() const;

	/* Dada una coordenada del mapa, devuelve al pokemon situado en ella.
	 * Es requisito que la coordenada exista en el mapa y que exista un pokemon alli. */
	Pokemon pokemonEnPos(const Coordenada & c) const;

 	/* Dada una coordenada, devuelve el valor del contador de movimientos fuera del rango.
	* Es requisito que en la coordenada pasada como parametro haya un pokemon. */
	Nat cantMovimientosParaCaptura(const Coordenada & c) const;

	/* Dada una coordenada cualquiera, indica si la coordenada existe en el mapa y
	 * que hay un pokemon a distancia menor o igual a 5. */

	bool puedoAgregarPokemon(const Coordenada & c) const;

	/* Devuelve si hay un pokemon a distancia menor o igual a 2
	 * de la Coordenada pasada como parametro. */
	bool hayPokemonCercano(const Coordenada & c) const;

	/* Dada una Coordenada, devuelve la coordenada del pokemon cercano.
	 * Requiere que haya un pokemon a distancia menor o igual a 2. */
	Coordenada posPokemonCercano(const Coordenada & c) const;

	/* Devuelve todos los jugadores que esten a distancia menor o igual a 2 de
	 * la coordenada indicada, que tengan un camino hasta ella.
	 * Requiere que haya un pokemon a distancia menor o igual a 2 de la Coordenada. */
	Conj<Jugador> entrenadoresPosibles(const Coordenada & c) const;
	
	/* Devuelve el indice de rarez del pokemon pasado como parametro.
	 * Requiere que haya al menos un pokemon de la especie en el juego. */
	Nat indiceRareza(const Pokemon & p) const;

	/* Devuelve la cantidad de pokemons totales en el juego. */
	Nat cantPokemonsTotales() const;

	/* Indica cuantos pokemons de la especie de unPokemon hay en pokemons. */
	Nat cantMismaEspecie(const Pokemon & p) const;


	private:

	/************************************************************************
	 * TODO: Va a ser necesario instanciar privadamente el Modulo principal *
	 * con el cuál interactuar. Además, pueden declarar todas las		   *
	 * funciones auxiliares que les hagan falta.							*
	 ************************************************************************/  

}; // class Driver


#endif // DRIVER_H_

