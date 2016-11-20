#include "Mapa.h"
#include <iostream>
using namespace std;

Mapa::Mapa(){

}

Mapa::~Mapa(){
    this->EliminarMapa();
}

void Mapa::EliminarMapa(){

}

void Mapa::crearMapa(){
    aed2::Arreglo<aed2::Arreglo<aed2::Nat>>* matriz = new aed2::Arreglo<aed2::Arreglo<aed2::Nat>>(1);
    aed2::Arreglo<aed2::Nat>* matrizY = new aed2::Arreglo<aed2::Nat>(1) ;
    aed2::Conj<Coordenada>* coordenadas = new aed2::Conj<Coordenada>;
    matrizY->Definir(0,0);
    matriz->Definir(0,*matrizY);
    this->coordenadasM = *coordenadas;
    this->latitudMax = 0;
    this->longitudMax = 0;
    this->matrizCaminos = *matriz;
    this->marca = 1;
    }

void Mapa::agregarCoor(Coordenada c){
    bool cambioLatitud = false;
    bool cambioLongitud = false;
    aed2::Nat latitudAnterior = this->latitudMax;
    aed2::Nat longitudAnterior = this->longitudMax;
    if(c.latitud() > latitudAnterior){
        this->latitudMax = c.latitud();
        cambioLatitud = true;
    }
    if(c.longitud() > longitudAnterior){
        this->longitudMax = c.longitud();
        cambioLongitud = true;
    }
    if(cambioLongitud){
        this->matrizCaminos.Redimensionar(c.longitud() + 1);
        if(cambioLatitud){
            int j = 0;
            while(j <= longitudAnterior){
                this->matrizCaminos[j].Redimensionar(c.latitud() + 1);
                this->matrizCaminos[j].Definir(c.latitud(), 0);
                j++;
            }
        }
        aed2::Arreglo<aed2::Nat>* nuevoArreglo = new aed2::Arreglo<aed2::Nat>(this->matrizCaminos[0].Tamanho() + 1);
        int k = 0;
        while(k < nuevoArreglo->Tamanho()){
            nuevoArreglo->Definir(k,0);
            k++;
        }
        this->matrizCaminos.Definir(c.longitud(), *nuevoArreglo);
        aed2::Nat i = longitudAnterior + 1;
        while(i < this->matrizCaminos.Tamanho()){
            if(i != c.longitud()){
                if(!this->matrizCaminos.Definido(i)){
                    this->matrizCaminos.Definir(i, *nuevoArreglo);
                }else{
                    this->matrizCaminos[i] = *nuevoArreglo;
                }
            }
            i++;
        }
    }else{
        if(cambioLatitud){
            int j = 0;
            while(j < this->longitudMax){
                this->matrizCaminos[j].Redimensionar(c.latitud() + 1);
                j++;
            }
        }else{
            if(!this->matrizCaminos[c.longitud()].Definido(c.latitud())){
                this->matrizCaminos[c.longitud()].Definir(c.latitud(), 0);
            }else{
                this->matrizCaminos[c.longitud()][c.latitud()] = 0;
            }
        }
    }
    for(int i = 0; i < this->matrizCaminos.Tamanho(); i ++){
        for(int j = 0; j < this->matrizCaminos[i].Tamanho(); j++){
            if(!this->matrizCaminos[i].Definido(j)){
                this->matrizCaminos[i].Definir(j,0);
            }
        }
    }
    aed2::Arreglo<aed2::Nat> vecinosCoor = this->vecinos(c);
    if(vecinosCoor.Tamanho() == 0){
        this->matrizCaminos[c.longitud()][c.latitud()] = this->marca;
        this->marca ++;
    }else if(vecinosCoor.Tamanho() == 1){
        //aed2::Nat nico1 = vecinosCoor[0];
        this->matrizCaminos[c.longitud()][c.latitud()] = vecinosCoor[0];
    }else{
        this->marcarVecinos(vecinosCoor[0], vecinosCoor);
        this->matrizCaminos[c.longitud()][c.latitud()] = vecinosCoor[0];
    }
    aed2::Nat nico = this->matrizCaminos[c.longitud()][c.latitud()];
    this->coordenadasM.Agregar(c);
}


aed2::Conj<Coordenada> Mapa::coordenadas(){
    return this->coordenadasM;
}

bool Mapa::posExistente(Coordenada c) const{
    bool res = false;
    aed2::Conj<Coordenada>::const_Iterador itConj = this->coordenadasM.CrearIt();
    while(itConj.HaySiguiente()){
        if(itConj.Siguiente() == c){
            res = true;
        }
        itConj.Avanzar();
    }
    return res;
}

bool Mapa::hayCamino(Coordenada c, Coordenada c1) const{
    assert(this->posExistente(c) && this->posExistente(c1));
    return this->matrizCaminos[c.longitud()][c.latitud()] == this->matrizCaminos[c1.longitud()][c1.latitud()];
}

aed2::Nat Mapa::maximaLatitud(){
    return this->latitudMax;
}

aed2::Nat Mapa::maximaLongitud(){
    return this->longitudMax;
}


aed2::Arreglo<aed2::Nat> Mapa::vecinos(Coordenada c){
    aed2::Lista<Coordenada> vecinos;
    if(this->posExistente(c.coordenadaArriba())){
        vecinos.AgregarAtras(c.coordenadaArriba());
    }
    if(this->posExistente(c.coordenadaAbajo())){
        vecinos.AgregarAtras(c.coordenadaAbajo());
    }
    if(this->posExistente(c.coordenadaALaDerecha())){
        vecinos.AgregarAtras(c.coordenadaALaDerecha());
    }
    if(this->posExistente(c.coordenadaALaIzquierda())){
        vecinos.AgregarAtras(c.coordenadaALaIzquierda());
    }
    aed2::Arreglo<aed2::Nat>* res = new aed2::Arreglo<aed2::Nat> (vecinos.Longitud());
    aed2::Lista<Coordenada>::Iterador itVecinos = vecinos.CrearIt();
    aed2::Nat i = 0;
    while(itVecinos.HaySiguiente()){
        aed2::Nat lat = itVecinos.Siguiente().latitud();
        aed2::Nat lon = itVecinos.Siguiente().longitud();
        res->Definir(i, this->matrizCaminos[lon][lat]);
        itVecinos.Avanzar();
        i++;
    }
    return *res;

}

void Mapa::marcarVecinos(aed2::Nat color, aed2::Arreglo<aed2::Nat> pinto){
    Coordenada c;
    for(int i = 0; i < this->matrizCaminos.Tamanho(); i++){
        for(int j = 0; j < this->matrizCaminos[i].Tamanho(); j++){
            c.crearCoor(j,i);
            if(this->posExistente(c)){
                aed2::Nat elem = this->matrizCaminos[i][j];
                bool esta = false;
                for(int k = 0; k < pinto.Tamanho(); k ++){
                    aed2::Nat bug = pinto[k];
                    if(pinto[k] == elem){
                        esta = true;
                        break;
                    }
                }
                if(esta && elem != color){
                    this->matrizCaminos[i][j] = color;
                }
            }
        }
    }
}

bool Mapa::operator == (const Mapa& m) const{
    bool res = true;
    res = res && (this->latitudMax == m.latitudMax);
    res = res && (this->longitudMax == m.longitudMax);
    res = res && (this->marca == m.marca);
    res = res && (this->coordenadasM == m.coordenadasM);
}


// BORRAR ES PARA TEST

aed2::Arreglo<aed2::Arreglo<aed2::Nat>> Mapa::verMatriz(){
    return this->matrizCaminos;
}
