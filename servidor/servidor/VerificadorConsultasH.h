/*
 * VerificadorConsultasH.h
 *
 *  Created on: 09/06/2012
 *      Author: migue
 */

#ifndef __VALIDADORCONSULTAS_H
#define __VALIDADORCONSULTAS_H

class Consulta;

class VerificadorConsultasH {
public:
	bool verificarConsulta(const Consulta& consulta);
	VerificadorConsultasH() {}
	~VerificadorConsultasH() {}
private:
	bool hayDimesionesEnRes(const Consulta& cons);
	bool hayHechosEnRes(const Consulta& cons);
	bool hayAgregacionesEnHechos(const Consulta& cons);
	bool filtrosCorrectos(const Consulta& cons);
	bool entradasCorrectos(const Consulta& cons);
	bool resultadoCorrectos(const Consulta& cons);
	bool camposTablaPivoteCorrectos(const Consulta& cons);


	bool cClienteValida(const Consulta& cons);
	bool cClienteTP(const Consulta& cons);
};

#endif
