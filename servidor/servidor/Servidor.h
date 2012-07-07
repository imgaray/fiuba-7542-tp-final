#ifndef __SERVIDOR_H
#define __SERVIDOR_H

#include "../MotorDeConsultas/BaseDeDatos.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "VerificadorConsultasH.h"
#include "VerificadorEntradasH.h"
#include "ControladorServidor.h"
#include "../../comun/Definiciones.h"

/** @class Servidor

	Esta clase es la que se maneja desde el programa principal. La clase
contendrá a la base de datos, los verificadores y al controlador. En sí,
es la clase que nuclea las funcionalidades necesarias para el funcionamiento.

	Su función es básicamente iniciar la base de datos, los verificadores y
el controlador. A su vez, tambien transmite las consultas y actualizaciones
a la base de datos, haciendo previa verificacion de las mismas. */

class Servidor: public ResolvedorConsultas, public ResolvedorEntradas {
private:
	BaseDeDatos *bdd; /* Base de datos a consultar o actualizar */
	VerificadorConsultasH vdc; /* Verificador de integridad de consulta */
	VerificadorEntradasH vde; /* Verificador de integridad de entrada */
	ControladorServidor cds; /* Controlador del servidor */

public:
	
	/** Es el método que realiza las actualizaciones. Antes de pasarle
		la consulta a la base de datos, realiza una verificación de la
		entrada. Si es válida, pasará la entrada a la base de datos. En
		caso contrario, devuelve una respuesta con un mensaje de error.
	*/
	Respuesta resolverEntrada(Consulta& entrada);

	/** Es el método que realiza las consultas. Antes de pasarle
		la consulta a la base de datos, realiza una verificación de la
		misma. Si es válida, pasará la consulta a la base de datos, obteniendo
		la respuesta a la misma. En	caso contrario, devuelve una respuesta
		con un mensaje de error.
	 */
	Respuesta resolver(Consulta& consulta);
	
	/** Evalúa si el servidor esta funcional, es decir si los receptores
		de conexión están activos. 
	*/
	bool funcional();
	
	/** Al crear el servidor, éste ya comienza sus funcionalidades.
	 * @param pclientes El puerto por el cual se escucharán conexiones de clientes.
	 * @param pagentes El puerto por el cual se escucharán conexiones de agentes.
	*/
	Servidor(Puerto pclientes, Puerto pagentes);
	
	/** Detiene la ejecución del servidor y se encarga de liberar la memoria pedida */
	~Servidor();
	
	BaseDeDatos& baseDeDatos(){ return *this->bdd; }
};
#endif
