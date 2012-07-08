/*
 * M_Fechas.h
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#ifndef M_FECHAS_H_
#define M_FECHAS_H_
#include "Definiciones.h"
#include <sstream>
#include "Utilitario.h"

/**
 *	@class M_Fechas
 *  Esta clase es la encargada de manejar fechas, para un uso mas comodo guardando
 *	dia, semana, mes, bimestre , trimestre, cuatrimeste, semestre para algun anio.
 *	Se encarga de manejar fechas simple o fechas compuestas, siendo las fechas simples
 *	fechas con formato comun numerico y las fechas compuestas serian semana, mes,
 *	bimestes, etc.
 */

class M_Fechas {
public:

	/**
	 * @brief Constructor sin argumentos.
	 */
	M_Fechas() {}
	virtual ~M_Fechas() {}
	/**
	 * Se ingresa fecha como "12-12-2012" y se retorna en el formato
	 * correcto utilazado para el índice
	 */
	Fecha fecha(const std::string& fechaComun)  const;
	bool esFechaConvecional(const std::string& fecha)  const;

	/**
	 * @brief Transforma dos Fechas en una Fecha Compuesta, que representa un rango de
	 * fechas.
	 * @param f1 Fecha que representara al limite inferior del rango
	 * @param f2 Fecha que representara al limite superior del rango
	 * @return Fecha Compuesta que comprede el rango de fechas.
	 */
	Fecha rango(const Fecha& f1,const Fecha& f2) const;

	/**
	 * @brief Transforma una fecha a partir de de los datos numericos de esta, al
	 * formato utilizado en la aplicacion.
	 * @param dia entero que representa al dia
	 * @param mes entero que representa al mes
	 * @param anio entero que representa al año
	 * @return Fecha con el formato utilizado.
	 */
	Fecha fecha(int dia, int mes, int anio) const;

	/**
	 * @brief A partir de un año se crea un Fecha Rango que corresponde a todo el año.
     * Que compredera las fechas comprendidas en ese periodo.
	 * @param anio entero que representa al año que se va a utilizar.
	 * @return Fecha
	 */
    Fecha anio(const std::string& anio) const;

    /**
     * @brief A partir de un año y un semestre se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param sem semestre del año (siendo 1 o 2)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha semestre(int sem, const std::string& anio) const;

    /**
     * @brief A partir de un año y un cuatrimestre se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param cuat cuatrimestre del año (siendo 1, 2 o 3)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha cuatrimestre(int cuat, const std::string& anio) const;

    /**
     * @brief A partir de un año y un trimestre se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param tri trimeste del año (siendo 1, 2, 3 o 4)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha trimestre(int tri, const std::string& anio) const;

    /**
     * @brief A partir de un año y un bimestre se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param bim bimestre del año (siendo 1, 2, 3, 4, 5 o 6)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha bimestre(int bim, const std::string& anio) const;

    /**
     * @brief A partir de un año y un mes se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param mes mes del año (siendo 1, 2, 3, ... , 10, 11 o 12)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha mes(int mes, const std::string& anio) const;

    /**
     * @brief A partir de un año y un semama se crea una Fecha de Rango.
     * Que compredera las fechas comprendidas en ese periodo.
     * @param semana semana del año (siendo desde 1 hasta 53)
     * @param anio año de la Fecha
     * @retur Fecha que representa el rango
     */
	Fecha semana(int semana, const std::string& anio) const;

	/**
	 * @brief Indica si una Fecha es Rango(o Compuesta).
	 * @param fecha Fecha a analizar
	 * @return booleano indicando el resultado.
	 */
	bool esRango(const Fecha& fecha) const;

	/**
	 * @brief Indica si una Fecha es simple, es decir, que no es Rango.
	 * @param fecha Fecha a analizar.
	 * @return booleano indicando el resultado.
	 */
	bool esSimple(const Fecha& fecha) const;

	/**
	 * @brief Descompone una Fecha Rango en dos fechas que compreden
	 * el perido que representaba el rango.
	 * @param rango Fecha Rango a desarmar
	 * @param f1 Fecha inferior del rango a escribir
	 * @param f2 Fecha superior del rango a escribir
	 */
	void desarmar(const Fecha& rango, Fecha& f1, Fecha& f2) const;

	/**
	 * @brief Transforma una Fecha con el formato utilizado en un representacion
	 * numerica de esta.
	 * @param fecha Fecha a transformar
	 * @return Valor numerico que representa la Fecha parametro.
	 */
	FechaNumerica convertir(const Fecha& fecha) const;

	/*@brief Trasnforma una Fecha desde su representacion numerica en el formato
	 * tradicional utilizado por la aplicaión.
	 * @param fecha valor numerico de la fecha.
	 * @return Fecha en el formato comun.
	 */
	Fecha convertir(const FechaNumerica& fecha) const;

	/*@brief Trasnforma una Fecha desde su representacion numerica en el formato
	 * tradicional utilizado por la aplicaión.
	 * @param fecha valor numerico de la fecha.
	 * @param ancho indica el tamaño de digitos que tendra la Fecha transformada.
	 * @return Fecha en el formato comun.
	 */
	Fecha convertir(const FechaNumerica& fecha, int ancho) const;
private:

private:
	void desarmarMes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarBimes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarTrimes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarCuatrimes(const Fecha& rango, Fecha& f1, Fecha& f2)  const;
	void desarmarSemes(const Fecha& rango, Fecha& f1, Fecha& f2)  const;
	void desarmarAnio(const Fecha& rango, Fecha& f1, Fecha& f2)  const;


	void desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul)  const;
	void armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha)  const;

	void calcularDia(const int& diaAnio,const FechaNumerica& anio, int& dia, int& mes) const;
};

#endif /* M_FECHAS_H_ */
