// Compilar usando:
//  g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//  valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_con_mapa() {
  aed2::Conj<Coordenada> cc;
  Coordenada a;
  Coordenada b;
  Coordenada c;
  Coordenada d;
  Coordenada e;
  Coordenada f;
  a.crearCoor(0,0);
  b.crearCoor(0,1);
  c.crearCoor(0,2);
  d.crearCoor(1,2);
  e.crearCoor(10,0);
  f.crearCoor(1,4);
  cc.Agregar(a);
  cc.Agregar(b);
  cc.Agregar(c);
  cc.Agregar(d);
  cc.Agregar(e);
  cc.Agregar(f);
  Driver driverTest(cc);
  ASSERT( driverTest.mapa() == cc );
}


void test_agregar_jugadores(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,2);
    d.crearCoor(1,2);
    e.crearCoor(10,0);
    f.crearCoor(1,4);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    Driver driverTest(cc);
    Conj<Jugador> jugadores;
    jugadores.Agregar(0);
    jugadores.Agregar(1);
    jugadores.Agregar(2);
    jugadores.Agregar(3);
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    ASSERT(driverTest.jugadores() == jugadores);
}

void test_agregar_pokemones(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    a.crearCoor(0,0);
    b.crearCoor(0,10);
    c.crearCoor(0,20);
    d.crearCoor(1,6);
    e.crearCoor(10,0);
    f.crearCoor(1,40);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    Driver driverTest(cc);
    Pokemon poke = "pikachu";
    Pokemon poke1 = "squirtle";
    Pokemon poke2 = "pikachu";
    Pokemon poke3 = "charmander";
    Pokemon poke4 = "charmander";
    driverTest.agregarPokemon(poke, a);
    driverTest.agregarPokemon(poke1, b);
    driverTest.agregarPokemon(poke2, c);
    driverTest.agregarPokemon(poke3, d);
    driverTest.agregarPokemon(poke4, f);
    // Veo si la cantidad total y la cantidad de cada especie son correctas
    ASSERT(driverTest.cantPokemonsTotales() == 5 && driverTest.cantMismaEspecie(poke) == 2 && driverTest.cantMismaEspecie(poke1) == 1 && driverTest.cantMismaEspecie(poke2) == 2 && driverTest.cantMismaEspecie(poke3) == 2);
}

void test_conectarse_desconectarse(){
    aed2::Conj<Coordenada> cc;
    Pokemon p = "pikachu";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,2);
    d.crearCoor(1,2);
    e.crearCoor(10,0);
    f.crearCoor(1,4);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    Driver driverTest(cc);
    driverTest.agregarPokemon(p, b);
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 0)
    driverTest.agregarJugador();
    ASSERT(!driverTest.estaConectado(0));
    driverTest.conectarse(0, a);
    //aed2::Nat nico = driverTest.entrenadoresPosibles(b).Cardinal();
    //aed2::Nat nico1 = driverTest.entrenadoresPosibles(b).Cardinal();
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 1)
    ASSERT(driverTest.estaConectado(0));
    //driverTest.desconectarse(0);
    //ASSERT(!driverTest.estaConectado(0));
}


int main(int argc, char **argv)
{
  /*RUN_TEST(test_constructor_con_mapa);
  RUN_TEST(test_agregar_jugadores);
  RUN_TEST(test_agregar_pokemones);*/
  RUN_TEST(test_conectarse_desconectarse);


  return 0;
}
