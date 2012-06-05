/*
 * IndiceDeFechas.h
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#ifndef INDICEDEFECHAS_H_
#define INDICEDEFECHAS_H_

#include "TiposDeDatos.h"

class IndiceDeFechas {
public:
	IndiceDeFechas();
	virtual ~IndiceDeFechas();

	const Lista_Id& recuperar(const Fecha& fecha);

	void guardarFecha(const Fecha& fecha, const Id_Registro& id);
private:
	void guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2);

	void guardarIDs(const FechaNumerica& fecha);

	MapaDeFechas _fechas;
	Lista_Id _res;
};

#endif /* INDICEDEFECHAS_H_ */
