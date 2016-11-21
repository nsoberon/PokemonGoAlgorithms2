// Compilar usando:
//  g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//  valgrind --leak-check=full ./tests

#include "Driver.h"
#include "mini_test.h"

using namespace aed2;

// TESTS DESTRUCTORES

void test_coordenada_destructor(){
    Coordenada c;
    c.crearCoor(1,1);
}

void test_mapa_destructor(){
    Mapa m;
    m.crearMapa();
}

void test_cola_destructor(){
    ColaPrior<int> nico;
    nico.Vacia();
    nico.Encolar(1);
    nico.Encolar(2);
}

void test_dicc_destructor(){
    DiccString<int> nico;
    nico.vacio();
    nico.Definir("nico",1);
    nico.Claves();
}

// TESTS JUEGO

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
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    ASSERT(!driverTest.estaConectado(0));
    driverTest.conectarse(0, a);
    driverTest.conectarse(1,c);
    driverTest.conectarse(2,b);
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 3)
    ASSERT(driverTest.estaConectado(0));
    driverTest.desconectarse(0);
    ASSERT(!driverTest.estaConectado(0));
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 2)
    driverTest.desconectarse(1);
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 1)
    driverTest.desconectarse(2);
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 0)
}

void test_moverse(){
    aed2::Conj<Coordenada> cc;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    Pokemon squirtle = "squirtle";
    Pokemon bulbasaur = "bulbasaur";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    Coordenada i;
    Coordenada j;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(5,0);
    d.crearCoor(5,1);
    e.crearCoor(10,0);
    f.crearCoor(10,1);
    g.crearCoor(15,0);
    h.crearCoor(15,1);
    i.crearCoor(20,0);
    j.crearCoor(20,1);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    cc.Agregar(g);
    cc.Agregar(h);
    cc.Agregar(i);
    cc.Agregar(j);
    Driver driverTest(cc);
    // Agrego 6 jugadores
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    // Conecto a los jugadores y Agrego Pokemons
    driverTest.conectarse(0,b);
    driverTest.agregarPokemon(pikachu, a);
    aed2::Nat nico = driverTest.cantMovimientosParaCaptura(a);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    driverTest.entrenadoresPosibles(a);
    driverTest.conectarse(1,d);
    driverTest.agregarPokemon(charmander, c);
    driverTest.conectarse(2,f);
    driverTest.agregarPokemon(squirtle, e);
    driverTest.conectarse(5,g);
    driverTest.conectarse(3,h);
    driverTest.agregarPokemon(bulbasaur, g);
    driverTest.conectarse(4,i);
    // Chequeo que para cada pokemon tengo un solo entrenador que puede atraparlo
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    ASSERT(driverTest.entrenadoresPosibles(b).Cardinal() == 1);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 1);
    ASSERT(driverTest.entrenadoresPosibles(d).Cardinal() == 1);
    // Chequeo que ninguno de los jugadores tiene pokemons atrapados
    ASSERT(driverTest.pokemons(0).CantClaves() == 0);
    ASSERT(driverTest.pokemons(1).CantClaves() == 0);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);
    ASSERT(driverTest.pokemons(3).CantClaves() == 0);
    ASSERT(driverTest.pokemons(4).CantClaves() == 0);
    // Genero 10 movimientos externos para que todos atrapen el pokemon que tienen cercano
    driverTest.moverse(4,j);
    driverTest.moverse(4,i);
    driverTest.moverse(4,j);
    driverTest.moverse(4,i);
    driverTest.moverse(4,j);
    driverTest.moverse(4,i);
    driverTest.moverse(4,j);
    driverTest.moverse(4,i);
    driverTest.moverse(4,j);
    driverTest.moverse(4,i);
    // Chequeo que efectivamente se hayan capturado los pokemons
    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    ASSERT(driverTest.pokemons(1).CantClaves() == 1);
    ASSERT(driverTest.pokemons(2).CantClaves() == 1);
    ASSERT(driverTest.pokemons(5).CantClaves() == 1);
    ASSERT(driverTest.pokemons(4).CantClaves() == 0);
}

void test_cola_copia(){
    ColaPrior<int> nico;
    nico.Vacia();
    nico.Encolar(1);
    nico.Encolar(2);
    nico.Encolar(3);
    ASSERT(nico.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 2);
    ASSERT(nico.Desencolar() == 3);
    nico.Encolar(1);
    nico.Encolar(2);
    nico.Encolar(3);
    ColaPrior<int> pedro = ColaPrior<int>(nico);
    ASSERT(pedro.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 2);
    ASSERT(nico.Desencolar() == 3);
    ASSERT(pedro.Desencolar() == 2);
    ColaPrior<int>::Iterador apunta = pedro.Encolar(8);
    apunta.EliminarSiguiente();
}

void test_sancionar_bannear(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    Coordenada i;
    Coordenada j;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(5,0);
    d.crearCoor(5,1);
    e.crearCoor(10,0);
    f.crearCoor(10,1);
    g.crearCoor(15,0);
    h.crearCoor(15,1);
    i.crearCoor(20,0);
    j.crearCoor(20,1);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    cc.Agregar(g);
    cc.Agregar(h);
    cc.Agregar(i);
    cc.Agregar(j);
    Driver driverTest(cc);
    // Agrego 1 jugador
    driverTest.agregarJugador();
    // Conecto los jugadores
    driverTest.conectarse(0,a);
    // Miro las sanciones
    ASSERT(driverTest.sanciones(0) == 0);
    // Hago que lo sancionen
    driverTest.moverse(0,h);
    ASSERT(driverTest.sanciones(0) == 1);
    driverTest.moverse(0,a);
    driverTest.moverse(0,h);
    driverTest.moverse(0,a);
    ASSERT(driverTest.sanciones(0) == 4);
    driverTest.moverse(0,h);
    ASSERT(driverTest.expulsados().Pertenece(0));
}

void test_bannear_eliminar_pokemons(){
    aed2::Conj<Coordenada> cc;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    Pokemon squirtle = "squirtle";
    Pokemon bulbasaur = "bulbasaur";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    Coordenada i;
    Coordenada j;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    d.crearCoor(0,9);
    e.crearCoor(0,17);
    f.crearCoor(0,18);
    g.crearCoor(15,0);
    h.crearCoor(15,1);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    cc.Agregar(g);
    cc.Agregar(h);
    Driver driverTest(cc);
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.conectarse(0, a);
    driverTest.conectarse(1, g);
    driverTest.agregarPokemon(pikachu, a);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    ASSERT(driverTest.cantPokemonsTotales() == 1);
    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    driverTest.moverse(0, c);
    ASSERT(driverTest.posicion(0) == c);
    driverTest.agregarPokemon(charmander,d);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    driverTest.moverse(1, h);
    driverTest.moverse(1, g);
    ASSERT(driverTest.cantPokemonsTotales() == 2);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2);
    driverTest.agregarPokemon(squirtle, a);
    ASSERT(driverTest.cantPokemonsTotales() == 3);
    driverTest.moverse(0, g);
    driverTest.moverse(0, a);
    driverTest.moverse(0, g);
    driverTest.moverse(0, a);
    ASSERT(driverTest.expulsados().Pertenece(0));
    ASSERT(!driverTest.jugadores().Pertenece(0));
    ASSERT(driverTest.cantPokemonsTotales() == 1);
}

void test_jugador_pokemon_cercano(){
    aed2::Conj<Coordenada> cc;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    Driver driverTest(cc);
    driverTest.agregarPokemon(pikachu, a);
    driverTest.agregarJugador();
    driverTest.conectarse(0, b);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    driverTest.agregarPokemon(charmander, c);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 0);
    driverTest.moverse(0,c);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 0);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 1);
}

void test_salir_zona_pokemon(){
    aed2::Conj<Coordenada> cc;
    Pokemon pikachu = "pikachu";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    Driver driverTest(cc);
    driverTest.agregarJugador();
    driverTest.conectarse(0, b);
    driverTest.agregarPokemon(pikachu, a);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    driverTest.moverse(0,c);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 0);
}

void test_atrapa_el_de_menos(){
    aed2::Conj<Coordenada> cc;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    Pokemon squirtle = "squirtle";
    Pokemon bulbasaur = "bulbasaur";
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    Coordenada h;
    Coordenada i;
    Coordenada j;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    d.crearCoor(0,9);
    e.crearCoor(0,17);
    f.crearCoor(0,18);
    g.crearCoor(0,19);
    h.crearCoor(15,1);
    i.crearCoor(15,2);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    cc.Agregar(g);
    cc.Agregar(h);
    cc.Agregar(i);
    Driver driverTest(cc);
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarPokemon(pikachu, a);
    driverTest.agregarPokemon(charmander, c);
    // 0 y 1 van a atrapar pokemons, 2 va a ser el que genere los movimientos para que puedan atraparlos
    driverTest.conectarse(0, b);
    driverTest.conectarse(1, d);
    driverTest.conectarse(2, h);
    // TENGO UN ENTRENADOR EN LA ZONA DE CADA POKEMON
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 1);
    ASSERT(driverTest.pokemons(0).CantClaves() == 0);
    ASSERT(driverTest.pokemons(1).CantClaves() == 0);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);
    // GENERO 10 MOVIMIENTOS EXTERIORES PARA QUE LOS DOS ATRAPEN
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    // CHEQUEO QUE EFECTIVAMENTE LOS DOS ATRAPAN
    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    ASSERT(driverTest.pokemons(1).CantClaves() == 1);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);
    driverTest.agregarPokemon(squirtle, a);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    // AGREGO UN POKEMON PARA QUE PUEDA SER ATRAPADO POR EL JUGADOR 0
    // GENERO LOS MOVIMIENTOS PARA LA CAPTURA
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2);
    ASSERT(driverTest.pokemons(1).CantClaves() == 1);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);
    // PONGO A LOS DOS JUGADORES CERCA DE UN POKEMON PARA QUE LOS DOS ESTEN EN LA ZONA DE CAPTURA
    driverTest.moverse(0, e);
    driverTest.moverse(1, g);
    driverTest.agregarPokemon(bulbasaur, f);
    // TENGO DOS ENTRENADORES EN LA ZONA DEL POKEMON
    ASSERT(driverTest.entrenadoresPosibles(f).Cardinal() == 2);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    driverTest.moverse(2, i);
    driverTest.moverse(2, h);
    // CHEQUEO QUE EFECTIVAMENTE ATRAPA EL QUE TIENE MENOS POKEMONS
    ASSERT(driverTest.pokemons(0).CantClaves() == 2);
    ASSERT(driverTest.pokemons(1).CantClaves() == 2);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);
}


int main(int argc, char **argv)
{
    // TESTS DESTRUCTORES
    /*RUN_TEST(test_coordenada_destructor);
    RUN_TEST(test_mapa_destructor);
    RUN_TEST(test_cola_destructor);
    RUN_TEST(test_dicc_destructor);
    */
    // TESTS JUEGO
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_cola_copia);
    RUN_TEST(test_sancionar_bannear);
    RUN_TEST(test_bannear_eliminar_pokemons);
    RUN_TEST(test_conectarse_desconectarse);
    RUN_TEST(test_moverse);
    RUN_TEST(test_salir_zona_pokemon);
    RUN_TEST(test_jugador_pokemon_cercano);
    RUN_TEST(test_atrapa_el_de_menos);


    // TESTS PARA HACER
    // POKEMONS POSICIONES; QUE CUANDO AGERGO CHEQUEO QUE EL POKEMON DE ESA POSICION SEA ESE
    // JUGADORES POSICION ACTUAL, CHEQUEO LA POSCIION ACTUAL DEL JUGADOR LUEGO DE CONECTARSE Y MOVERSE
    // CHEQUEAR FUNCIONES CHICAS
    // CHEQUEAR CONECTAR DESCONECTAR TENIENDO POKEMONS CERCA
    return 0;
}
