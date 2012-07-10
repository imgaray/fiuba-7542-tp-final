#ifndef __CONTENEDORAGENTES_H
#define __CONTENEDORAGENTES_H

#include "AgenteRemoto.h"

/** @class ContenedorAgentes
 
	Es una clase que hace de interfaz a un objeto que pueda contener a los
agentes remotos. La misma será utilizada por el controlador del servidor
que los contendrá a todos. Sirve para mitigar el acoplamiento.

*/

class ContenedorAgentes {
public:
	/**	Metodo virtual abstracto que debe implementar cada contenedor. */
	virtual void agregarAgente(AgenteRemoto* agt) = 0;
	virtual ~ContenedorAgentes() {}
};

#endif
