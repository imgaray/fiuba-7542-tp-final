#ifndef __SERVIDOR_H
#define __SERVIDOR_H

#include "../MotorDeConsultas/BaseDeDatos.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "VerificadorConsultasH.h"
#include "VerificadorEntradasH.h"
#include "ControladorServidor.h"
#include "../../comun/Definiciones.h"

/* @DOC

	Clase Servidor

	Esta clase es la que se maneja desde el programa principal. La clase
contendra a la base de datos, los verificadores y al controlador. En si,
es la clase que nuclea las funcionalidades necesarias para el funcionamiento.

	Su funcion es basicamente iniciar la base de datos, los verificadores y
el controlador. A su vez, tambien transmite las consultas y actualizaciones
a la base de datos, haciendo previa verificacion de las mismas.

@END */

class Servidor: public ResolvedorConsultas, public ResolvedorEntradas {
private:
	BaseDeDatos *bdd;
	VerificadorConsultasH vdc;
	VerificadorEntradasH vde;
	ControladorServidor cds;
public:

	/* @DOC
Metodos publicos
	@END */
	
	/* @DOC
	Respuesta resolverEntrada(Consulta& entrada)
		Es el metodo que realiza las actualizaciones. Antes de pasarle
		la consulta a la base de datos, realiza una verificacion de la
		entrada. Si es valida, pasara la entrada a la base de datos. En
		caso contrario, devuelve un mensaje de error.
	@END */
	Respuesta resolverEntrada(Consulta& entrada);

	/* @DOC
	Respuesta resolver(Consulta& entrada)
		Es el metodo que realiza las consultas. Antes de pasarle
		la consulta a la base de datos, realiza una verificacion de la
		misma. Si es valida, pasara la consulta a la base de datos, obteniendo
		la respuesta a la misma. En	caso contrario, devuelve un mensaje de error.
	@END */
	Respuesta resolver(Consulta& consulta);
	
	/* @DOC
	bool funcional()
		Evalua si el servidor esta funcional, es decir si los receptores
		de conexino son validos 
	@END */
	bool funcional();
	
	Servidor(Puerto pclientes, Puerto pagentes);
	~Servidor();
	BaseDeDatos& baseDeDatos(){ return *this->bdd; }
};
#endif
