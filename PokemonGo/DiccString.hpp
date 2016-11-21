#ifndef DICC_STRING_H_
#define DICC_STRING_H_

#include "aed2/Conj.h"
#include "TiposJuego.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


template<typename T>
class DiccString {
        public:
                /**
                CONSTRUCTOR
                * Construye un diccionario vacio.
                **/
                DiccString();


                /**
                DESTRUCTOR
                **/
                ~DiccString();


                void vacio();

                /**
                DEFINIR
                * Recibe una clave con su significado de tipo T y la define.
                * Si ya estaba definida, la reescribe.
                **/
                void Definir(const string& clave, const T& significado);

                /**
                DEFINIDO?
                * Devuelve un bool, que es true si la clave pasada está definida en
                * el diccionario.
                **/
                bool Definido(const string& clave) const;

                /**
                OBTENER
                * Dada una clave, devuelve su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
        -- Versión modificable y no modificable
                **/
                const T& Obtener(const string& clave) const;
                T& Obtener(const string& clave);

                /**
                BORRAR
                * Dada una clave, la borra del diccionario junto a su significado.
                * PRE: La clave está definida.
                --PRODUCE ALIASING--
                **/
                void Borrar(const string& clave);


                /**
                CLAVES
                * Devuelve las claves del diccionario.
                --NO PRODUCE ALIASING--
                **/
                aed2::Conj<typename DiccString<T>::Tupla> Claves();


                //ITERADOR


                class Iterador
                {
                  public:

                    Iterador();
                    ~Iterador();
                    bool HaySiguiente();
                    typename DiccString<T>::Tupla Siguiente();
                    void Avanzar();

                  private:

                    typename aed2::Conj<typename DiccString<T>::Tupla>::Iterador it_dicc_;
                    Iterador(DiccString<T>& c);
                    friend class DiccString<T>;
                    friend class DiccString<T>::const_Iterador;
                };

                Iterador CrearIt();


                class const_Iterador
                {
                  public:

                    const_Iterador();
                    ~const_Iterador();
                    bool HaySiguiente();
                    typename DiccString<T>::Tupla Siguiente();
                    void Avanzar();

                  private:

                    typename aed2::Conj<typename DiccString<T>::Tupla>::const_Iterador it_dicc_;
                    const_Iterador(const DiccString<T>& c);
                    friend class DiccString<T>;
                    friend typename DiccString<T>::const_Iterador DiccString<T>::CrearIt() const;

                };

                const_Iterador CrearIt() const;

        private:

                struct Tupla{
                    aed2::String clave;
                    T significado;
                    Tupla(aed2::String c, T s){
                        clave = c;
                        significado = s;
                    }
                };

                struct Nodo{
                    Nodo** siguientes;
                    T* significado;
                    aed2::Nat cantidadSiguientes;
                    typename aed2::Conj<Tupla>::Iterador posicionClaves;
                    Nodo(){
                        siguientes = new Nodo*[256];
                        for (int i = 0; i < 256; i++){
                            siguientes[i] = NULL;
                        }
                        significado = NULL;
                    }
                    ~Nodo(){
                        delete significado;
                        delete [] siguientes;
                    }
                };

                //TODO: funciones auxiliares

                Nodo* raiz;
                aed2::Conj<Tupla> claves;

                Nodo* buscarNodo(string);
                bool borrarRama(Nodo*, int, string);

};

// Funciones del Iterador

template<class T>
DiccString<T>::Iterador::Iterador(DiccString<T>& c)
  : it_dicc_( c.claves.CrearIt())
{}

template<class T>
DiccString<T>::const_Iterador::const_Iterador(const DiccString<T>& c)
  : it_dicc_( c.claves.CrearIt())
{}

template <typename T>
typename DiccString<T>::Iterador DiccString<T>::CrearIt(){
     return Iterador(*this);
}

template <typename T>
typename DiccString<T>::const_Iterador DiccString<T>::CrearIt() const{
     return const_Iterador(*this);
}

template <typename T>
bool DiccString<T>::Iterador::HaySiguiente(){
    return it_dicc_.HaySiguiente();
}

template <typename T>
bool DiccString<T>::const_Iterador::HaySiguiente(){
    return it_dicc_.HaySiguiente();
}

template <typename T>
typename DiccString<T>::Tupla DiccString<T>::Iterador::Siguiente(){
    return it_dicc_.Siguiente();
}

template <typename T>
typename DiccString<T>::Tupla DiccString<T>::const_Iterador::Siguiente(){
    return it_dicc_.Siguiente();
}

template <typename T>
void DiccString<T>::Iterador::Avanzar(){
    return it_dicc_.Avanzar();;
}

template <typename T>
void DiccString<T>::const_Iterador::Avanzar(){
    return it_dicc_.Avanzar();;
}

// Funciones de DiccString

template <typename T>
DiccString<T>::Iterador::Iterador()
{}

template <typename T>
DiccString<T>::Iterador::~Iterador()
{}

template <typename T>
DiccString<T>::const_Iterador::const_Iterador(){

}

template <typename T>
DiccString<T>::const_Iterador::~const_Iterador()
{}

template <typename T>
DiccString<T>::DiccString()
    : raiz(NULL), claves(){
}

template <typename T>
DiccString<T>::~DiccString(){

}


template <typename T>
void DiccString<T>::vacio(){
    aed2::Conj<Tupla>* nuevaTupla = new aed2::Conj<Tupla>;
    this->raiz = NULL;
    this->claves = *nuevaTupla;
}

template <typename T>
aed2::Conj<typename DiccString<T>::Tupla> DiccString<T>::Claves(){
    return this->claves;
}

template <typename T>
void DiccString<T>::Definir(const string& clave, const T& significado){
    if(!this->raiz){
        this->raiz = new Nodo();
    }
    Nodo* actual;
    actual = this->raiz;
    int i = 0;
    int claveLength = clave.length();
    while(i < claveLength){
        if(actual->siguientes[int(clave[i])]){
            actual = actual->siguientes[int(clave[i])];
        }else{
            Nodo* caracter = new Nodo();
            actual->siguientes[int(clave[i])] = caracter;
            actual->cantidadSiguientes ++;
            actual = actual->siguientes[int(clave[i])];
        }
        i++;
    }
    if(actual->significado){
        delete actual->significado;
        actual->posicionClaves.EliminarSiguiente();
    }
    DiccString<T>::Tupla* nuevaTupla = new DiccString<T>::Tupla(clave, significado);
    actual->posicionClaves = this->claves.AgregarRapido(*nuevaTupla);
    T* nuevoSignificado = new T(significado);
    actual->significado = nuevoSignificado;
}


template <typename T>
bool DiccString<T>::Definido(const string& clave) const{
    if(!this->raiz){
        return false;
    }else{
        Nodo* actual;
        actual = this->raiz;
        int i = 0;
        int claveLength = clave.length();
        while(i < claveLength){
            if(actual->siguientes[int(clave[i])]){
                actual = actual->siguientes[int(clave[i])];
            }else{
                return false;
            }
            i++;
        }
        return actual->significado != NULL;
    }
}

template <typename T>
T& DiccString<T>::Obtener(const string& clave) {
    Nodo* actual;
    actual = this->raiz;
    int i = 0;
    int claveLength = clave.length();
    while(i < claveLength){
        actual = actual->siguientes[int(clave[i])];
        i++;
    }
    return *(actual->significado);
}


template <typename T>
const T& DiccString<T>::Obtener(const string& clave) const {
    Nodo* actual;
    actual = this->raiz;
    int i = 0;
    int claveLength = clave.length();
    while(i < claveLength){
        actual = actual->siguientes[int(clave[i])];
        i++;
    }
    return *(actual->significado);
}

template <typename T>
void DiccString<T>::Borrar(const string& clave) {
    aed2::Nat clavesTrie = this->claves.Cardinal();
    bool empiezoABorrar = false;
    Nodo* actual = this->raiz;
    Nodo* siguiente;
    int i = 0;
    // Miro si tengo un solo elemento en el trie, lo borro y asigno la raiz NULL
    if(clavesTrie == 1){
        while(i < clave.length()){
            siguiente = actual->siguientes[int(clave[i])];
            delete actual;
            actual = siguiente;
            i++;
        }
        actual->posicionClaves.EliminarSiguiente();
        delete actual;
        this->raiz = NULL;
    }else{
        // El nodo que tiene la significado de la clave
        Nodo* nodoDefinido = this->buscarNodo(clave);
        // Si el nodo tiene al menos un hijo, quiere decir que es un nodo intermedio
        if(nodoDefinido->cantidadSiguientes > 0){
            // Borro la significado de ese nodo y le asigno NULL
            delete nodoDefinido->significado;
            nodoDefinido->significado = NULL;
        }else{
            // Si el nodo no tiene algun hijo, quiere decir que es una hoja, entonces voy a buscar
            // la rama que debo borrar
            while(i < clave.length()){
                // Miro si el nodo en el que estoy parado tiene una significado
                // Si tiene una significado, chequeo si tengo que empezar a borrar a
                // partir del nodo siguiente
                if(actual->significado){
                    empiezoABorrar = borrarRama(actual, i, clave);
                    // Si empiezoABorrar es true, quiere decir que la clave que tengo que borrar
                    // esta en una rama que tiene otras significadoes
                    // por ejemplo si defino en un trie "la" y "las", y busco borrar "las"
                    if(empiezoABorrar){
                        // Asigno a NULL el puntero que va al primero que voy a borrar
                        // y dejo en actual el primer nodo a borrar
                        siguiente = actual->siguientes[int(clave[i])];
                        actual->siguientes[int(clave[i])] = NULL;
                        actual = siguiente;
                        i++;
                    }
                }else if(actual->cantidadSiguientes > 1 && actual->siguientes[int(clave[i])]->cantidadSiguientes <= 1){
                    // Miro si el nodo en el que estoy parado tiene mas de 1 hijo y el siguiente tiene 1 o 0
                    // Si esto pasa miro si es la rama que tengo que borrar
                    empiezoABorrar = borrarRama(actual, i, clave);
                    // Si empiezoABorrar es true, quiere decir que el nodo en el que estoy parado
                    // es el primer nodo, de abajo para arriba, que tiene mas de un hijo
                    // por ejemplo si tengo definidos en mi trie "casa" y "casona"
                    // en este caso, el nodo que voy a estar mirando es "s"
                    if(empiezoABorrar){
                        // Asigno a NULL el puntero que va al primero que voy a borrar
                        // y dejo en actual el primer nodo a borrar
                        siguiente = actual->siguientes[int(clave[i])];
                        actual->siguientes[int(clave[i])] = NULL;
                        actual = siguiente;
                        i++;
                    }
                }
                if(empiezoABorrar){
                    // Empiezo a borrar, borro el nodo actual
                    // luego asigno el siguiente a actual
                    siguiente = actual->siguientes[int(clave[i])];
                    if(siguiente){
                        delete actual;
                        actual = siguiente;
                    }
                }else{
                    // Si no tengo que borrar, avanzo hasta encontrar el punto donde empiezo a borrar
                    actual = actual->siguientes[int(clave[i])];
                }
                i++;
            }
            // Me va a quedar en nodo actual el de la significado, como ya llegue a la longitud de la clave
            // lo borro cuando salgo del while
            actual->posicionClaves.EliminarSiguiente();
            delete actual;
        }
    }
}

template <typename T>
bool DiccString<T>::borrarRama(Nodo* a, int x, string clave){
    int i = x+1;
    a = a->siguientes[clave[int(x)]];
    while(i < clave.length()){
        if(a->cantidadSiguientes > 1 || a->significado){
            return false;
        }
        a = a->siguientes[int(clave[i])];
        i++;
    }
    return true;
}

template <typename T>
typename DiccString<T>::Nodo* DiccString<T>::buscarNodo(string clave){
        Nodo* actual;
        actual = this->raiz;
        int i = 0;
        int claveLength = clave.length();
        while(i < claveLength){
            actual = actual->siguientes[int(clave[i])];
            i++;
        }
        return actual;
}


#endif
