#ifndef JUEGO_H
#define JUEGO_H

#include "TiposJuego.h"
#include "Coordenada.h"
#include "Mapa.h"

class Juego{
    private:
        // Falta el vector con lso dats jugador, hay que crear el tipo tupla
        aed2::Conj<Jugador> jugadoresAgregados;
        aed2::Conj<Coordenada> posicionesPokemons;
        aed2::Dicc<Pokemon, aed2::Nat> pokemonsCantidades;
        // Falta jugadoresPokemonsMapa hay que crear el tipo arreglo redimensionable
        // Falta pokemonsSalvajes
        Mapa mapaJuego;
        aed2::Nat cantidadTotalPokemons;
        aed2::Nat cantidadFilas;
        aed2::Nat cantidadColumnas;
        // La tupla podriamos representarla como una lista de cosas

    public:

        Juego();
        ~Juego();

        void crearJuego(Mapa);
        void agregarPokemon(Pokemon, Coordenada);
        void agregarJugador(Jugador);
        void conectarse(Jugador, Coordenada);
        void desconectarse(Jugador);
        void moverse(Jugador, Coordenada);
        Mapa mapa();
        aed2::Conj<Jugador> jugadores();
        bool estaConectado(Jugador);
        aed2::Nat sanciones(Jugador);
        Coordenada posicion(Jugador);
        // Falta pokemons que devuelve el iterador
        aed2::Conj<Jugador> expulsados();
        aed2::Conj<Coordenada> posConPokemons();
        Pokemon pokemonsEnPos(Coordenada);
        aed2::Nat cantidadMovimientosParaCapturar(Coordenada);
        bool puedoAgregarPokemon(Coordenada);
        bool hayPokemonCercano(Coordenada);
        Coordenada posPokemonCercano(Coordenada);
        aed2::Conj<Jugador> entrenadoresPosibles(Coordenada, aed2::Conj<Jugador>);
        aed2::Nat indiceRareza(Pokemon);
        aed2::Nat cantPokemonsTotales();
        aed2::Nat cantMismaEspecie(Pokemon);
};

#endif // JUEGO_H
