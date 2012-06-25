#ifndef __CONTENEDORCLIENTES_H
#define __CONTENEDORCLIENTES_H

#include "ClienteRemoto.h"


/* @DOC
	Clase ContenedorClientes
 
	Es una clase que hace de interfaz a un objeto que pueda contener a los
clientes remotos. La misma sera aplicada por el controlador del servidor
que los contendra a todos. Sirve como para mitigar el acoplamiento.

 * @END
*/

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
