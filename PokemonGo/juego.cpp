#include "Juego.h"


void Juego::crearJuego(Mapa m){

}
void Juego::agregarPokemon(Pokemon p, Coordenada c){

}
void Juego::agregarJugador(Jugador j){

}

void Juego::conectarse(Jugador j, Coordenada c){

}

void Juego::desconectarse(Jugador j){

}

void Juego::moverse(Jugador j, Coordenada c){

}

Mapa Juego::mapa(){
    return this->mapaJuego;
}

aed2::Conj<Jugador> Juego::jugadores(){
    return this->jugadoresAgregados;
}

bool Juego::estaConectado(Jugador j){

}

aed2::Nat Juego::sanciones(Jugador j){

}

Coordenada Juego::posicion(Jugador j){

}

// Falta pokemons que devuelve el iterador

aed2::Conj<Jugador> Juego::expulsados(){

}

aed2::Conj<Coordenada> Juego::posConPokemons(){

}

Pokemon Juego::pokemonsEnPos(Coordenada c){

}

aed2::Nat Juego::cantidadMovimientosParaCapturar(Coordenada c){

}

bool Juego::puedoAgregarPokemon(Coordenada c){

}

bool Juego::hayPokemonCercano(Coordenada c){

}

Coordenada Juego::posPokemonCercano(Coordenada c){

}

aed2::Conj<Jugador> Juego::entrenadoresPosibles(Coordenada c, aed2::Conj<Jugador> ju){

}

aed2::Nat Juego::indiceRareza(Pokemon p){

}

aed2::Nat Juego::cantPokemonsTotales(){
    this->cantidadTotalPokemons;
}

aed2::Nat Juego::cantMismaEspecie(Pokemon p){

}
