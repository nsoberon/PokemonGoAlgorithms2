#ifndef COORDENADA_H
#define COORDENADA_H

#include <string>
#include <ostream>
#include <iostream>

#include "TiposJuego.h"

class Coordenada{

    private:
        aed2::Nat latitudC;
        aed2::Nat longitudC;


    public:

    // Constructor y destructor
      Coordenada();
      ~Coordenada();


    // Generadores
    void crearCoor(aed2::Nat, aed2::Nat);

    // Observadores básicos
    aed2::Nat latitud() const;
    aed2::Nat longitud() const;

    // Otras operaciones
    aed2::Nat distEuclidea(Coordenada);
    Coordenada coordenadaArriba();
    Coordenada coordenadaAbajo();
    Coordenada coordenadaALaDerecha();
    Coordenada coordenadaALaIzquierda();
    bool operator == (const Coordenada & c) const;
    bool operator != (const Coordenada& c) const;
};

#endif // COORDENADA_H
