#ifndef AED2_TIPOSBASICOS_H_INCLUDED
#define AED2_TIPOSBASICOS_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

namespace aed2{
    typedef unsigned int Nat;
    typedef std::string String;
    
	/** 
	 * Imprime un elemento a un string, en vez de a una pantalla, 
	 * a través del operador << 
	 */
	template <typename T>
	std::string to_str(const T& t)
	{
		std::stringstream ss;
		ss << t;

		return ss.str();
	}
		
	
	/**
	 * Función para mostrar genérica
	 */
    template<class T>
    std::ostream& Mostrar(std::ostream& os, const T& t, char izq, char der, char sep = ',') {
        typename T::const_Iterador it = t.CrearIt();
        os << izq;
        while(it.HaySiguiente()) {
            os << it.Siguiente();
            it.Avanzar();
            if(it.HaySiguiente()) os << sep;
        }
        return os << der;
    }
	

	/**
	 * Esta función se puede utilizar para comparar dos colecciones
	 * iterables que representen conjuntos, es decir, que no tengan 
	 * elementos repetidos.
	 */
	template<typename T, typename S>
	bool Comparar(const T& t, const S& s)
	{
	  typename T::const_Iterador it1 = t.CrearIt();
	  typename S::const_Iterador it2 = s.CrearIt();

		// me fijo si tienen el mismo tamanho

		Nat len1 = 0;
		while( it1.HaySiguiente() ) {
			len1++;
			it1.Avanzar();
		}

		Nat len2 = 0;
		while( it2.HaySiguiente() ) {
			len2++;
			it2.Avanzar();
		}

		if ( len1 != len2 )
			return false;

		it1 = t.CrearIt();
		it2 = s.CrearIt();

		// me fijo que tengan los mismos elementos

		while( it1.HaySiguiente() )
		{
			bool esta = false;
			it2 = s.CrearIt();

			while( it2.HaySiguiente() ) {
			  if ( it1.Siguiente() == it2.Siguiente() ) {
				esta = true;
				break;
			  }
			  it2.Avanzar();
			}

			if ( !esta ) {
				return false;
			}
				
			it1.Avanzar();
		}
	  
	  return true;
	}

} // namespace aed2

#endif //AED2_TIPOSBASICOS_H_INCLUDED