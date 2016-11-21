#include "Coordenada.h"

Coordenada::Coordenada(){
    this->latitudC = 0;
    this->longitudC = 0;
}

Coordenada::~Coordenada(){
}

void Coordenada::crearCoor(aed2::Nat x, aed2::Nat y){
    this->latitudC = x;
    this->longitudC = y;
}

aed2::Nat Coordenada::latitud() const{
    return this->latitudC;
}

aed2::Nat Coordenada::longitud() const{
    return this->longitudC;
}

aed2::Nat Coordenada::distEuclidea(Coordenada c){
    aed2::Nat latC = c.latitud();
    aed2::Nat longC = c.longitud();
    aed2::Nat latD = this->latitud();
    aed2::Nat longD = this->longitud();
    aed2::Nat la;
    aed2::Nat lo;
    if(latC > latD){
        la = latC - latD;
    }else{
        la = latD - latC;
    }
    if(longC > longD){
        lo = longC - longD;
    }else{
        lo = longD - longC;
    }
    return la*la + lo*lo;
}

Coordenada Coordenada::coordenadaArriba(){
    Coordenada res;
    res.crearCoor(this->latitud()+1, this->longitud());
    return res;
}

Coordenada Coordenada::coordenadaAbajo(){
    Coordenada res;
    res.crearCoor(this->latitud()-1, this->longitud());
    return res;
}

Coordenada Coordenada::coordenadaALaDerecha(){
    Coordenada res;
    res.crearCoor(this->latitud(), this->longitud()+1);
    return res;
}

Coordenada Coordenada::coordenadaALaIzquierda(){
    Coordenada res;
    res.crearCoor(this->latitud(), this->longitud()-1);
    return res;
}

bool Coordenada::operator == (const Coordenada& c) const{
    return this->latitud() == c.latitud() && this->longitud() == c.longitud();
}

bool Coordenada::operator != (const Coordenada& c) const{
 return not (*this == c);
}

