// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"

using namespace aed2;

void test_constructor_con_mapa() {
  Conj<Coordenada> cc;
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
  //Driver d(cc);
  //ASSERT( d.mapa() == cc );
}


void test_agregar_jugadores(){
	ASSERT( false );
}

void test_agregar_pokemones(){
	ASSERT( false );
}

void test_nico(){
    ColaPrior<int> nico;
    nico.Encolar(20);
    ColaPrior<int>::Iterador itNico = nico.CrearIterador(nico.Encolar(1).Siguiente());
    itNico.EliminarSiguiente();
    ASSERT(nico.Proximo() == 20);
}

// TODO: Agregar más tests


int main(int argc, char **argv)
{
  RUN_TEST(test_constructor_con_mapa);
  RUN_TEST(test_agregar_jugadores);
  RUN_TEST(test_agregar_pokemones);
  //RUN_TEST(test_nico);
  
  return 0;
}
