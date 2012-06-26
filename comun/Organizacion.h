/*
 * Organizacion.h
 *
 *  Created on: 03/06/2012
 *      Author: migue
 */

#ifndef ORGANIZACION_H_
#define ORGANIZACION_H_
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Definiciones.h"
#include "Utilitario.h"

#define RUTA_ARCH_MODELO "./modelo.config"

/*
 * @DOC:
						Clase Organizacion

	Esta clase estatica encargada de cargar, guardar el modole del Archivo,
	pudiendo consultar sobre sus dimensiones, hechos, y cantidades que hay de estos,
	es decir, se encarga de resolver toda cuestion que implicase al modelo.
	El funcionamiento de esta clase es solo de consulta para cuestiones que
	involucren al modelo de datos.

Atributos:
	static std::fstream _archModelo: stream que guarda los datos del modelo en disco
*
	static ConjuntoCampos _dimensiones: contenedor encargado de guardar las dimensiones.
*
	static ConjuntoCampos _hechos: contenedor encargado de guardar los hechos.
*
	static vectorCampos _campos: contenedor encargado de guardar todos los campos del modelo
	(dimensiones y hechos).
*
	static std::string nombreNulo: string nulo para referenciarlo como un string vacio.
*
	static bool _existeCampoEspecial: booleano indicando si existe alguna Dimension Especial.
*
	static unsigned _indEspecial: posicion que indica en que campo esta la Dimension Especial.
*
    static Utilitario u: encargado de hacer operaciones y calculos auxiliares.

 * @END
 * */

/*
 (Ej de archivo de Modelo)

	.................................................
	:Dimensiones = { Vendedor, Marca, Producto, }	:
	:Hechos = { PrecioLista, PrecioVenta }			:
	:												:
	:...............................................:
*/

typedef std::pair<std::string, unsigned> parDeConjunto;
typedef std::map <std::string, unsigned> ConjuntoCampos;
typedef std::vector <std::string> vectorCampos;

class Organizacion {
public:
	static void cargarDefiniciones(const std::string& rutaArchivo = STR_NULA);

	static bool esDimension(const std::string& nombreCampo);
	static bool esHecho(const std::string& nombreCampo);
	static bool esDimensionEspecial(const std::string& nombreCampo);

	static const std::string& nombreCampo(unsigned indice);
	static const std::string& nombreCampoSimple(unsigned indice);

	static const std::string& nombreDimension(unsigned indice);
	static const std::string& nombreDimensionSimple(unsigned indice);
	static const std::string& nombreHecho(unsigned indice);

	static unsigned indiceDeCampo(const std::string& campo);
	static unsigned indiceDeCampoSimple(const std::string& campo);

	static unsigned cantidadHechos();
	static unsigned cantidadDimensionesTotal();
	static unsigned cantidadDimensionesSimples();
	static unsigned cantidadCampos();
	static unsigned cantidadCamposSimples();

private:
	Organizacion() {}
	virtual ~Organizacion() {}

	static void cargarDimensiones(const std::string& dimensiones);
	static void cargarHechos(const std::string& hechos);
	static void borrarCaracter(std::string& palabra, const char caracter);

	static std::fstream _archModelo;
	static ConjuntoCampos _dimensiones;
	static ConjuntoCampos _hechos;
	static vectorCampos _campos;
	static std::string nombreNulo;
	static bool _existeCampoEspecial;
	static unsigned _indEspecial;
    static Utilitario u;
};

#endif /* ORGANIZACION_H_ */
