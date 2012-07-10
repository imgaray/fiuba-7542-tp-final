#ifndef __CONTENEDORCLIENTES_H
#define __CONTENEDORCLIENTES_H

#include "ClienteRemoto.h"


/** @class ContenedorClientes
 
	Es una clase que hace de interfaz a un objeto que pueda contener a los
clientes remotos. La misma será uitlizada por el controlador del servidor
que los contendrá a todos. Sirve para mitigar el acoplamiento. */

class ContenedorClientes {
public:
	/*@DOC
	virtual void agregarCliente(ClienteRemoto* cli) = 0
		Metodo virtual abstracto que debe implementar cada contenedor.
	@END*/
	virtual void agregarCliente(ClienteRemoto* agt) = 0;
	virtual ~ContenedorClientes() {}
};

#endif
