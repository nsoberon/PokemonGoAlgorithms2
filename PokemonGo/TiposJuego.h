#ifndef TIPOSJUEGO_H_
#define TIPOSJUEGO_H_


#include "aed2/TiposBasicos.h"
#include "aed2/Conj.h"
#include "aed2/ConjAcotado.h"
#include "aed2/Dicc.h"
#include "aed2/Vector.h"
#include "aed2/Arreglo.h"

typedef unsigned int Jugador;
typedef std::string Pokemon;
 
struct Tupla{
    aed2::Nat primero;
    aed2::Nat segundo;
    Tupla(aed2::Nat primero, aed2::Nat segundo) : primero(primero), segundo(segundo){}
};

/*struct Coordenada
{
	Nat latitud;
	Nat longitud;
	Coordenada(Nat latitud, Nat longitud) : latitud(latitud), longitud(longitud)
	{
	}
};
*/

#endif
