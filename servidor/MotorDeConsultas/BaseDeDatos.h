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

/**
 * @class Esta clase es la encargada de resolver las todos los tipos de consultas
 * hechas por un cliente y/o agente.
 */

class BaseDeDatos {
public:
	/**
	 * @brief Constructor que recibe la ruta del archivo de datos.
	 * @param rutaArchivo string que contiene la ruta del archivo
	 */
	BaseDeDatos(const std::string rutaArchivo = "ruta.txt");

	/**
	 * @brief Resuelve una Consulta y retorna la Respuesta de esta.
	 * @param consulta es la Consulta a resolver
	 * @return respuesta que contiene los datos de la consulta resuelta.
	 */
	Respuesta resolverConsulta(const Consulta& consulta);

	/**
	 * @brief Agrega una entrada por parte del agente.
	 * @param entrada es la Consulta que recive por parte del agente.
	 * @return respuesta que contiene informacion del estado de la resolucion de la entrada.
	 */
	Respuesta agregarEntrada(const Consulta& entrada);

	/**
	 * @brief Metodo que deja a la base de datos vacia.
	 */
	void borrarDatos();

	virtual ~BaseDeDatos();
//private:
	/**
	 * @brief Resuelve una consulta con tabla pivote.
	 * @param consulta es la Consulta que se tiene que resolver.
	 * @param resp es la Respuesta que se tiene que modificar para enviar
	 */
	void resolverTablaPivote(const Consulta& consulta, Respuesta& resp);

	/**
	 * @brief Resuelve una consulta en forma simple. Tabla de resultados
	 * @param consulta es la Consulta que se tiene que resolver
	 * @param respuesta es la Respuesta que se tiene que modificar para enviar
	 */
	void resolverConsultaNormal(const Consulta& consulta, Respuesta& respuesta);

	/**
	 * @brief Actualiza los indices con una entrada de registros y con el id de ese registro
	 * @param entrada registro que contiene los datos para actualizar los indices
	 * @param id identificador del registro.
	 */
	void actualizarIndices(const std::string& entrada, const Id_Registro& id);

	/**
	 * @brief Calcula interseccion de dos lista l1 y l2, y almacena el resultado en destino
	 * @param l1 es la primer lista a calcular la interseccion
	 * @param l2 es la segunda lista a calcular la interseccion
	 * @param destino es la lista donde se guardara el resultado de la interseccion
	 */
	void calcularInterseccion(const Lista_Id& l1, const Lista_Id& l2, Lista_Id& destino) const;

	/**
	 * @brief Calcula los Filtros de una consulta y guarda los id filtrados en lista
	 * @param consulta es la consulta que contiene los filtros y sus valores
	 * @param lista es la Lista donde se guardan los id de los campos filtrados
	 */
	void calcularFiltros(const Consulta& consulta, Lista_Id& lista) const;

	/**
	 * @brief Calcula las Entradas de una consulta y guarda los id filtrados en lista
	 * @param consulta es la consulta que contiene las entradas y sus valores
	 * @param lista es la Lista donde se guardan los id de los campos filtrados
	 */
	void calcularEntradas(const Consulta& consulta, Lista_Id& lista) const;


	/**
	 * @brief Retorna un bool indicando si hubo filtrado de datos y si es asi
	 * se guardan se los ids filtrados en listaReg.
	 * @param consulta es la Consulta que contiene los datos por los cual filtrar
	 * @param listaReg lista donde se almacenaran los ids de registro filtrados
	 * @return booleano indicando si hubo algun tipo de filtrado en la consulta.
	 */
	bool filtrarDatos(const Consulta& consulta, Lista_Id& listaReg) const;

	/**
	 * @brief Retorna un bool indicando si se tienen que filtrar datos de hechos
	 * (desde Filtros o desde Entradas).
	 * @param consulta es la Consulta a comprobar
	 * @return booleano indicando si hay filtros en hechos
	 */
	bool hayFiltrosDeHechos(const Consulta& consulta) const;
	/**
	 * @brief Retorna un bool indicando si hay al menos una Dimension en los Resultados de la Consulta
	 * (desde Filtros o desde Entradas).
	 * @param consulta es la Consulta a comprobar
	 * @return booleano indicando si hay dimensiones en resultados
	 */
	bool hayResultadosDeDimensiones(const Consulta& consulta) const;

	/*
	 * @brief Guarda las distintans combinaciones de dimensiones en MapaCombinacions y guardando
	 * para combinacino un conjunto de id que pertenecen a esa combinacion.
	 * @param consulta es la Consulta a resolver
	 * @param lReg lista con los ids que se tiene que recuperar y analizar.
	 * @param mCombinaciones mapa donde se almacenaran las combinaciones de las dimensiones de los registros con sus ids
	 * @param filtrarHechos booleano indicando si se tiene que filtrar los hechos en los registros.
	 */
	void guardarCombinaciones(const Consulta& consulta, Lista_Id& lReg, MapaCombinaciones& mCombinaciones, bool filtrarHechos);

	/*
	 * @brief Guarda las distintans combinaciones de dimensiones en MapaCombinacions y guardando
	 * para combinacino un conjunto de id que pertenecen a esa combinacion.
	 * @param consulta es la Consulta a resolver
	 * @param mCombinaciones mapa donde se almacenaran las combinaciones de las dimensiones de los registros con sus ids
	 * @param filtrarHechos booleano indicando si se tiene que filtrar los hechos en los registros.
	 */
	void guardarCombinaciones(const Consulta& consulta, MapaCombinaciones& mCombinaciones, bool filtrarHechos);

	/**
	 * @brief Guarda las distintans combinaciones de dimensiones en MapaCombinacions y guardando
	 * para combinacino un conjunto de id que pertenecen a esa combinacion,para resolver una
	 * Consulta de Tabla Pivote.
	 * @param consulta es la Consulta a resolver
	 * @param mCombinaciones mapa donde se almacenaran las combinaciones de las dimensiones de los registros con sus ids
	 * @param filtrarHechos booleano indicando si se tiene que filtrar los hechos en los registros.
	 * @param lReg puntero a Lista_Id que contiene los registros a recuperar para analizar, si es nulo recupera todos los registros
	 */
	void guardarCombinacionesTP(const Consulta& consulta, MapaCombinaciones& mCombinaciones, bool filtrarHechos, Lista_Id* lReg = NULL);


	/**
	 * @brief Realiza las agregaciones para un MapaCombinaciones partiendo de los ids de cada combinacion y
	 * los guarda en Respuesta.
	 * @param consulta es la Consulta a que contiene las .....................
	 * @param mCombinaciones mapa donde que contiene las combinaciones de las dimensiones de los registros con sus ids
	 * @param respuesta es la Respuesta a escribir que se va a enviar
	 */
	void hacerAgregaciones(const Consulta& consulta, const MapaCombinaciones& mCombinaciones, Respuesta& respuesta);

	/**
	 * @brief Hace las agregaciones correspondiente para dos conjunto de Combinaciones
	 * que representa al grupo X e Y. Guardando los resoluciones en "respuesta".
	 * @param cX es la consulta que contiene los resultados del grupo X de la tabla pivote
	 * @param mCombX mapa de combinaciones de dimensiones y hechos del grupo X con sus ids correspondientes
	 * @param cY es la consulta que contiene los resultados del grupo Y de la tabla pivote
	 * @param mCombY mapa de combinaciones de dimensiones y hechos del grupo Y con sus ids correspondientes
	 * @param cons es la Consulta raiz a resolver.
	 * @param respuesta es la Respuesta a escribir y enviar.
	 */
	void hacerAgregacionesTP(const Consulta& cX,
			const MapaCombinaciones& mCombX,
			const Consulta& cY,
			const MapaCombinaciones& mCombY,
			const Consulta& cons,
			Respuesta& respuesta);

	/**
	 * @brief Realiza el calculo de una Agregacion para el resultado de la Consulta y lo almacena en
	 * campoRes.
	 * @param ids lista contiendo los ids de los registros a agregar.
	 * @param cons es la Consulta de Tabla Pivote a resolver, que contiene la agregacion del resultado.
	 * @param campoRes string que donde se guardara la agregacion hecha para los registros.
	 */
	void calcularAgregacionTP(const Lista_Id& ids, const Consulta& cons, std::string& campoRes);

	/**
	 * @brief Hace la agregacion para una Fila de una Respuesta a partir de una combinacion y sus ids de registros.
	 * @param consulta .................................
	 * @param combinacion ..............................
	 * @param ids lista que contiene los ids de registros.
	 * @param resp es la Respuesta a escribir que se enviara.
	 */
    void agregaParaFila(const Consulta& consulta, const Combinacion& combinacion,const Lista_Id& ids, Respuesta& resp);


	/**
	 * @brief Calcula la agragacion para un hecho almacenandola en "acumulador"
	 * @param agregacion enumeracion del tipo de agregacion.
	 * @param acumulador es la variable donde se almacena el resultado parcial de la agregacion actual.
	 * @param aAgregar valor que se añadira segunla agregacion al valor del acumulador.
	 */
	void calcularAgregacion(const Agregacion& agregacion, unsigned& acumulador, unsigned aAgregar) const;

	/**
	 * @brief Calcula la agregacion de PROM para un hecho guardando el resultado parcial en "acumulador".
	 * @param acumulador variable donde se almacena el promedio parcial
	 * @param cantidad cantidad de las totalidad de los datos promediados
	 * @param nuevoHecho nuevo valor que se añadira al promedio
	 */
	void calcularPromedio(unsigned& acumulador, unsigned& cantidad, const unsigned& nuevoHecho) const;


	/**
	 * @brief metodo simple para resolver una consulta rapido, metodo de prueba no debe usarse.
	 *
	 */
	void __guardarRegistros(const Consulta& cons, Respuesta& resp);

	/**
	 * @brief Guarda los hechos filtrados en un lista de ids en la respuesta, haciendo
	 * la agregacion o no dependiendo de la consulta.
	 * @param cons que contiene los resultados solo con hechos
	 * @param ids lista que contiene los ids los registros a analizar
	 * @param resp Respuesta donde se guardaran los hechos calculados.
	 */
	void guardarHechos(const Consulta& cons,const Lista_Id& ids, Respuesta& resp);

	/**
	 * @brief Guarda los hechos para todos los en la respuesta, haciendo
	 * la agregacion o no dependiendo de la consulta.
	 * @param cons que contiene los resultados solo con hechos
	 * @param resp Respuesta donde se guardaran los hechos calculados.
	 */
	void guardarHechos(const Consulta& cons, Respuesta& resp);

	/**
	 * @brief Retorna un bool indicando si se tienen que agregar los hechos en los
	 * resultados.
	 * @param cons es la Consulta que contiene
	 * @param indice vector de unsigned donde se almacenara los numero de indice de los campos
	 * de resultados de la Consulta.
	 * @return booleano indicando si hay agregacion en los hechos o no.
	 */
	bool aplicarAgregacionHechos(const Consulta& cons, std::vector <unsigned>& indice) const;

	/**
	 * @brief Carga los indices segun los datos guardados en el archivo de Datos.
	 */
	void cargarIndices();

	/**
	 * @brief Imprime un registro completo segun su id.
	 * @param id identificador del registro a imprimir
	 */
	void imprimirRegistro(Id_Registro id);

private:
	Lista_Id _interseccion; // no puedo tenerla tengo que hacer instancias
							// porque tiene que ser concurrente
	Indice <Dimension> *_indDimensiones;

	IndiceDeFechas _indFechas;

	ArchivoDeDatos _archDatos;
	unsigned _cantDimensionesSimples;

	Mutex _mutex;
};

#endif /* BASEDEDATOS_H_ */
