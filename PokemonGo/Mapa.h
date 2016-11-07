#ifndef MAPA
#define MAPA

#include <string>
#include <ostream>
#include <iostream>
#include <Coordenada.h>
#include <aed2/Conj.h>
#include <aed2/Lista.h>

class Mapa {

  private:

    aed2::Nat latitudMax;
    aed2::Nat longitudMax;
    //aed2::Conj<Coordenada> coordenadasMapa;
    aed2::Lista<aed2::Nat> caminos;
    aed2::Nat marca;


  public:

  // Constructor y destructor
    Mapa();
    ~Mapa();


  // Generadores
    void crearMapa();
    void agregarCoor(Coordenada);

  // Observadores básicos
    //aed2::Conj<Coordenada> coordenadas();

  // Otras operaciones
    bool posExistente(Coordenada);
    bool hayCamino(Coordenada, Coordenada);
    aed2::Nat maximaLatitud();
    aed2::Nat maximaLongitud();
    aed2::Nat pos(Coordenada);
    aed2::Lista<Coordenada> vecinos(Coordenada);
    void pintarVecinos(aed2::Nat, aed2::Nat);

};


#endif // MAPA

