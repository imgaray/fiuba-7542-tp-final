/*
 * BaseDeDatos.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_
#include "TiposDeDatos.h"
#include "Indice.hpp"
#include "IndiceDeFechas.h"
#include "ArchivoDeDatos.h"

class Respuesta;
class Consulta;

class BaseDeDatos {
public:
	BaseDeDatos(const std::string rutaArchivo);

	/*
	 * Resuelve una Consulta y retorna la Respuesta de esta.
	 */
	Respuesta resolverConsulta(const Consulta& consulta);

	/*
	 * Agrega una entrada por parte del agente
	 */
	Respuesta agregarEntrada(const Consulta& entrada);


	virtual ~BaseDeDatos();
private:

	void resolverTablaPivote(const Consulta& consulta, Respuesta& resp);
	void resolverSinAgregacion(const Consulta& consulta, Respuesta& resp);
	void resolverConAgregacion(const Consulta& consulta, Respuesta& resp);


	void actualizarIndices(const std::string& entrada, const Id_Registro& id);
	void calcularInterseccion(const Lista_Id& l1, const Lista_Id& l2, Lista_Id& destino);
	void calcularFiltros(const Consulta& consulta, Lista_Id& lista);
	void calcularEntradas(const Consulta& consulta, Lista_Id& lista);

	void obtenerIDs(const std::string& dimension, const std::string& valorDim, Lista_Id& lista);

	Lista_Id _interseccion; // no puedo tenerla tengo que hacer instancias
							// porque tiene que ser concurrente
	Indice <Dimension> *_indDimensiones;
	ConjuntoValoresDimension *_cnjDimensiones;
	Indice <Hecho> *_indHechos;

	IndiceDeFechas _indFechas;

	ArchivoDeDatos _archDatos;
};

#endif /* BASEDEDATOS_H_ */
