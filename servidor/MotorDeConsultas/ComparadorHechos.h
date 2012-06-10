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
	ComparadorHechos(bool filtarHechos, const Consulta& consulta);
	virtual ~ComparadorHechos();

	bool registroAceptado(const std::string& registro);
private:
	bool aceptarHecho(const std::string& hechoComparador, const std::string& valorHecho);
	bool _filtrarHechos;
	//std::vector <std::string> _HechosAFiltrar;
	std::vector <unsigned> _indHechos;
	std::vector <std::string> _valorHechos;
	std::string _campoActual;
};

#endif /* COMPARADORHECHOS_H_ */
