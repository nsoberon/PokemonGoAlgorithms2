#include "Mapa.h"
#include <iostream>
using namespace std;

Mapa::Mapa(){

}

Mapa::~Mapa(){

}

void Mapa::crearMapa(){
    // Inicializa un mapa vacio
    aed2::Arreglo<aed2::Arreglo<aed2::Nat> >(1);
    aed2::Arreglo<aed2::Arreglo<aed2::Nat> > matriz = aed2::Arreglo<aed2::Arreglo<aed2::Nat> >(1);
    matriz.Definir(0,aed2::Arreglo<aed2::Nat>(1));
    this->latitudMax = 0;
    this->longitudMax = 0;
    this->matrizCaminos = matriz;
    this->marca = 1;
    }

void Mapa::agregarCoor(Coordenada c){
    // Chequea si cambia la latitud y longitud maxima
    // En caso de que cambie guarda los nuevos valores
    bool cambioLatitud = false;
    bool cambioLongitud = false;
    if(c.latitud() > this->latitudMax){
        this->latitudMax = c.latitud();
        cambioLatitud = true;
    }
    if(c.longitud() > this->longitudMax){
        this->longitudMax = c.longitud();
        cambioLongitud = true;
    }
    // Si cambio latitud o longitud, redimensiona la matriz de caminos del mapa
    if(cambioLongitud){
        this->matrizCaminos.Redimensionar(c.longitud() + 1);
        if(cambioLatitud){
            aed2::Nat j = 0;
            while(j < this->matrizCaminos.Tamanho()){
                if(this->matrizCaminos.Definido(j)){
                    this->matrizCaminos[j].Redimensionar(c.latitud() + 1);
                }else{
                    aed2::Arreglo<aed2::Nat> nuevoArreglo(c.latitud() + 1);
                    this->matrizCaminos.Definir(j, nuevoArreglo);
                }
                j++;
            }
        }else{
            aed2::Nat j = 0;
            while(j < this->matrizCaminos.Tamanho()){
                if(!this->matrizCaminos.Definido(j)){
                    aed2::Arreglo<aed2::Nat> nuevoArreglo(this->latitudMax + 1);
                    this->matrizCaminos.Definir(j, nuevoArreglo);
                }
                j++;
            }
        }
    }else{
        if(cambioLatitud){
            aed2::Nat j = 0;
            while(j < this->matrizCaminos.Tamanho()){
                this->matrizCaminos[j].Redimensionar(c.latitud() + 1);
                j++;
            }
        }
    }
    // Todas las posiciones de la matriz que no estan definidas, las define con un 0
    for(aed2::Nat i = 0; i < this->matrizCaminos.Tamanho(); i ++){
        for(aed2::Nat j = 0; j < this->matrizCaminos[i].Tamanho(); j++){
            if(!this->matrizCaminos[i].Definido(j)){
                this->matrizCaminos[i].Definir(j,0);
            }
        }
    }
    // Mira si la coordenada que agrego tiene vecinos
    // En caso de que tenga, forma las clases de equivalencia teniendo en cuenta la nueva coordenada
    aed2::Arreglo<aed2::Nat> vecinosCoor = this->vecinos(c);
    if(vecinosCoor.Tamanho() == 0){
        this->matrizCaminos[c.longitud()][c.latitud()] = this->marca;
        this->marca ++;
    }else if(vecinosCoor.Tamanho() == 1){
        this->matrizCaminos[c.longitud()][c.latitud()] = vecinosCoor[0];
    }else{
        this->marcarVecinos(vecinosCoor[0], vecinosCoor);
        this->matrizCaminos[c.longitud()][c.latitud()] = vecinosCoor[0];
    }
    // Agrega la coordenada  a las coordenadas del mapa
    this->coordenadasM.Agregar(c);
}


aed2::Conj<Coordenada> Mapa::coordenadas(){
    return this->coordenadasM;
}

bool Mapa::posExistente(Coordenada c) const{
    bool res = false;
    // Recorre todas las coordenadas del mapa y se fija si esta c
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
    // Mira si las dos coordenadas pertenecen a la misma clase de equivalencia
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
    // Mira las 4 coordenadas vecinas, y se fija si son posiciones existentes del mapa
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
    aed2::Arreglo<aed2::Nat> res = aed2::Arreglo<aed2::Nat> (vecinos.Longitud());
    aed2::Lista<Coordenada>::Iterador itVecinos = vecinos.CrearIt();
    aed2::Nat i = 0;
    // Crea un arreglo con los vecinos de la coordenada
    while(itVecinos.HaySiguiente()){
        aed2::Nat lat = itVecinos.Siguiente().latitud();
        aed2::Nat lon = itVecinos.Siguiente().longitud();
        res.Definir(i, this->matrizCaminos[lon][lat]);
        itVecinos.Avanzar();
        i++;
    }
    return res;

}

void Mapa::marcarVecinos(aed2::Nat color, aed2::Arreglo<aed2::Nat> pinto){
    Coordenada c;
    // Recorre todas las posiciones de la matriz de caminos del mapa
    // Marca las que son iguales a "pinto" con "color"
    for(aed2::Nat i = 0; i < this->matrizCaminos.Tamanho(); i++){
        for(aed2::Nat j = 0; j < this->matrizCaminos[i].Tamanho(); j++){
            c.crearCoor(j,i);
            if(this->posExistente(c)){
                aed2::Nat elem = this->matrizCaminos[i][j];
                bool esta = false;
                for(aed2::Nat k = 0; k < pinto.Tamanho(); k ++){
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
    return res;
}


// BORRAR ES PARA TEST

aed2::Arreglo<aed2::Arreglo<aed2::Nat> > Mapa::verMatriz(){
    return this->matrizCaminos;
}
