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
class Consulta;

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
};

#endif /* COMPARADORHECHOS_H_ */
