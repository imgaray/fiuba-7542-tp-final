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

#define RUTA_ARCH_MODELO "./modelo.config"

/*
 * Clase encaragada de determinar y guardar los metadatos
 * refentes a la informacion guardada en el servidor.
 */

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
};

#endif /* ORGANIZACION_H_ */
