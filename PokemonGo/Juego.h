#ifndef JUEGO_H
#define JUEGO_H

#include "TiposJuego.h"
#include "Coordenada.h"
#include "Mapa.h"

class Juego{
    private:

        struct JugadorEsperando{
            Jugador jugador;
            aed2::Nat cantidadPokemonsAtrapados;
            JugadorEsperando(){

            };
            void crearJugadorEsperando(Jugador j, aed2::Nat c){
                jugador = j;
                cantidadPokemonsAtrapados = c;
            }

            bool operator < (const JugadorEsperando & c) const{
                return this->cantidadPokemonsAtrapados < c.cantidadPokemonsAtrapados;
            }
        };

        struct DatosPokemonSalvaje{
            Pokemon pokemon;
            Coordenada posicion;
            ColaPrior<Juego::JugadorEsperando> jugadoresEsperando;
            aed2::Nat cantidadMovimientos;
            DatosPokemonSalvaje(){
            };
            void crearDatosPokeSalv(Pokemon p, Coordenada c, ColaPrior<Juego::JugadorEsperando> cp){
                pokemon = p;
                posicion = c;
                jugadoresEsperando = cp;
                cantidadMovimientos = 0;
            }
        };

        struct DatosJugador {
            aed2::Nat id;
            aed2::Nat sanciones;
            Coordenada posicion;
            bool conectado;
            DiccString<aed2::Nat> pokemonsCapturados;
            aed2::Nat cantidadPokemonsAtrapados;
            bool banneado;
            ColaPrior<Juego::JugadorEsperando>::Iterador esperandoParaCapturar;
            aed2::Conj<aed2::Nat>::Iterador referenciaConjunto;
            DatosJugador(aed2::Nat i, aed2::Conj<aed2::Nat>::Iterador refConj){
                id = i;
                sanciones = 0;
                Coordenada c;
                c.crearCoor(0,0);
                posicion = c;
                conectado = false;
                DiccString<aed2::Nat> pokeCap;
                pokemonsCapturados = pokeCap;
                cantidadPokemonsAtrapados = 0;
                banneado = false;
                ColaPrior<Juego::JugadorEsperando>::Iterador colaPoke;
                esperandoParaCapturar = colaPoke;
                referenciaConjunto = refConj;
            };
        };

        struct JugadorPokemonEnMapa{
            Juego::DatosJugador* jugador;
            Juego::DatosPokemonSalvaje* pokemon;
            JugadorPokemonEnMapa(Juego::DatosJugador* j, Juego::DatosPokemonSalvaje* p){
                jugador = j;
                pokemon = p;
            };
        };

        aed2::Vector<Juego::DatosJugador> jugadoresVector;
        aed2::Conj<aed2::Nat> jugadoresConjunto;
        aed2::Conj<Coordenada> posicionesPokemons;
        DiccString<aed2::Nat> pokemonsCantidades;
        aed2::Arreglo<Juego::JugadorPokemonEnMapa> jugadoresPokemonsMapa;
        aed2::Lista<Juego::DatosPokemonSalvaje> pokemonsSalvajes;
        Mapa mapaJuego;
        aed2::Nat cantidadTotalPokemons;
        aed2::Nat cantidadFilas;
        aed2::Nat cantidadColumnas;

        aed2::Lista<Juego::DatosJugador> jugadoresADistancia(aed2::Nat, Coordenada);
        aed2::Lista<Juego::DatosPokemonSalvaje> pokemonsADistancia(aed2::Nat, Coordenada);
        aed2::Conj<Jugador> expulsadosAux(aed2::Vector<Juego::DatosJugador>);
        aed2::Conj<Jugador> jugadoresAux(aed2::Vector<Juego::DatosJugador>);

    public:

        Juego();
        ~Juego();

        void crearJuego(Mapa);
        void agregarPokemon(Pokemon, Coordenada);
        void agregarJugador();
        void conectarse(Jugador, Coordenada);
        void desconectarse(Jugador);
        void moverse(Jugador, Coordenada);
        Mapa mapa();
        aed2::Conj<Jugador>::Iterador jugadores();
        bool estaConectado(Jugador);
        aed2::Nat sanciones(Jugador);
        Coordenada posicion(Jugador);
        DiccString<aed2::Nat>::Iterador pokemons(Jugador);
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
