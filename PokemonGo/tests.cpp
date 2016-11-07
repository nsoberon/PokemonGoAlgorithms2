#include <iostream>
#include "mini_test.h"

#include "Mapa.h"
#include "Coordenada.h"

// Tests Coordenada
void test_coordenada_lat_long() {
    Coordenada a;
    a.crearCoor(1,5);
    ASSERT(a.latitud() == 1)
    ASSERT(a.longitud() == 5)
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
    //m.coordenadas();
    ASSERT(true);
}

int main() {
    // Tests Coordenada
    RUN_TEST(test_coordenada_lat_long);
    RUN_TEST(test_coordenada_vecinos);
    RUN_TEST(test_coordenada_distancia);
    // Tests Mapa
    RUN_TEST(test_mapa_vacio);
	return 0;

}
