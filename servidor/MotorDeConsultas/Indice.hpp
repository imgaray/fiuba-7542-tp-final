/*
 * Indice.hpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef INDICE_HPP_
#define INDICE_HPP_
#include <iostream>
#include <map>
#include "TiposDeDatos.h"
#include <algorithm>


/*
 * @DOC:
						Clase Indice

	Esta clase es un templete creada para funcionar como indice, que guarda los id
	de registros para un valores del tipo _dato_.

Atributos:

	Mapa _mapa: mapa que utilizado para guardar los id.

 * @END
 * */


template < class _dato_ >
class Indice {
public:
	typedef std::multimap < _dato_, Id_Registro> Mapa;
	typedef typename Mapa::iterator Iterador;
	typedef typename std::pair < Iterador, Iterador > Rango;

	Indice() { }

	/*
	 * Recupera una Lista de Ids que corresponde al valor "dato"
	 */
	Lista_Id recuperar(_dato_ dato) {
		Iterador _it;
		Rango _ret;
		std::list<Id_Registro> _res;

		_res.clear();

		_ret = _mapa.equal_range(dato);

		for (_it = _ret.first ; _it != _ret.second ; ++_it)
			_res.push_back(_it->second);

		_res.sort();
		_res.unique();

		return _res;
	} ;

	/*
	 * Recupera una Lista de Ids que corresponde al valor "dato"
	 */
	void recuperar(_dato_ dato, Lista_Id& lista) {
			Iterador _it;
			Rango _ret;

			_ret = _mapa.equal_range(dato);

			for (_it = _ret.first ; _it != _ret.second ; ++_it)
				lista.push_back(_it->second);

			lista.sort();
			lista.unique();
		} ;

	/*
	 * Recupera una Lista de Ids que corresponde al valor "dato"
	 */
	void agregar(_dato_ dato, Id_Registro registro) {
		_mapa.insert(std::pair< _dato_, Id_Registro > (dato, registro));
	}

	/*
	 * Se borra y restablece el contenido del indice
	 */
	void limpiar() {
		_mapa.clear();
	}

	virtual ~Indice() { }
private:
	Mapa _mapa;
};
#endif /* INDICE_HPP_ */
