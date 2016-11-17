#include <iostream>
#include "mini_test.h"


#include "Mapa.h"
#include "Coordenada.h"
#include "ColaPrior.hpp"
#include "DiccString.hpp"
#include "Juego.h"

// Tests Estructuras

// Tests DiccString
void test_claves_dicc_vacio() {
    DiccString<int> d;
    ASSERT(d.Claves().Cardinal() == 0);
}


//Chequea el definir y definido
void test_definir_definido() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("hola",5);
    d.Definir("casona",13);
    ASSERT(d.Obtener("hola") == 5);
}

//cheque el obtener
void test_obtener() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    ASSERT( d.Obtener("hola") == 42 );
    ASSERT( d.Obtener("casa") == 22 );
}

//cheque el borrar
void test_borrar() {
    DiccString<int> d;
    d.Definir("hola",42);
    d.Definir("casa",22);
    d.Definir("casa",1);
    ASSERT(d.Claves().Cardinal() == 2);
    d.Borrar("casa");
    ASSERT(d.Claves().Cardinal() == 1);
    d.Borrar("hola");
    ASSERT(d.Claves().Cardinal() == 0);
    ASSERT( !d.Definido("hola") );
    ASSERT(!d.Definido("casa") );
}

// Tests ColaPrior

void test_cola(){
    ColaPrior<int> nico;
    nico.Vacia();
    nico.Encolar(3);
    nico.Encolar(1);
    ASSERT(!nico.EsVacia());
    ASSERT(nico.Desencolar() == 1);
}


// Tests Coordenada
void test_coordenada_lat_long() {
    Coordenada a;
    a.crearCoor(1,5);
    ASSERT(a.latitud() == 1);
    ASSERT(a.longitud() == 5);
}

void test_coordenada_vecinos() {
    Coordenada a;
    a.crearCoor(1,5);
    ASSERT(a.latitud() == 1)
    ASSERT(a.longitud() == 5)
    ASSERT(a.coordenadaAbajo().latitud() == 0)
    ASSERT(a.coordenadaAbajo().longitud()==5)
    ASSERT(a.coordenadaArriba().latitud() == 2)
    ASSERT(a.coordenadaArriba().longitud()==5)
    ASSERT(a.coordenadaALaDerecha().latitud()==1)
    ASSERT(a.coordenadaALaDerecha().longitud() == 6)
    ASSERT(a.coordenadaALaIzquierda().latitud()==1)
    ASSERT(a.coordenadaALaIzquierda().longitud() == 4)
}

void test_coordenada_distancia(){
    Coordenada a;
    Coordenada b;
    a.crearCoor(1,5);
    b.crearCoor(5,10);
    ASSERT(a.distEuclidea(b) == 41);
    ASSERT(a.coordenadaArriba().distEuclidea(b) == 34)
}

// Tests Mapa

void test_mapa_vacio(){
    Mapa m;
    m.crearMapa();
    ASSERT(m.coordenadas().Cardinal() == 0 && m.maximaLongitud() == 0 && m.maximaLatitud() == 0);
}

void test_mapa_agregar_coordenada(){    
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    c.crearCoor(10,2);
    h.crearCoor(10,3);
    d.crearCoor(10,5);    
    e.crearCoor(8,1);
    f.crearCoor(5,5);
    g.crearCoor(0,2);
    Mapa m;
    m.crearMapa();
    m.agregarCoor(c);
    m.agregarCoor(d);
    m.agregarCoor(e);
    m.agregarCoor(f);
    m.agregarCoor(g);
    m.agregarCoor(h);
    ASSERT(m.posExistente(c) && m.posExistente(d) && m.posExistente(e) && m.posExistente(f) && m.posExistente(g) && m.posExistente(h));
}

void test_mapa_hay_camino(){
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    c.crearCoor(1,1);
    d.crearCoor(2,3);
    e.crearCoor(3,3);
    f.crearCoor(0,0);
    g.crearCoor(1,2);
    h.crearCoor(0,1);
    Mapa m;
    m.crearMapa();
    m.agregarCoor(c);
    cout << m.verMatriz()[c.longitud()][c.latitud()] << endl;
    m.agregarCoor(d);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "siguiente paso" << endl;
    m.agregarCoor(e);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "siguiente paso" << endl;
    m.agregarCoor(f);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "siguiente paso" << endl;
    m.agregarCoor(g);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
        cout << "siguiente paso" << endl;
    m.agregarCoor(h);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
    ASSERT(m.hayCamino(f,h) && m.hayCamino(f,c) && m.hayCamino(h, c) && m.hayCamino(f,g) && m.hayCamino(h,g) && m.hayCamino(c,g));
    ASSERT(m.hayCamino(f,h) && m.hayCamino(f,c) && m.hayCamino(h, c) && m.hayCamino(f,g) && m.hayCamino(h,g) && m.hayCamino(c,g));
    ASSERT(m.hayCamino(d,e));
    ASSERT(!m.hayCamino(d,f));
    Coordenada i;
    i.crearCoor(1,3);
        cout << "siguiente paso" << endl;
    m.agregarCoor(i);
    for(int i = 0; i < m.verMatriz().Tamanho(); i ++){
        for(int j = 0; j < m.verMatriz()[i].Tamanho(); j++){
            cout << m.verMatriz()[i][j] << ' ';
        }
        cout << endl;
    }
    ASSERT(m.hayCamino(d,h));
}


// Tests Juego

void test_juego_vacio(){
    Juego j;
    Mapa m;
    j.crearJuego(m);
    ASSERT(j.mapa() == m)
}

void test_juego_agregar_jugador(){
    Juego j;
    aed2::Conj<Jugador>::Iterador it = j.jugadores();
    ASSERT(!it.HaySiguiente())
    j.agregarJugador();
    aed2::Conj<Jugador>::Iterador it1 = j.jugadores();
    ASSERT(it1.HaySiguiente() && it1.Siguiente() == 0);
}

void test_juego_conectar_desconectar(){
    Juego j;
    Jugador nico = 0;
    Mapa m;
    m.crearMapa();
    Coordenada c;
    c.crearCoor(1,1);
    m.agregarCoor(c);
    j.crearJuego(m);
    j.agregarJugador();
    ASSERT(!j.estaConectado(nico));
    j.conectarse(nico,c);
    ASSERT(j.estaConectado(nico));
    j.desconectarse(nico);
    ASSERT(!j.estaConectado(nico));
}

void test_juego_agregar_pokemon(){
    Mapa m;
    m.crearMapa();
    Coordenada d;
    d.crearCoor(10,10);
    Coordenada f;
    f.crearCoor(1,1);
    Coordenada h;
    h.crearCoor(1,2);
    m.agregarCoor(d);
    m.agregarCoor(f);
    m.agregarCoor(h);
    Juego j;
    Coordenada e;
    e.crearCoor(1,2);
    j.crearJuego(m);
    j.agregarJugador();
    j.conectarse(0,e);
    Pokemon p = "pikachu";
    Coordenada c;
    c.crearCoor(1,1);
    j.agregarPokemon(p, c);
    ASSERT(j.cantPokemonsTotales() == 1);
}

int main() {
    // Tests DiccString
    /*RUN_TEST(test_claves_dicc_vacio);
    RUN_TEST(test_definir_definido);
    RUN_TEST(test_obtener);
    RUN_TEST(test_borrar);*/
    // Tests ColaPrior
    RUN_TEST(test_cola);
    // Tests Coordenada
    /*RUN_TEST(test_coordenada_lat_long);
    RUN_TEST(test_coordenada_vecinos);
    RUN_TEST(test_coordenada_distancia);
    // Tests Mapa
    RUN_TEST(test_mapa_vacio);
    RUN_TEST(test_mapa_agregar_coordenada);
    RUN_TEST(test_mapa_hay_camino);*/

    // Tests Juego
    RUN_TEST(test_juego_vacio);
    RUN_TEST(test_juego_agregar_jugador);
    RUN_TEST(test_juego_conectar_desconectar);
    RUN_TEST(test_juego_agregar_pokemon);

    return 0;

}
