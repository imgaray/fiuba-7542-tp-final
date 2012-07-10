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


/**
 * @class Indice
 * 		Esta clase es un templete creada para funcionar como indice, que guarda los id
 * de registros para un valores del tipo _dato_.
 */
template < class _dato_ >
class Indice {
public:
	typedef std::multimap < _dato_, Id_Registro> Mapa;
	typedef typename Mapa::iterator Iterador;
	typedef typename std::pair < Iterador, Iterador > Rango;

	/**
	 * @brief Constructor sin argumentos.
	 */
	Indice() { }

	/**
	 * @brief Recupera una Lista de Ids que corresponde al valor "dato".
	 * @param dato valor del cual se va a recuperar la lista de ids
	 * @return lista que contiene los ids recuperados
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

	/**
	 * @brief Recupera una Lista de Ids que corresponde al valor "dato".
	 * @param dato valor del cual se va a recuperar la lista de ids.
	 * @param lista es la lista donde se almacenaran los ids recuperados
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

	/**
	 * @brief Recupera una Lista de Ids que corresponde al valor "dato"
	 * @param dato valor que se guardara en el indice.
	 * @param registro id del registro para el cual se guardara el dato
	 */
	void agregar(_dato_ dato, Id_Registro registro) {
		_mapa.insert(std::pair< _dato_, Id_Registro > (dato, registro));
	}

	/**
	 * @brief Se borra y restablece el contenido del indice
	 */
	void limpiar() {
		_mapa.clear();
	}

	virtual ~Indice() { }
private:
	Mapa _mapa;
};
#endif /* INDICE_HPP_ */
