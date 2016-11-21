#ifndef COLAPRIOR_H
#define COLAPRIOR_H

#include "aed2/TiposBasicos.h"
#include "aed2/Lista.h"
#include "aed2/Conj.h"

template<class T>
class ColaPrior{


    private:
        struct Nodo{
            Nodo* padre;
            Nodo* izq;
            Nodo* der;
            T dato;
            typename aed2::Conj<T>::Iterador posicionEnConj;
            Nodo(T d){
                this->der = NULL;
                this->izq = NULL;
                this->padre = NULL;
                this->dato = d;
            }
        };

        aed2::Conj<T> elementos_;
        aed2::Nat tam;
        ColaPrior<T>::Nodo* cabeza;


        void Intercambiar(Nodo*, Nodo*);
        Nodo* ultimoNodo();
        Nodo* ultimoPadre();

    public:
        ColaPrior();
        ColaPrior(const ColaPrior&);
        ~ColaPrior();
        void Destruir();
        void Vacia();
        bool EsVacia();
        T Proximo();
        T Desencolar();
        aed2::Nat Tamanio();

        ColaPrior<T>& operator = (const ColaPrior& otra);


        /************************************
        * Iterador de Cola de Prioridad *
        ************************************/
        class Iterador
        {


            private:

                ColaPrior<T>::Nodo* siguiente;
                ColaPrior<T>* cola;
                typename aed2::Conj<T>::Iterador it_cola_;
                friend class ColaPrior;

        public:

                Iterador();
                void EliminarSiguiente();
                bool HaySiguiente();
                ColaPrior<T>::Nodo* Siguiente();
        };

        ColaPrior<T>::Iterador CrearIterador(ColaPrior<T>::Nodo*);
        ColaPrior<T>::Iterador Encolar(T);

        class const_Iterador
        {


            private:

                typename aed2::Conj<T>::const_Iterador it_cola_;
                const_Iterador(const ColaPrior<T>& c);
                friend class ColaPrior<T>;

        public:

                const_Iterador();
                void Avanzar();
                bool HaySiguiente();
                T Siguiente();
        };

         const_Iterador CrearIt() const;


};


template< typename T>
ColaPrior<T>::ColaPrior(){

};

template <typename T>
ColaPrior<T>::ColaPrior(const ColaPrior& otra)
{
    this->Vacia();
    ColaPrior<T>::const_Iterador it = otra.CrearIt();
    while(it.HaySiguiente()){
        this->Encolar(it.Siguiente());
        it.Avanzar();
    }
}

template <typename T>
ColaPrior<T>& ColaPrior<T>::operator = (const ColaPrior& otra)
{
    this->Vacia();
    ColaPrior<T>::const_Iterador it = otra.CrearIt();
    while(it.HaySiguiente()){
        this->Encolar(it.Siguiente());
        it.Avanzar();
    }

}



template< typename T>
ColaPrior<T>::~ColaPrior(){
    this->Destruir();
};

template< typename T>
void ColaPrior<T>::Destruir(){
    while(this->cabeza != NULL){
        this->Desencolar();
    }
}

template< typename T>
void ColaPrior<T>::Vacia(){
    this->tam = 0;
    this->cabeza = NULL;
    aed2::Conj<T> conjElementos;
    this->elementos_ = conjElementos;
};

template< typename T>
bool ColaPrior<T>::EsVacia(){
    return this->tam == 0;
};

template< typename T>
typename ColaPrior<T>::Iterador ColaPrior<T>::Encolar(T elem){
    Nodo* nuevoNodo = new Nodo(elem);
    nuevoNodo->posicionEnConj = this->elementos_.AgregarRapido(elem);
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

    return this->CrearIterador(nuevoNodo);;
};

template< typename T>
T ColaPrior<T>::Desencolar(){
    T res = this->cabeza->dato;
    //this->cabeza->posicionEnConj.EliminarSiguiente();
    delete this->cabeza;
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
        this->cabeza = ultimo;
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
    assert(this->tam > 0);
    return this->cabeza->dato;
};

template< typename T>
aed2::Nat ColaPrior<T>::Tamanio(){
    return this->tam;
};

template< typename T>
ColaPrior<T>::Iterador::Iterador(){}

template< typename T>
typename ColaPrior<T>::Iterador ColaPrior<T>::CrearIterador(ColaPrior<T>::Nodo* n){
    //ColaPrior<T>::Iterador* res = new ColaPrior<T>::Iterador();
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
        elem->posicionEnConj.EliminarSiguiente();
        Nodo* ultimo = this->cola->ultimoNodo();
        if(ultimo->padre->der == ultimo){
            ultimo->padre->der = NULL;
        }else{
            ultimo->padre->izq = NULL;
        }
        ultimo->izq = elem->izq;
        ultimo->der = elem->der;
        ultimo->padre = elem->padre;
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
        this->cola->tam --;
    }
    if(this->cola->EsVacia()){
        this->siguiente = NULL;
    }else{
        this->siguiente = this->cola->cabeza;
    }
};

template< typename T>
bool ColaPrior<T>::Iterador::HaySiguiente(){
    return this->siguiente != NULL;
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
    if(ultimo == this->cabeza){
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

// Funciones const_Iterador
template<class T>
ColaPrior<T>::const_Iterador::const_Iterador(){

}

template<class T>
ColaPrior<T>::const_Iterador::const_Iterador(const ColaPrior<T>& c)
  : it_cola_( c.elementos_.CrearIt())
{}

template <typename T>
typename ColaPrior<T>::const_Iterador ColaPrior<T>::CrearIt() const{
     return const_Iterador(*this);
}

template <typename T>
bool ColaPrior<T>::const_Iterador::HaySiguiente(){
    return it_cola_.HaySiguiente();
}

template <typename T>
T ColaPrior<T>::const_Iterador::Siguiente(){
    return it_cola_.Siguiente();
}

template <typename T>
void ColaPrior<T>::const_Iterador::Avanzar(){
    return it_cola_.Avanzar();;
}


#endif // COLAPRIOR_H
