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
#include "../../comun/Utilitario.h"
#include <map>
#include "Mutex.h"

class Respuesta;
class Consulta;


/*
 * @DOC:
						Clase BaseDeDatos

	Esta clase es la encargada de resolver las todos los tipos de consultas
	hechas por un cliente y/o agente.

Atributos:

	Indice <Dimension> *_indDimensiones: es vector dinamico que contiene los
	indices de ids de registro que se utilizaran para filtrar los datos en
	la resolucion de una consulta.
 *
	IndiceDeFechas _indFechas: es un indice especial utilizado para guardar
	los id de registros y filtrarlos a partir de una gran cantidad de
	diferentes tipos de rangos.
 *
	ArchivoDeDatos _archDatos: clase que se encarga de almacenar los registros
	en disco y permite acceder a estos a partir de su id cuando sea necesario
 *
	unsigned _cantDimensionesSimples: se utiliza para tener la cantidad de dimensiones
	simples que poseen por parte del Modelo.
 * @END
 * */

class BaseDeDatos {
public:
	BaseDeDatos(const std::string rutaArchivo = "ruta.txt");

	/*
	 * Resuelve una Consulta y retorna la Respuesta de esta.
	 */
	Respuesta resolverConsulta(const Consulta& consulta);

	/*
	 * Agrega una entrada por parte del agente
	 */
	Respuesta agregarEntrada(const Consulta& entrada);

	/*
	 * Metodo que deja a la base de datos vacia.
	 */
	void borrarDatos();

	virtual ~BaseDeDatos();
//private:
	/*
	 * Resuelve una consulta con tabla pivote
	 */
	void resolverTablaPivote(const Consulta& consulta, Respuesta& resp);

	/*
	 * Resuelve una consulta en forma simple. Tabla de resultados
	 */
	void resolverConsultaNormal(const Consulta& consulta, Respuesta& respuesta);

	/*
	 * Actualiza los indices con una entrada de registros y con el id de ese registro
	 */
	void actualizarIndices(const std::string& entrada, const Id_Registro& id);

	/*
	 * Calcula interseccion de dos lista l1 y l2, y almacena el resultado en destino
	 */
	void calcularInterseccion(const Lista_Id& l1, const Lista_Id& l2, Lista_Id& destino) const;

	/*
	 * Calcula los Filtros de una consulta y guarda los id filtrados en lista
	 */
	void calcularFiltros(const Consulta& consulta, Lista_Id& lista) const;

	/*
	 * Calcula las Entradas de una consulta y guarda los id filtrados en lista
	 */
	void calcularEntradas(const Consulta& consulta, Lista_Id& lista) const;


	/*
	 * Retorna un bool indicando si hubo filtrado de datos y si es asi
	 * se guardan se los ids filtrados en listaReg
	 */
	bool filtrarDatos(const Consulta& consulta, Lista_Id& listaReg) const;

	/*
	 * Retorna un bool indicando si se tienen que filtrar datos de hechos
	 * (desde Filtros o desde Entradas).
	 */
	bool hayFiltrosDeHechos(const Consulta& consulta) const;
	bool hayResultadosDeDimensiones(const Consulta& consulta) const;

	/*
	 * Guarda las distintans combinaciones de dimensiones en MapaCombinacions y guardando
	 * para combinacino un conjunto de id que pertenecen a esa combinacion
	 */
	void guardarCombinaciones(const Consulta& consulta, Lista_Id& lReg, MapaCombinaciones& mCombinaciones, bool filtrarHechos);
	void guardarCombinaciones(const Consulta& consulta, MapaCombinaciones& mCombinaciones, bool filtrarHechos);

	/*
	 * Guarda las distintans combinaciones de dimensiones en MapaCombinacions y guardando
	 * para combinacino un conjunto de id que pertenecen a esa combinacion,
	 * para resolver una Consulta de Tabla Pivote
	 */
	void guardarCombinacionesTP(const Consulta& consulta, MapaCombinaciones& mCombinaciones, bool filtrarHechos, Lista_Id* lReg = NULL);
	//void guardarCombinacionesTP(const Consulta& consulta, MapaCombinaciones& mCombinaciones, bool filtrarHechos);


	/*
	 * Realiza las agregaciones para un MapaCombinaciones partiendo de los ids de cada combinacion y
	 * los guarda en Respuesta.
	 */
	void hacerAgregaciones(const Consulta& consulta, const MapaCombinaciones& mCombinaciones, Respuesta& respuesta);

	/*
	 * Hace las agregaciones correspondiente para dos conjunto de Combinaciones
	 * que representa al grupo X e Y. Guardando los resoluciones en "respuesta"
	 */
	void hacerAgregacionesTP(const Consulta& cX,
			const MapaCombinaciones& mCombX,
			const Consulta& cY,
			const MapaCombinaciones& mCombY,
			const Consulta& cons,
			Respuesta& respuesta);

	/*
	 * Realiza el calculo de una Agregacion para un resultado y lo guarda en
	 * campoRes.
	 */
	void calcularAgregacionTP(const Lista_Id& ids, const Consulta& cons, std::string& campoRes);

	/*
	 * Hace la agregacion para una Fila de una Respuesta a partir de una combinacion y sus ids de registros
	 */
    void agregaParaFila(const Consulta& consulta, const Combinacion& combinacion,const Lista_Id& ids, Respuesta& resp);


	/*
	 * Calcula la agragacion para un hecho almacenandola en "acumulador"
	 */
	void calcularAgregacion(const Agregacion& agregacion, unsigned& acumulador, unsigned aAgregar) const;
	/*
	 * Calcula la agregacion de PROM para un hecho guardando el resultado parcial en "acumulador"
	 */
	void calcularPromedio(unsigned& acumulador, unsigned& cantidad, const unsigned& nuevoHecho) const;


	// metodo simple para resolver una consulta rapido
	void __guardarRegistros(const Consulta& cons, Respuesta& resp);

	/*
	 * Guarda los hechos filtrados en un lista de ids en la respuesta, haciendo
	 * la agregacion o no dependiendo de la consulta.
	 */
	void guardarHechos(const Consulta& cons,const Lista_Id& ids, Respuesta& resp);

	/*
	 * Guarda los hechos para todos los en la respuesta, haciendo
	 * la agregacion o no dependiendo de la consulta
	 */
	void guardarHechos(const Consulta& cons, Respuesta& resp);

	/*
	 * Retorna un bool indicando si se tienen que agregar los hechos en los
	 * resultados
	 */
	bool aplicarAgregacionHechos(const Consulta& cons, std::vector <unsigned>& indice) const;


	void cargarIndices();

	void imprimirRegistro(Id_Registro id);

private:
	Lista_Id _interseccion; // no puedo tenerla tengo que hacer instancias
							// porque tiene que ser concurrente
	Indice <Dimension> *_indDimensiones;

	IndiceDeFechas _indFechas;

	ArchivoDeDatos _archDatos;
	unsigned _cantDimensionesSimples;
	//Utilitario u;


	Mutex _mutex;
};

#endif /* BASEDEDATOS_H_ */
