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

/**
 * @class ComparadorHechos
 *  Esta clase es la encargada de decidir si un registro en particular
 *  debe o no ser filtrado a partir de filtros de Hechos. Construyendose a
 *  partir un Consulta en particular.
 */


class ComparadorHechos {
public:
	/**
	 * @brief Constructor que se indica si se tiene que filtrar los hechos y
	 * la consulta con las caracterizticas del filtrado.
	 * @param filtarHechos booleano indicando si hay filtrados de hechos.
	 * @param consulta es la Consulta que contiene los datos por los cual filtrar
	 */
	ComparadorHechos(bool filtarHechos, const Consulta& consulta);
	virtual ~ComparadorHechos();

	/**
	 * @brief Retorna un bool indicando si el registro a aceptado filtrado o
	 * si se debe descartar.
	 * @brief registro string que contiene el registro completo a analizar.
	 * @return booleano indicando si el registro se debe filtrar o descartar.
	 */
	bool registroAceptado(const std::string& registro);
private:
	/**
	 * @brief Retorna un bool indicando si un hecho en especifico
	 * tenga que ser filtrado o no.
	 * @param hechoComparador string que contiene el valor un hecho con el cual comparar.
	 * @param valorHecho string que contien el valor del hecho del registros a comparar.
	 */
	bool aceptarHecho(const std::string& hechoComparador, const std::string& valorHecho);

	bool _filtrarHechos;
	std::vector <unsigned> _indHechos;
	std::vector <std::string> _valorHechos;
	std::string _campoActual;
	Utilitario u;
};

#endif /* COMPARADORHECHOS_H_ */
