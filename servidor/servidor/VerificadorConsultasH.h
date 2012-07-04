/*
 * VerificadorConsultasH.h
 *
 *  Created on: 09/06/2012
 *      Author: migue
 */

#ifndef __VALIDADORCONSULTAS_H
#define __VALIDADORCONSULTAS_H

class Consulta;

class VerificadorConsultasH {
public:
	/**
	 * @brief Analiza una consulta verificando su contenido para comprobar
	 * que esta bien formada.
	 * @param consulta Consulta a analizar.
	 * @return booleano indicando si la consulta esta correctamente formada.
	 */
	bool verificarConsulta(const Consulta& consulta);

	/**
	 * @brief Constructor sin argumento.
	 */
	VerificadorConsultasH() {}
	~VerificadorConsultasH() {}
private:
	/**
	 * @brief Indica si hay dimensiones en los resultados de la Consulta.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si hay dimensiones.
	 */
	bool hayDimesionesEnRes(const Consulta& cons);

	/**
	 * @brief Indica si hay hechos en los resultados de la Consulta.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si hay hechos.
	 */
	bool hayHechosEnRes(const Consulta& cons);

	/**
	 * @brief Indica si hay agregaciones en los hechos de la Consulta.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si hay agregaciones.
	 */
	bool hayAgregacionesEnHechos(const Consulta& cons);

	/**
	 * @brief Indica si los filtros de la Consulta son correctos.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si la consulta tiene filtros correctos.
	 */
	bool filtrosCorrectos(const Consulta& cons);

	/**
	 * @brief Indica si las entradas de la Consulta son correctos.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si la consulta tiene entradas correctas.
	 */
	bool entradasCorrectos(const Consulta& cons);

	/**
	 * @brief Indica si los resultados de la Consulta son correctos.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si los resultados son correctos.
	 */
	bool resultadoCorrectos(const Consulta& cons);

	/**
	 * @brief Indica si los campos que hay para la Tabla pivote de la Consulta
	 * son correctos.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si los campos son correctos.
	 */
	bool camposTablaPivoteCorrectos(const Consulta& cons);

	/**
	 * @brief Indica si en la Consulta hay alguno campo o valor de campo Nulo.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si la consulta es tiene datos no nulos.
	 */
	bool hayCamposNulos(const Consulta& cons);

	/**
	 * @brief Indica si la consulta del Cliente esta correctamente formada.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si la consulta es correcta.
	 */
	bool cClienteValida(const Consulta& cons);

	/**
	 * @brief Indica si la consulta de Tabla Pivote del Cliente esta correctamente
	 * formada.
	 * @param cons Consulta a analizar
	 * @return booleano indicando si la consulta es correcta.
	 */
	bool cClienteTP(const Consulta& cons);
};

#endif
