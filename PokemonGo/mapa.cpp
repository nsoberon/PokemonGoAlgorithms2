#include "Mapa.h"


Mapa::Mapa(){

}

Mapa::~Mapa(){

}

void Mapa::crearMapa(){
    aed2::Lista<aed2::Nat> caminos;
    this->latitudMax = 0;
    this->longitudMax = 0;
    this->caminos = caminos;
    this->marca = 0;
    }

void Mapa::agregarCoor(Coordenada c){
    aed2::Nat latVieja = this->latitudMax;
    aed2::Nat longVieja = this->longitudMax;
    // Actualizo la latitud y longitud maxima
    if(c.latitud() > latVieja){
        this->latitudMax = c.latitud();
    }
    if(c.longitud() > longVieja){
        this->longitudMax = c.longitud();
    }
    // Miro si hay que actualizar el vector de caminos
    aed2::Nat tam = this->latitudMax * this->longitudMax;
    if(tam > this->caminos.Longitud()){
        aed2::Lista<aed2::Nat>* nuevosCaminos = new aed2::Lista<aed2::Nat>[tam];
        aed2::Lista<aed2::Nat>::Iterador itCaminos = nuevosCaminos->CrearIt();
        aed2::Nat tamViejo = this->caminos.Longitud();
        while(itCaminos.HaySiguiente()){
            itCaminos.Siguiente() = 0;
            itCaminos.Avanzar();
        }
        // Creo un iterador de las coordenadas
        // posVieja = pos(Siguiente(i)) pero con la latitud y longitud max anterior
        // Buscar posNueva = pos(Siguiente(i))
        // nuevosCaminos[posNueva] = this.caminos[posvieja]

        // VER COMO RESUELVO LA PARTE DE MIGRAR LOS CAMINOS VIEJOS A LOS CAMINOS NUEVOS
    }
    //this->coordenadasMapa.Agregar(c);
}


/*aed2::Conj<Coordenada> Mapa::coordenadas(){
    return this->coordenadasMapa;
}
*/
bool Mapa::posExistente(Coordenada c){
    //return this->coordenadas().Pertenece(c);
}

bool Mapa::hayCamino(Coordenada c, Coordenada c1){
    return true;
}

aed2::Nat Mapa::maximaLatitud(){
    return this->latitudMax;
}

aed2::Nat Mapa::maximaLongitud(){
    return this->longitudMax;
}

aed2::Nat Mapa::pos(Coordenada c){
    return (c.latitud() - 1) * this->longitudMax + (c.longitud() - 1);
}

aed2::Lista<Coordenada> Mapa::vecinos(Coordenada c){

}

void Mapa::pintarVecinos(aed2::Nat color, aed2::Nat pinto){

}
