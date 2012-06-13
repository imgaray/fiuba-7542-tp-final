#include "VerificadorEntradasH.h"
#include "../../comun/Consulta.h"
#include "../../comun/Organizacion.h"

bool VerificadorEntradasH::verificarEntrada(const Consulta& entrada) {
/*	if (!entrada.esConsultaDeAgente())
		return false;

	if (entrada.cantidadCampos() == Organizacion::cantidadCampos())
		return true;
	else
		return false;*/
	return true;
}
