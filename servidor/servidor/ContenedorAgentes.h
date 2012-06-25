#ifndef __CONTENEDORAGENTES_H
#define __CONTENEDORAGENTES_H

#include "AgenteRemoto.h"

/* @DOC
	Clase ContenedorAgentes
 
	Es una clase que hace de interfaz a un objeto que pueda contener a los
agentes remotos. La misma sera aplicada por el controlador del servidor
que los contendra a todos. Sirve como para mitigar el acoplamiento.

 * @END
*/

class ContenedorAgentes {
public:
	/*@DOC
	virtual void agregarAgente(AgenteRemoto* agt) = 0
		Metodo virtual abstracto que debe implementar cada contenedor.
	@END*/
	virtual void agregarAgente(AgenteRemoto* agt) = 0;
	virtual ~ContenedorAgentes() {}
};

#endif
