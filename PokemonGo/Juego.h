#ifndef JUEGO_H
#define JUEGO_H

#include "TiposJuego.h"
#include "Mapa.h"
#include "DiccString.hpp"
#include "ColaPrior.hpp"
#include "aed2/Vector.h"

class Juego{
    private:

        struct JugadorEsperando{
            Jugador jugador;
            aed2::Nat cantidadPokemonsAtrapados;
            JugadorEsperando(){}
            JugadorEsperando(Jugador j, aed2::Nat c){
                jugador = j;
                cantidadPokemonsAtrapados = c;
            }

            bool operator < (const JugadorEsperando & c) const{
                return this->cantidadPokemonsAtrapados < c.cantidadPokemonsAtrapados;
            }

            bool operator > (const JugadorEsperando & c) const{
                return this->cantidadPokemonsAtrapados > c.cantidadPokemonsAtrapados;
            }

            void operator = (const JugadorEsperando & c){
                this->jugador = c.jugador;
                this->cantidadPokemonsAtrapados = c.cantidadPokemonsAtrapados;
            }

            bool operator == (const JugadorEsperando & c) const{
                bool res = false;
                res = this->jugador == c.jugador;
                res = res && this->cantidadPokemonsAtrapados == c.cantidadPokemonsAtrapados;
                return res;
            }
        };

        struct DatosPokemonSalvaje{
            Pokemon pokemon;
            Coordenada posicion;
            ColaPrior<Juego::JugadorEsperando> jugadoresEsperando;            
            aed2::Nat cantidadMovimientos;
            aed2::Conj<Coordenada>::Iterador referenciaPosiciones; // ESTO NO ESTA EN EL DISEÑO
            DatosPokemonSalvaje(Pokemon p, Coordenada c, ColaPrior<Juego::JugadorEsperando> cp, aed2::Conj<Coordenada>::Iterador itConj){
                pokemon = p;
                posicion = c;
                jugadoresEsperando = cp;
                cantidadMovimientos = 0;
                referenciaPosiciones = itConj;
            }

            void operator = (const DatosPokemonSalvaje & c){
                this->pokemon = c.pokemon;
                this->posicion = c.posicion;
                this->jugadoresEsperando = c.jugadoresEsperando;
                this->cantidadMovimientos = c.cantidadMovimientos;
                this->referenciaPosiciones = c.referenciaPosiciones;
            }

            bool operator == (const DatosPokemonSalvaje & c){
                bool res = false;
                res = this->pokemon == c.pokemon;
                res = res && this->posicion == c.posicion;
                res = res && this->jugadoresEsperando == c.jugadoresEsperando;
                res = res && this->cantidadMovimientos == c.cantidadMovimientos;
                res = res && this->referenciaPosiciones == c.referenciaPosiciones;
                return res;
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
            aed2::Conj<Juego::DatosJugador*>::Iterador referenciaMapa; // NO ESTABA EN EL DISEÑO, SE AGREGA PARA CONTEMPLAR QUE HAYA MAS DE UN JUGADOR EN LA MISMA POS
            DatosJugador(aed2::Nat i, aed2::Conj<aed2::Nat>::Iterador refConj){
                id = i;
                sanciones = 0;
                Coordenada c;
                c.crearCoor(0,0);
                posicion = c;
                conectado = false;
                DiccString<aed2::Nat> pokeCap;
                pokeCap.vacio();
                pokemonsCapturados = pokeCap;
                cantidadPokemonsAtrapados = 0;
                banneado = false;
                ColaPrior<Juego::JugadorEsperando> colaPoke;
                colaPoke.Vacia();
                ColaPrior<Juego::JugadorEsperando>::Iterador itColaPoke = colaPoke.CrearIterador(NULL);
                esperandoParaCapturar = itColaPoke;
                referenciaConjunto = refConj;
            }

            void operator = (const DatosJugador & c){
                this->id = c.id;
                this->sanciones = c.sanciones;
                this->posicion = c.posicion;
                this->conectado = c.conectado;
                this->pokemonsCapturados = c.pokemonsCapturados;
                this->banneado = c.banneado;
                this->esperandoParaCapturar = c.esperandoParaCapturar;
                this->referenciaConjunto = c.referenciaConjunto;
            }

            bool operator == (const DatosJugador & c){
                bool res = false;
                res = this->id == c.id;
                res = res && this->sanciones == c.sanciones;
                res = res && this->posicion == c.posicion;
                res = res && this->conectado == c.conectado;
                res = res && this->pokemonsCapturados == c.pokemonsCapturados;
                res = res && this->banneado == c.banneado;
                res = res && this->referenciaConjunto == c.referenciaConjunto;
                return res;
            }

        };

        struct JugadorPokemonEnMapa{
            aed2::Conj<Juego::DatosJugador*> jugadores; // NO ESTABA EN EL DISEÑO, SE AGREGA PARA CONTEMPLAR QUE HAYA MAS DE UN JUGADOR EN LA MISMA POS
            Juego::DatosPokemonSalvaje* pokemon;
            JugadorPokemonEnMapa(aed2::Conj<Juego::DatosJugador*> j, Juego::DatosPokemonSalvaje* p){
                jugadores = j;
                pokemon = p;
            }

            void operator = (const JugadorPokemonEnMapa & c){
                this->jugadores = c.jugadores;
                this->pokemon = c.pokemon;
            }

            bool operator == (const JugadorPokemonEnMapa & c){
                bool res = this->jugadores == c.jugadores;
                res = res && this->pokemon == c.pokemon;
                return res;
            }

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

        aed2::Lista<Juego::DatosJugador> jugadoresADistancia(aed2::Nat, Coordenada) const;
        aed2::Lista<Coordenada> pokemonsADistancia(aed2::Nat, Coordenada) const;
        aed2::Conj<Jugador> expulsadosAux(aed2::Vector<Juego::DatosJugador>);
        aed2::Conj<Jugador> jugadoresAux(aed2::Vector<Juego::DatosJugador>);

    public:

        Juego();
        ~Juego();

        void EliminarJuego();
        void crearJuego(Mapa);
        void agregarPokemon(Pokemon, Coordenada);
        aed2::Nat agregarJugador();
        void conectarse(Jugador, Coordenada);
        void desconectarse(Jugador);
        void moverse(Jugador, Coordenada);
        Mapa mapa() const;
        aed2::Conj<Jugador>::const_Iterador jugadores() const;
        bool estaConectado(Jugador) const;
        aed2::Nat sanciones(Jugador) const;
        Coordenada posicion(Jugador) const;
        DiccString<aed2::Nat>::const_Iterador pokemons(Jugador) const;
        aed2::Conj<Jugador> expulsados() const;
        aed2::Conj<Coordenada> posConPokemons() const;
        Pokemon pokemonsEnPos(Coordenada) const;
        aed2::Nat cantidadMovimientosParaCapturar(Coordenada) const;
        bool puedoAgregarPokemon(Coordenada) const;
        bool hayPokemonCercano(Coordenada) const;
        Coordenada posPokemonCercano(Coordenada) const;
        aed2::Conj<Jugador> entrenadoresPosibles(Coordenada) const;
        aed2::Nat indiceRareza(Pokemon) const;
        aed2::Nat cantPokemonsTotales() const;
        aed2::Nat cantMismaEspecie(Pokemon) const;
};

#endif // JUEGO_H
