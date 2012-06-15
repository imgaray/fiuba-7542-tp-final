/*
 * IndiceDeFechas.h
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#ifndef INDICEDEFECHAS_H_
#define INDICEDEFECHAS_H_

#include "TiposDeDatos.h"
#include "../../comun/M_Fechas.h"

class IndiceDeFechas {
public:
	IndiceDeFechas();
	virtual ~IndiceDeFechas();

	/*
	 * Se recupera una lista con Ids que corresponden
	 * a la fecha pasada como argumento.
	 */
	const Lista_Id& recuperar(const Fecha& fecha);

	/*
	 * Se recupera una lista con Ids que corresponden
	 * a la fecha pasada como argumento.
	 */
	void recuperar(const Fecha& fecha, Lista_Id& ids);

	/*
	 * Se guarda una fecha al indice con su id correspondiente
	 */
	void guardarFecha(const Fecha& fecha, const Id_Registro& id);

	/*
	 * Se borra y reestablece el contenido del indice
	 */
	void limpiar();
private:
	/*
	 * Almacena en la lista los Ids que corresponden desde la fecha f1
	 * hasta la fecha f2.
	 */
	void guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2);
	void guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2, Lista_Id& ids);

	/*
	 * Almacena en la lista los Ids que corresponden a una fecha.
	 */
	void guardarIDs(const FechaNumerica& fecha);
	void guardarIDs(const FechaNumerica& fecha, Lista_Id& ids);

	MapaDeFechas _fechas;
	M_Fechas m_fechas;
	Lista_Id _res;
};

#endif /* INDICEDEFECHAS_H_ */
