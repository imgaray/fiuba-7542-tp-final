#ifndef __CONTENEDORAGENTES_H
#define __CONTENEDORAGENTES_H

#include "AgenteRemoto.h"

/** @class ContenedorAgentes
 
	Es una clase que hace de interfaz a un objeto que pueda contener a los
agentes remotos. La misma será aplicada por el controlador del servidor
que los contendrá a todos. Sirve como para mitigar el acoplamiento.

*/

class ContenedorAgentes {
public:
	/**	Metodo virtual abstracto que debe implementar cada contenedor. */
	virtual void agregarAgente(AgenteRemoto* agt) = 0;
	virtual ~ContenedorAgentes() {}
};

#endif
