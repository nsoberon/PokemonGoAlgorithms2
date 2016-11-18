#ifndef COLAPRIOR_H
#define COLAPRIOR_H

#include "aed2/TiposBasicos.h"
#include "aed2/Lista.h"

template<class T>
class ColaPrior{


    private:
        struct Nodo{
            Nodo* padre;
            Nodo* izq;
            Nodo* der;
            T dato;
            Nodo(T d){
                this->der = NULL;
                this->izq = NULL;
                this->padre = NULL;
                this->dato = d;
            }
        };

    public:
        ColaPrior();
        ~ColaPrior();
        void Vacia();
        bool EsVacia();
        T Proximo();
        T Desencolar();
        aed2::Nat Tamanio();



        /************************************
        * Iterador de Cola de Prioridad *
        ************************************/
        class Iterador
        {


            private:

                /*struct Nodo{
                    Nodo* padre;
                    Nodo* izq;
                    Nodo* der;
                    T dato;
                    Nodo(T d){
                        this->der = NULL;
                        this->izq = NULL;
                        this->padre = NULL;
                        this->dato = d;
                    }
                };*/

                ColaPrior<T>::Nodo* siguiente;
                ColaPrior<T>* cola;
                friend class ColaPrior;

        public:

                Iterador();
                ~Iterador();
                void EliminarSiguiente();
                bool HaySiguiente();
                ColaPrior<T>::Nodo* Siguiente();
        };

        ColaPrior<T>::Iterador CrearIterador(ColaPrior<T>::Nodo*);
        ColaPrior<T>::Iterador Encolar(T);
        aed2::Nat tam;
        ColaPrior<T>::Nodo* cabeza;

        void Intercambiar(Nodo*, Nodo*);
        Nodo* ultimoNodo();
        Nodo* ultimoPadre();



};


template< typename T>
ColaPrior<T>::ColaPrior(){

};

template< typename T>
ColaPrior<T>::~ColaPrior(){

};

template< typename T>
void ColaPrior<T>::Vacia(){
    this->cabeza = NULL;
    this->tam = 0;
};

template< typename T>
bool ColaPrior<T>::EsVacia(){
    return this->tam == 0;
};

template< typename T>
typename ColaPrior<T>::Iterador ColaPrior<T>::Encolar(T elem){
    Nodo* nuevoNodo = new Nodo(elem);
    if(this->EsVacia()){
        this->cabeza = nuevoNodo;
    }else{
        Nodo* ultimoPadre = this->ultimoPadre();
        if(ultimoPadre->izq){
            ultimoPadre->der = nuevoNodo;
        }else{
            ultimoPadre->izq = nuevoNodo;
        };
        nuevoNodo->padre = ultimoPadre;
        while(this->cabeza != nuevoNodo && nuevoNodo->dato < nuevoNodo->padre->dato){
            this->Intercambiar(nuevoNodo->padre, nuevoNodo);
        }
    }
    this->tam ++;
    ColaPrior<T>::Iterador res = this->CrearIterador(nuevoNodo);
    return res;
};

template< typename T>
T ColaPrior<T>::Desencolar(){
    T res = this->cabeza->dato;
    aed2::Nat tam = this->tam;
    if(tam == 1){
        this->cabeza = NULL;
    }else{
        Nodo* ultimo = this->ultimoNodo();
        if(ultimo->padre->der == ultimo){
            ultimo->padre->der = NULL;
        }else{
            ultimo->padre->izq = NULL;
        }
        ultimo->der = cabeza->der;
        ultimo->izq = cabeza->izq;
        ultimo->padre = NULL;
        Nodo* actual = ultimo;
        while((actual->izq && actual->dato > actual->izq->dato) || (actual->der && actual->dato > actual->der->dato)){
            if(!actual->der){
                this->Intercambiar(actual, actual->izq);
            }else{
                if(actual->izq->dato < actual->dato){
                    this->Intercambiar(actual, actual->der);
                }else
                    this->Intercambiar(actual, actual->izq);
            }
        }
    }
    this->tam --;
    return res;

};

template< typename T>
T ColaPrior<T>::Proximo(){
    return this->cabeza->dato;
};

template< typename T>
aed2::Nat ColaPrior<T>::Tamanio(){
    return this->tam;
};

template< typename T>
ColaPrior<T>::Iterador::Iterador(){

}

template< typename T>
ColaPrior<T>::Iterador::~Iterador(){

}

template< typename T>
typename ColaPrior<T>::Iterador ColaPrior<T>::CrearIterador(ColaPrior<T>::Nodo* n){
    ColaPrior<T>::Iterador res;
    res.siguiente = n;
    res.cola = this;
    return res;
}

template< typename T>
void ColaPrior<T>::Iterador::EliminarSiguiente(){
    Nodo* ultimo = this->cola->ultimoNodo();
    Nodo* elem = this->siguiente;
    if(elem == this->cola->cabeza){
        this->cola->Desencolar();
    }else{
        Nodo* ultimo = this->cola->ultimoNodo();
        if(ultimo->padre->der == ultimo){
            ultimo->padre->der = NULL;
        }else{
            ultimo->padre->izq = NULL;
        }
        ultimo->izq = elem->izq;
        ultimo->der = elem->der;
        ultimo->padre = elem->padre;
        // VER QUE PASA S EL ELEM ES LA RAIZ NO TENDRIA PADRE

        if(elem->padre->der == elem){
            elem->padre->der = NULL;
        }else{
            elem->padre->izq = NULL;
        }
        Nodo* actual = ultimo;
        ColaPrior<T>* cp = this->cola;
        while((actual->izq && actual->dato > actual->izq->dato) || actual->der && (actual->dato > actual->der->dato)){
            if(!actual->der || actual->izq->dato < actual->dato){
                cp->Intercambiar(actual, actual->izq);
            }else{
                cp->Intercambiar(actual, actual->der);
            }

        }
    }
};

template< typename T>
bool ColaPrior<T>::Iterador::HaySiguiente(){
    return this->siguiente;
}


template< typename T>
typename ColaPrior<T>::Nodo* ColaPrior<T>::ultimoNodo(){
    if(this->tam == 1){
        return this->cabeza;
    }else{
        aed2::Lista<aed2::Nat> listaLog;
        aed2::Nat tam = this->tam;
        while(tam > 1){
            listaLog.AgregarAdelante(tam % 2);
            tam = tam/2;
        }
        aed2::Lista<aed2::Nat>::Iterador it = listaLog.CrearIt();
        Nodo* actual = this->cabeza;
        while(it.HaySiguiente()){
            if(it.Siguiente() == 0){
                actual = actual->izq;
            }else{
                actual = actual->der;
            }
        it.Avanzar();
        }
        return actual;
    }
};

template< typename T>
typename ColaPrior<T>::Nodo* ColaPrior<T>::ultimoPadre(){
    Nodo* ultimo = this->ultimoNodo();
    if(ultimo = this->cabeza){
        return ultimo;
    }else{
        Nodo* actual = ultimo;
        while(actual->padre->der == actual){
            actual = actual->padre;
        }
        actual = actual->padre;
        while(actual->izq){
            actual = actual->izq;
        }
        return actual;
    }
};

template< typename T>
void ColaPrior<T>::Intercambiar(ColaPrior<T>::Nodo* padre, ColaPrior<T>::Nodo* hijo){
if(hijo == padre->izq){
    Nodo* derPadre = padre->der;
    padre->der = hijo->der;
    padre->izq = hijo->izq;
    hijo->izq = padre;
    hijo->der = derPadre;
}else{
    Nodo* izqPadre = padre->izq;
    padre->izq = hijo->izq;
    padre->der = hijo->der;
    hijo->der = padre;
    hijo->izq = izqPadre;
}
hijo->padre = padre->padre;
padre->padre = hijo;
if(!hijo->padre){
    this->cabeza = hijo;
}
};

template< typename T>
typename ColaPrior<T>::Nodo* ColaPrior<T>::Iterador::Siguiente(){
    return this->siguiente;
}

#endif // COLAPRIOR_H
