#ifndef MAPA
#define MAPA

#include <string>
#include <ostream>
#include <iostream>
#include "Coordenada.h"
#include "aed2/Conj.h"
#include "aed2/Lista.h"

class Mapa {

  private:

    aed2::Nat latitudMax;
    aed2::Nat longitudMax;
    aed2::Conj<Coordenada> coordenadasM;
    aed2::Arreglo<aed2::Arreglo<aed2::Nat> > matrizCaminos;
    aed2::Nat marca;


    aed2::Arreglo<aed2::Nat> vecinos(Coordenada);
    void marcarVecinos(aed2::Nat, aed2::Arreglo<aed2::Nat>);

public:

  // Constructor y destructor
    Mapa();
    ~Mapa();
    void EliminarMapa();

  // Generadores
    void crearMapa();
    void agregarCoor(Coordenada);

  // Observadores básicos
    aed2::Conj<Coordenada> coordenadas();

  // Otras operaciones
    bool posExistente(Coordenada) const;
    bool hayCamino(Coordenada, Coordenada) const;
    aed2::Nat maximaLatitud();
    aed2::Nat maximaLongitud();

    // BORRAR ES SOLO PARA TEST
    aed2::Arreglo<aed2::Arreglo<aed2::Nat> > verMatriz();
    // BORRAR ES SOLO PARA TEST

    bool operator == (const Mapa & m) const;
};


#endif // MAPA
