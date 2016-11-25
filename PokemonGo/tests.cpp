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
    Coordenada c;
    Coordenada d;
    Coordenada e;
    e.crearCoor(2,4);
    d.crearCoor(2,5);
    c.crearCoor(1,1);
    m.agregarCoor(c);
    m.agregarCoor(d);
    m.agregarCoor(e);
    ASSERT(m.hayCamino(e,d));

}

void test_cola_destructor(){
    ColaPrior<int> nico;
    nico.Vacia();
    nico.Encolar(1);
    nico.Encolar(2);
    nico.Encolar(3);
    nico.Encolar(4);
    nico.Encolar(10);
    nico.Encolar(12);
    nico.Encolar(15);
    nico.Encolar(5);

    /*
    nico.Encolar(20);
    nico.Encolar(40);
    nico.Encolar(50);
    nico.Encolar(60);
    nico.Encolar(80);
    nico.Encolar(90);
    nico.Encolar(100);
    nico.Encolar(120);
    nico.Encolar(150);
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();
    nico.Desencolar();*/
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
    //driverTest.agregarPokemon(poke3, d);
    driverTest.agregarPokemon(poke4, f);
    // Veo si la cantidad total y la cantidad de cada especie son correctas
    ASSERT(driverTest.cantPokemonsTotales() == 4 );
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
    ASSERT(driverTest.pokemons(3).CantClaves() == 1);
    ASSERT(driverTest.pokemons(4).CantClaves() == 0);
}

void test_cola_copia(){
    ColaPrior<int> nico;
    nico.Vacia();
    nico.Encolar(1);
    nico.Encolar(2);
    nico.Encolar(6);
    ASSERT(nico.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 2);
    ASSERT(nico.Desencolar() == 6);
    nico.Encolar(1);
    nico.Encolar(2);
    nico.Encolar(3);
    ColaPrior<int> pedro = ColaPrior<int>(nico);
    ASSERT(pedro.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 1);
    ASSERT(nico.Desencolar() == 2);
    ASSERT(nico.Desencolar() == 3);
    ASSERT(pedro.Desencolar() == 2);
    ASSERT(pedro.Desencolar() == 3);

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
    driverTest.agregarJugador();
    driverTest.conectarse(0, b);
    driverTest.conectarse(1, c);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);
    driverTest.agregarPokemon(charmander, c);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 1);
    driverTest.moverse(0,c);
    ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 0);
    ASSERT(driverTest.entrenadoresPosibles(c).Cardinal() == 2);
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
    Coordenada k;
    Coordenada l;
    Coordenada m;
    Coordenada n;
    Coordenada o;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    d.crearCoor(0,9);
    e.crearCoor(0,17);
    f.crearCoor(0,18);
    g.crearCoor(0,19);
    h.crearCoor(15,1);
    i.crearCoor(15,2);
    j.crearCoor(0,2);
    k.crearCoor(0,3);
    l.crearCoor(0,4);
    m.crearCoor(0,5);
    n.crearCoor(0,6);
    o.crearCoor(0,7);
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
    cc.Agregar(k);
    cc.Agregar(l);
    cc.Agregar(m);
    cc.Agregar(n);
    cc.Agregar(o);
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
    driverTest.pokemons(0);
    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    ASSERT(driverTest.pokemons(1).CantClaves() == 1);
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);

    /* ESTA PARTE ES LA QUE FALLA SI DEJO EL DESTRUCTOR ANDANDO, Y AGREGO UN POKEMON Y HAY ALGUN JUGADOR CERCA
     * VER LA OPERACION AGREGAR POKEMON, EN LA PARTE DEL CODIGO COMENTADA LO QUE ESTA PASANDO ES QUE SE ME ESTA DESTRUYENDO
     * EL DICCIONARIO DE LOS POKEMONS ATRAPADOS POR EL JUGADOR, NO SE PORQUE PASA ESTO
    */

    //driverTest.moverse(0,c);
    driverTest.agregarPokemon(squirtle, a);
   // driverTest.moverse(0,b);
    //ASSERT(driverTest.entrenadoresPosibles(a).Cardinal() == 1);



    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    // AGREGO UN POKEMON PARA QUE PUEDA SER ATRAPADO POR EL JUGADOR 0
    // GENERO LOS MOVIMIENTOS PARA LA CAPTURA
   /* driverTest.moverse(2, i);
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
    ASSERT(driverTest.pokemons(2).CantClaves() == 0);*/
}

void test_sanciones(){
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
    driverTest.conectarse(0, a);
    ASSERT(driverTest.sanciones(0) == 0);
    // Movimiento que sanciona
    driverTest.moverse(0, f);
    ASSERT(driverTest.sanciones(0) == 1);
    driverTest.moverse(0, f);
    ASSERT(driverTest.sanciones(0) == 2);
    driverTest.moverse(0, f);
    ASSERT(driverTest.sanciones(0) == 3);
    driverTest.moverse(0, f);
    ASSERT(driverTest.sanciones(0) == 4);

}

void test_posicion(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,8);
    d.crearCoor(0,9);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    Driver driverTest(cc);
    driverTest.agregarJugador();
    driverTest.conectarse(0,a);
    ASSERT(driverTest.posicion(0) == a);
    driverTest.moverse(0, c);
    ASSERT(driverTest.posicion(0) == c);
    driverTest.desconectarse(0);
    driverTest.conectarse(0,b);
    ASSERT(driverTest.posicion(0) == b);
}


void test_puedo_agregar_pokemon(){
    aed2::Conj<Coordenada> cc;
    aed2::String pikachu = "Pikachu";
    Coordenada a(0,0);
    Coordenada b(0,1);
    Coordenada c(0,2);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    Driver driverTest(cc);
    driverTest.agregarPokemon(pikachu, a);
    driverTest.puedoAgregarPokemon(b);
    ASSERT(!driverTest.puedoAgregarPokemon(b));

}

void test_dicc_copia(){
    DiccString<int> dicc1;
    DiccString<int> dicc2;
    dicc1.vacio();
    dicc1.Definir("nico", 1);
    dicc1.Definir("nicolas", 2);
    ASSERT(dicc1.Obtener("nico") == 1);
    ASSERT(dicc1.Obtener("nicolas") == 2);
    dicc2 = dicc1;
    ASSERT(dicc2.Obtener("nico") == 1);
    ASSERT(dicc2.Obtener("nicolas") == 2);
    dicc2.Definir("nico", 4);
    dicc2.Definir("ni", 10);
    ASSERT(dicc1.Obtener("nico") == 1);
    ASSERT(dicc2.Obtener("nico") == 4);
    ASSERT(dicc2.Obtener("ni") == 10);
    ASSERT(!dicc1.Definido("ni"));

}

void test_agregar_pokemon_falla(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Pokemon pikachu = "pikachu";
    Pokemon charmander = "charmander";
    a.crearCoor(0,0);
    b.crearCoor(5,3);
    c.crearCoor(10,8);
    d.crearCoor(10,9);
    e.crearCoor(60,9);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    Driver driverTest(cc);
    driverTest.agregarJugador();
    driverTest.agregarPokemon(pikachu,b);
    driverTest.agregarPokemon(charmander,a);
    driverTest.agregarPokemon(charmander,c);
    driverTest.agregarPokemon(charmander,e);
    ASSERT(!driverTest.puedoAgregarPokemon(b));
    ASSERT(!driverTest.puedoAgregarPokemon(d));
}

void test_catedra(){
    Conj<Coordenada> cc;
    cc.Agregar(Coordenada(0,0));
    cc.Agregar(Coordenada(0,1));
    cc.Agregar(Coordenada(0,2));
    cc.Agregar(Coordenada(1,2));
    cc.Agregar(Coordenada(1,4));
    cc.Agregar(Coordenada(4,3));
    cc.Agregar(Coordenada(4,4));
    cc.Agregar(Coordenada(10,0));
    Driver driverTest(cc);
}


void test_pokemon_posicion(){
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
    //driverTest.agregarPokemon(poke3, d);
    driverTest.agregarPokemon(poke4, f);
    // Veo si la cantidad total y la cantidad de cada especie son correctas
    ASSERT(driverTest.pokemonEnPos(a) == poke );
    ASSERT(driverTest.pokemonEnPos(b) == poke1);
    ASSERT(driverTest.pokemonEnPos(c) == poke2 );
    ASSERT(driverTest.pokemonEnPos(f) == poke4 );
}

void test_nico(){
    aed2::Conj<Coordenada> cc;
    Coordenada a;
    Coordenada b;
    Coordenada c;
    Coordenada d;
    Coordenada e;
    Coordenada f;
    Coordenada g;
    a.crearCoor(0,0);
    b.crearCoor(0,10);
    c.crearCoor(0,20);
    d.crearCoor(1,6);
    e.crearCoor(10,0);
    f.crearCoor(1,40);
    g.crearCoor(1,41);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    cc.Agregar(e);
    cc.Agregar(f);
    cc.Agregar(g);
    Driver driverTest(cc);
    Pokemon poke = "pikachu";
    Pokemon poke1 = "squirtle";
    Pokemon poke2 = "pikachu";
    driverTest.agregarPokemon(poke, a);
    driverTest.agregarPokemon(poke1, b);
    driverTest.agregarPokemon(poke2, c);
    driverTest.agregarJugador();
    ASSERT(driverTest.cantMovimientosParaCaptura(a) == 0);
    ASSERT(driverTest.cantMovimientosParaCaptura(b) == 0);
    ASSERT(driverTest.cantMovimientosParaCaptura(c) == 0);
    driverTest.conectarse(0, f);
    driverTest.moverse(0, g);
    driverTest.moverse(0, f);
    driverTest.moverse(0, g);
    driverTest.moverse(0, f);
    driverTest.moverse(0, g);
    driverTest.moverse(0, f);
    driverTest.moverse(0, g);
    driverTest.moverse(0, f);
    driverTest.moverse(0, g);
    driverTest.moverse(0, f);
    ASSERT(driverTest.cantMovimientosParaCaptura(a) == 9);
    ASSERT(driverTest.cantMovimientosParaCaptura(b) == 9);
    ASSERT(driverTest.cantMovimientosParaCaptura(c) == 9);
    ASSERT(driverTest.cantPokemonsTotales() == 3);
}

void test_cantidad(){
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
    a.crearCoor(0,0);
    b.crearCoor(0,10);
    c.crearCoor(0,20);
    d.crearCoor(0,21);
    e.crearCoor(0,40);
    f.crearCoor(0,50);
    g.crearCoor(10,0);
    h.crearCoor(100,40);
    i.crearCoor(100,41);
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
    Pokemon poke = "pikachu";
    Pokemon poke1 = "squirtle";
    Pokemon poke2 = "charmander";
    driverTest.agregarPokemon(poke, a);
    driverTest.agregarPokemon(poke1, b);
    driverTest.agregarPokemon(poke, c);
    driverTest.agregarPokemon(poke, e);
    driverTest.agregarPokemon(poke2, f);
    ASSERT(driverTest.cantPokemonsTotales() == 5)
    ASSERT(driverTest.cantMismaEspecie(poke) == 3)
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1)
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1)
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.conectarse(0,a);
    ASSERT(driverTest.cantPokemonsTotales() == 5)
    ASSERT(driverTest.cantMismaEspecie(poke) == 3)
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1)
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1)
    driverTest.conectarse(1,c);
    driverTest.agregarJugador();
    driverTest.conectarse(2,h);
    ASSERT(driverTest.cantPokemonsTotales() == 5)
    ASSERT(driverTest.cantMismaEspecie(poke) == 3)
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1)
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1)
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    ASSERT(driverTest.cantPokemonsTotales() == 5)
    ASSERT(driverTest.cantMismaEspecie(poke) == 3)
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1)
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1)
    ASSERT(driverTest.posConPokemons().Cardinal() == 3)
    driverTest.agregarPokemon(poke, a);
    ASSERT(driverTest.posConPokemons().Cardinal() == 4)
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    ASSERT(driverTest.posConPokemons().Cardinal() == 3)
    ASSERT(driverTest.pokemons(0).CantClaves() == 1);
    driverTest.agregarPokemon(poke1, a);
    driverTest.posPokemonCercano(a);
    ASSERT(driverTest.posConPokemons().Cardinal() == 4);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    driverTest.moverse(2,i);
    driverTest.moverse(2,h);
    ASSERT(driverTest.posConPokemons().Cardinal() == 3);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2);
    ASSERT(driverTest.cantMismaEspecie(poke) == 4);
    ASSERT(driverTest.cantMismaEspecie(poke1) == 2);
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1);
    driverTest.moverse(0,h);
    driverTest.moverse(0,h);
    driverTest.moverse(0,h);
    driverTest.moverse(0,h);
    ASSERT(driverTest.sanciones(0) == 4);
    ASSERT(driverTest.posConPokemons().Cardinal() == 3);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2);
    ASSERT(driverTest.cantMismaEspecie(poke) == 4);
    ASSERT(driverTest.cantMismaEspecie(poke1) == 2);
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1);
    ASSERT(driverTest.cantPokemonsTotales() == 7);
    driverTest.moverse(0,h);
    ASSERT(driverTest.cantMismaEspecie(poke) == 2);
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1);
    ASSERT(driverTest.cantMismaEspecie(poke2) == 1);
    ASSERT(driverTest.cantPokemonsTotales() == 4);
}

void prueba(){
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
    a.crearCoor(0,0);
    b.crearCoor(0,1);
    c.crearCoor(0,20);
    d.crearCoor(0,21);
    e.crearCoor(0,40);
    f.crearCoor(0,50);
    g.crearCoor(10,0);
    h.crearCoor(100,40);
    i.crearCoor(100,41);
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
    Pokemon poke = "pikachu";
    Pokemon poke1 = "squirtle";
    Pokemon poke2 = "charmander";
    driverTest.agregarJugador();
    driverTest.agregarPokemon(poke, a);
    driverTest.conectarse(0, b);
    driverTest.agregarJugador();
    driverTest.conectarse(1, h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.agregarPokemon(poke1,a);
    ASSERT(driverTest.pokemons(0).CantClaves() == 1)
    driverTest.conectarse(1, h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    driverTest.moverse(1,i);
    driverTest.moverse(1,h);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2)
    driverTest.agregarPokemon(poke1,a);
    ASSERT(driverTest.pokemons(0).CantClaves() == 2)
}

void test_nico1(){
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
    a.crearCoor(0,0);
    b.crearCoor(12,0);
    c.crearCoor(120,2);
    d.crearCoor(120,3);
    cc.Agregar(a);
    cc.Agregar(b);
    cc.Agregar(c);
    cc.Agregar(d);
    Driver driverTest(cc);
    Pokemon poke = "squirtle";
    Pokemon poke1 = "ratata";
    Pokemon poke2 = "squirtle";
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarJugador();
    driverTest.agregarPokemon(poke,a);
    driverTest.agregarPokemon(poke1,b);
    driverTest.agregarPokemon(poke2,c);
    driverTest.conectarse(0,b);
    driverTest.conectarse(1,a);
    driverTest.conectarse(2,c);
    //ASSERT(driverTest.cantMismaEspecie(poke) == 2);
    //ASSERT(driverTest.cantMismaEspecie(poke1) == 1);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    driverTest.moverse(2,d);
    driverTest.moverse(2,c);
    //ASSERT(driverTest.cantMismaEspecie(poke) == 2);
    //ASSERT(driverTest.cantMismaEspecie(poke1) == 1);
    driverTest.moverse(0,c);
    driverTest.moverse(0,c);
    driverTest.moverse(0,c);
    driverTest.moverse(0,c);
    //ASSERT(driverTest.cantMismaEspecie(poke) == 2);
    //ASSERT(driverTest.cantMismaEspecie(poke1) == 1);
    driverTest.moverse(0,c);
   /* ASSERT(driverTest.cantMismaEspecie(poke) == 1);
    ASSERT(driverTest.cantMismaEspecie(poke1) == 1);
*/
}

void test_dicc_destructor(){
    DiccString<int> nico;
    nico.vacio();
    nico.Definir("asd",1);
    nico.Definir("asdsad",1);
    nico.Definir("awqesd",1);
    nico.Definir("asretd",1);
    //nico.Borrar("asd");
    //nico.Definir("nico",2);
}

int main(int argc, char **argv)
{
    // TESTS DESTRUCTORES
    /*
    */
    /*
    RUN_TEST(test_coordenada_destructor);
    RUN_TEST(test_mapa_destructor);
    RUN_TEST(test_dicc_copia)
    RUN_TEST(test_cola_destructor);
    RUN_TEST(test_pokemon_posicion);
    // TESTS JUEGO
    RUN_TEST(test_agregar_pokemones);
    RUN_TEST(test_agregar_jugadores);
    RUN_TEST(test_conectarse_desconectarse);
    RUN_TEST(test_jugador_pokemon_cercano);
    RUN_TEST(test_salir_zona_pokemon);
    RUN_TEST(test_posicion);
    RUN_TEST(test_cola_copia);
    RUN_TEST(test_puedo_agregar_pokemon);
    RUN_TEST(test_sancionar_bannear);
    RUN_TEST(test_constructor_con_mapa);
    RUN_TEST(test_bannear_eliminar_pokemons);
    //RUN_TEST(test_moverse);


    RUN_TEST(test_catedra);
    RUN_TEST(test_sanciones);
    RUN_TEST(test_nico);

    // TESTEAR CANTIDAD DE POKEMONS
    RUN_TEST(test_atrapa_el_de_menos);
    RUN_TEST(test_cantidad);
    RUN_TEST(test_agregar_pokemon_falla);
    RUN_TEST(prueba);
    */

    RUN_TEST(test_dicc_destructor);
    RUN_TEST(test_nico1);

    return 0;
}
