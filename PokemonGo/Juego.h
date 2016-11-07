#ifndef JUEGO_H
#define JUEGO_H

#include "TiposJuego.h"
#include "Coordenada.h"
#include "Mapa.h"

class Juego{
    private:


        struct DatosPokemon{
            Pokemon pokemon;
            aed2::Nat cantidad;
            DatosPokemon(Pokemon p, aed2::Nat c){
                pokemon = p;
                cantidad = c;
            };
        };

        struct DatosPokemonSalvaje{
            // Cambiar el tipo nat de la cola de prioridad por Juego::JugadorEsperando
            // Pero ahora lo dejo asi porque como no esta hecha la cola pincha
            Pokemon pokemon;
            Coordenada posicion;
            ColaPrior<aed2::Nat> jugadoresEsperando;
            aed2::Nat cantidadMovimientos;
            DatosPokemonSalvaje(Pokemon p, Coordenada c, ColaPrior<aed2::Nat> jc, aed2::Nat cm){
                pokemon = p;
                posicion = c;
                jugadoresEsperando = jc;
                cantidadMovimientos = cm;
            };
        };

        struct JugadorEsperando{
            Jugador jugador;
            aed2::Nat cantidadPokemonsAtrapados;
            JugadorEsperando(Jugador j, aed2::Nat c){
                jugador = j;
                cantidadPokemonsAtrapados = c;
            };
        };

        struct DatosJugador {
            aed2::Nat id;
            aed2::Nat sanciones;
            Coordenada posicion;
            bool conectado;
            // Pasarlo a multiconjunto
            aed2::Conj<Juego::DatosPokemon> pokemonsCapturados;
            bool banneado;
            Juego::JugadorEsperando* esperandoParaCapturar;
            DatosJugador(aed2::Nat i, aed2::Nat s, Coordenada p, bool c, aed2::Conj<DatosPokemon> pc, bool b, Juego::JugadorEsperando* je){
                id = i;
                sanciones = s;
                posicion = p;
                conectado = c;
                pokemonsCapturados = pc;
                banneado = b;
                esperandoParaCapturar = je;
            };
        };

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
