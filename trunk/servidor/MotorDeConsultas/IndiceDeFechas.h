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

	void recuperar(const Fecha& fecha, Lista_Id& ids);

	void guardarFecha(const Fecha& fecha, const Id_Registro& id);

	void limpiar();
private:
	void guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2);
	void guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2, Lista_Id& ids);

	void guardarIDs(const FechaNumerica& fecha);
	void guardarIDs(const FechaNumerica& fecha, Lista_Id& ids);

	MapaDeFechas _fechas;
	Lista_Id _res;
};

#endif /* INDICEDEFECHAS_H_ */
