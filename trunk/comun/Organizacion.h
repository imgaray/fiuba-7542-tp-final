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

typedef std::pair<std::string, unsigned> parDeConjunto;
typedef std::map <std::string, unsigned> ConjuntoCampos;
typedef std::vector <std::string> vectorCampos;

/*
 (Ej de archivo de Modelo)

	.................................................
	:Dimensiones = { Vendedor, Marca, Producto, }	:
	:Hechos = { PrecioLista, PrecioVenta }			:
	:												:
	:...............................................:
*/


/**
 * @class Organizacion
 *  Esta clase estatica encargada de cargar, guardar el modole del Archivo,
 *	pudiendo consultar sobre sus dimensiones, hechos, y cantidades que hay de estos,
 *	es decir, se encarga de resolver toda cuestion que implicase al modelo.
 *	La clasificacion de la Organizacino es la siguiente, las Dimensiones estan conformadas
 *	por Dimensiones simples y Dimensiones Especiales,en los Hechos no existe esta distincion,
 *	siendo los Campos comformados por Dimensiones y Hechos,un ejemplo de clasificacion seria
 *	que los Campos simples estan conformados por Dimensiones Simples y Hechos.
 *	El funcionamiento de esta clase es solo de consulta para cuestiones que
 *	involucren al modelo de datos.
 */

class Organizacion {
public:
	/**
	 * @brief Carga los datos de la Informacion desde un archivo.
	 * @param rutaArchivo string que contiene la ruta del archivo. Si no se
	 * especifica la ruta se utilizara la ruta por defecto.
	 */
	static void cargarDefiniciones(const std::string& rutaArchivo = STR_NULA);

	/**
	 * @brief Indica si un campo de la Organizacion es una Dimension.
	 * @param nombreCampo campo a analizar.
	 * @return booleano que indica el resultado.
	 */
	static bool esDimension(const std::string& nombreCampo);

	/**
	 * @brief Indica si un campo de la Organizacion es un Hecho.
	 * @param nombreCampo campo a analizar.
	 * @return booleano que indica el resultado.
	 */
	static bool esHecho(const std::string& nombreCampo);

	/**
	 * @brief Indica si un campo de la Organizacion es una Dimension Especial.
	 * @param nombreCampo campo a analizar.
	 * @return booleano que indica el resultado.
	 */
	static bool esDimensionEspecial(const std::string& nombreCampo);

	/**
	 * @brief Devuelve el nombre de un campo segun su indice en la Organizacion. Si
	 * no existe un nombre para el indice argumento, se retorna un string nulo.
	 * @param indice es indice del Campo a recuperar.
	 * @retrun string que contiene el nombre del campo.
	 */
	static const std::string& nombreCampo(unsigned indice);

	/**
	 * @brief Devuelve el nombre de un campo simple segun su indice en la Organizacion. Si
	 * no existe un nombre para el indice argumento, se retorna un string nulo.
	 * @param indice es indice del Campo Simple a recuperar.
	 * @return string que contiene el nombre del Campo Simple recuperado.
	 */
	static const std::string& nombreCampoSimple(unsigned indice);

	/**
	 * @brief Devuelve el nombre de una Dimension segun su indice en la Organizacion. Si
	 * no existe un nombre para el indice argumento, se retorna un string nulo.
	 * @param indice es indice de la Dimension a recuperar.
	 * @return string que contiene la Dimension recuperada.
	 */
	static const std::string& nombreDimension(unsigned indice);

	/**
	 * @brief Devuelve el nombre de una Dimension segun su indice en la Organizacion. Si
	 * no existe un nombre para el indice argumento, se retorna un string nulo.
	 * @param indice es el indice de la Dimension Simple a recuperar.
	 * @return string que contiene la Dimesion Simple recuperada.
	 */
	static const std::string& nombreDimensionSimple(unsigned indice);

	/**
	 * @brief Devuelve el nombre de un Hecho segun su indice en la Organizacion. Si
	 * no existe un nombre para el indice argumento, se retorna un string nulo.
	 * @param indice es l indice del Hecho a recuperar
	 * @return string que contiene el Hecho recuperado.
	 */
	static const std::string& nombreHecho(unsigned indice);

	/**
	 * @brief Indica cual es el indice de un Campo segun su Nombre.
	 * @param campo nombre del Campo recuperar su indice.
	 * @return indice del campo.
	 */
	static unsigned indiceDeCampo(const std::string& campo);

	/**
	 * @brief Indica cual es el indice de un Campo Simple segun su Nombre.
	 * @param campo nombre del Campo Simple recuperar su indice.
	 * @return indice del Campo Simple.
	 */
	static unsigned indiceDeCampoSimple(const std::string& campo);


	/**
	 * @brief Indica la cantidad de Hechos en la Organización.
	 * @return cantidad de Hechos.
	 */
	static unsigned cantidadHechos();

	/**
	 * @brief Indica la cantidad de Dimensiones que posee la Organización.
	 * @return cantidad de Dimensiones.
	 */
	static unsigned cantidadDimensionesTotal();

	/**
	 * @brief Indica la cantidad de Dimensiones Simples que posee la Organización.
	 * @return cantidad de Dimensiones Simples.
	 */
	static unsigned cantidadDimensionesSimples();

	/**
	 * @brief Indica la cantidad de Campos que posee la Organización.
	 * @param cantidad de Campos.
	 */
	static unsigned cantidadCampos();

	/**
	 * @brief Indica la cantidad de Campos Simples que posee la Organizacion.
	 * @param cantidad de Campos Simples.
	 */
	static unsigned cantidadCamposSimples();

private:
	Organizacion() {}
	virtual ~Organizacion() {}

	/**
	 * @brief Carga las dimensiones que contendra la Organizacion a partir de un string.
	 * @param dimensiones string que contiene las Dimensiones a cargar.
	 */
	static void cargarDimensiones(const std::string& dimensiones);

	/**
	 * @brief Carga los hechos que contendra la Organizacion a partir de un string.
	 * @param hechos string que contiene los hechos a cargar.
	 */
	static void cargarHechos(const std::string& hechos);

	/**
	 * @brief borra un caracter de todo un string.
	 * @param palabra string al cual se eliminaran los caracteres.
	 * @param caracter char a borrar del string.
	 */
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
