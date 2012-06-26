/*
 * ComparadorHechos.h
 *
 *  Created on: 09/06/2012
 *      Author: migue
 */

#ifndef COMPARADORHECHOS_H_
#define COMPARADORHECHOS_H_

#include <string>
#include <vector>
#include "../../comun/Utilitario.h"
class Consulta;

/*
 * @DOC:
						Clase ComparadorHechos

	Esta clase es la encargada de decidir si un registro en particular debe o no
	ser filtrado a partir de filtros de Hechos. Construyendose a partir un Consulta
	en particular.

Atributos:

	bool _filtrarHechos: booleano indicando si debe comprobar el registro a analizar
	o no, es decir, solo filtra si hay filtros o entradas de hechos.
*
	std::vector <unsigned> _indHechos: Contenedor utilizado para guardar los indices de campo
	(segun Organizacion) de los hechos que se tiene que filtrar.
*
	std::vector <std::string> _valorHechos: Contenedor utilizado para guardar los valores por
	los cual se tiene que filtrar los registros.
*
	std::string _campoActual: string utilizado para guardar el campo de registro temporalmente.
*
	Utilitario u: clase utilizada para hacer operaciones y calculos auxiliares.
 * @END
 * */


class ComparadorHechos {
public:
	/*
	 * Constructor que se indica si se tiene que filtrar los hechos y
	 * la consulta con las caracterizticas del filtrado
	 */
	ComparadorHechos(bool filtarHechos, const Consulta& consulta);
	virtual ~ComparadorHechos();

	/*
	 * Retorna un bool indicando si el registro a aceptado filtrado o
	 * si se debe descartar
	 */
	bool registroAceptado(const std::string& registro);
private:
	/*
	 * Retorna un bool indicando si un hecho en especifico
	 * tenga que ser filtrado o no.
	 */
	bool aceptarHecho(const std::string& hechoComparador, const std::string& valorHecho);

	bool _filtrarHechos;
	std::vector <unsigned> _indHechos;
	std::vector <std::string> _valorHechos;
	std::string _campoActual;
	Utilitario u;
};

#endif /* COMPARADORHECHOS_H_ */
