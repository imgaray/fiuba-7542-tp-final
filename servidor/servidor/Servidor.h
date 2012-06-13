#ifndef __SERVIDOR_H
#define __SERVIDOR_H

#include "../MotorDeConsultas/BaseDeDatos.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "VerificadorConsultasH.h"
#include "VerificadorEntradasH.h"
#include "ControladorServidor.h"
#include "GenRegistros.h"
#include "../../comun/Definiciones.h"

class Servidor: public ResolvedorConsultas, public ResolvedorEntradas {
private:
	BaseDeDatos bdd;
	VerificadorConsultasH vdc;
	VerificadorEntradasH vde;
	ControladorServidor cds;
public:
	Respuesta resolverEntrada(Consulta& entrada);
	Respuesta resolver(Consulta& consulta);
	Servidor(Puerto pclientes, Puerto pagentes);
	~Servidor();


	BaseDeDatos& baseDeDatos(){ return this->bdd; }
};
#endif
