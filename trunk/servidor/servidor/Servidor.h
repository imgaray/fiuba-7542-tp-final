#ifndef __SERVIDOR_H
#define __SERVIDOR_H

#include "BaseDeDatosH.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "VerificadorConsultasH.h"
#include "VerificadorEntradasH.h"
#include "ControladorServidor.h"

class Servidor: public ResolvedorConsultas, public ResolvedorEntradas {
private:
	BaseDeDatosH bdd;
	VerificadorConsultasH vdc;
	VerificadorEntradasH vde;
	ControladorServidor cds;
public:
	Respuesta resolverEntrada(Consulta& entrada);
	Respuesta resolver(Consulta& consulta);
	Servidor();
	~Servidor();
};
#endif