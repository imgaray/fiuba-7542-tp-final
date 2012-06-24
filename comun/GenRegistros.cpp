/*
 * GenRegistros.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#include "GenRegistros.h"
#include "Consulta.h"
#include "Respuesta.h"
#include <fstream>

int generarRandom (int cantMax) {
	float  r = (float)random() / (float) RAND_MAX;
	r = r * cantMax;
	int res = (int) r;

	return res;
}

void generarRegistros(BaseDeDatos& bdd, long cantReg) {
    Utilitario u;
	int cantVendedores = 15;
	std::string vendedores[] =
	{
	 "Luciano", "Francisco", "Sebastian", "Ricardo", "Augusto",
	 "Leonardo" ,"Ezequiel", "Oscar", "Miguel", "Alberto",
	 "Juan", "Santiago" , "Ignacio" , "Joaquin ", "Pedro"
	};


	int cantSucursales = 15;
	std::string sucursales[] = {
	"San Justo", "San Pedro", "San Salvador" ,"San Martin" , "Santo Thomas",
	"San Agustin", "San Nicolas", "San Escoliozios", "San Remo", "San Procto",
	"San Miguel", "San Gabriel", "San Julian", "San Mateo", "Avellaneda"
	};

	int cantMarcas= 10;
	std::string marcas[] = {
	"laptop", "Samsung", "Iphone", "Hp", "Marcapaso",
	"intel","IBM", "Commodore", "Genius", "MS"
	};

	int cantProductos = 10;
	std::string productos[] = {
	"e221", "Galaxy SII", "Xirix", "boligrafo", "x86",
	"notebook","Lithium", "i400", "Mouse optico", "Teclado"
	};

	int cantFechas = 20;
	std::string fechas[] = {
	"20002005" , "20020508" ,"20000501", "20030205", "20040702",
	"20011101" , "20030119" ,"20020701", "20020405", "20040752",
	"20011110" , "20020120" ,"20050708", "20030206", "20030702",
	"20011021" , "20050107" ,"20010505", "20030505", "20040502",
	};
	Consulta ca;
	std::string nomCampo;
	for (long i = 0; i < cantReg ; i++) {

		ca.limpiar();
		ca.definirComoConsultaAgente();

		for (unsigned r = 0; r < Organizacion::cantidadCampos() ; r++) {
			nomCampo = Organizacion::nombreCampo(r);
			if (nomCampo == "Vendedor")
				ca.agregarCampo(vendedores[generarRandom(cantVendedores)]);
			else if (nomCampo == "Sucursal")
				ca.agregarCampo(sucursales[generarRandom(cantSucursales)]);
			else if (nomCampo == "Fecha")
				ca.agregarCampo(fechas[generarRandom(cantFechas)]);
			else if (nomCampo == "Marca")
				ca.agregarCampo(marcas[generarRandom(cantMarcas)]);
			else if (nomCampo == "Producto")
				ca.agregarCampo(productos[generarRandom(cantProductos)]);
			else if (nomCampo == "PrecioLista" || nomCampo == "PrecioFinal" || Organizacion::esHecho(nomCampo))
				ca.agregarCampo(u.convertirAString(generarRandom(1000)));
			else
				ca.agregarCampo("CAMPOVACIO");

		}
		Respuesta res = bdd.agregarEntrada(ca);
		//std::cout << res.mensajeInterno();

/*
		std::cout << "RegNuevo: ";
		for (unsigned r = 0; r < ca.cantidadCampos() ; r++) {
			std::cout.width(15);
			std::cout.fill('.');
			std::cout << ca.campo(r);
			std::cout << "||";
		}
		std::cout << std::endl;
*/
	}

	std::cout << "+++++Se termino el Generar Registros+++++" << std::endl;
}

void generarArchivoRegistros(const std::string& ruta, long cantReg) {

	std::fstream archivo;
	archivo.open(ruta.c_str(), std::fstream::out);

	if (!archivo.is_open())
		throw "EL archivo para guardar registros no esta abierto";

	int cantVendedores = 15;
	std::string vendedores[] =
	{
	 "Luciano", "Francisco", "Sebastian", "Ricardo", "Augusto",
	 "Leonardo" ,"Ezequiel", "Oscar", "Miguel", "Alberto",
	 "Juan", "Santiago" , "Ignacio" , "Joaquin ", "Pedro"
	};


	int cantSucursales = 15;
	std::string sucursales[] = {
	"San Justo", "San Pedro", "San Salvador" ,"San Martin" , "Santo Thomas",
	"San Agustin", "San Nicolas", "San Escoliozios", "San Remo", "San Procto",
	"San Miguel", "San Gabriel", "San Julian", "San Mateo", "Avellaneda"
	};

	int cantMarcas= 10;
	std::string marcas[] = {
	"laptop", "Samsung", "Iphone", "Hp", "Marcapaso",
	"intel","IBM", "Commodore", "Genius", "MS"
	};

	int cantProductos = 10;
	std::string productos[] = {
	"e221", "Galaxy SII", "Xirix", "boligrafo", "x86",
	"notebook","Lithium", "i400", "Mouse optico", "Teclado"
	};

	int cantFechas = 20;
	std::string fechas[] = {
	"20002005" , "20020508" ,"20000501", "20030205", "20040702",
	"20011101" , "20030119" ,"20020701", "20020405", "20040752",
	"20011110" , "20020120" ,"20050708", "20030206", "20030702",
	"20011021" , "20050107" ,"20010505", "20030505", "20040502",
	};

	Utilitario u;

	std::string reg;
	std::string nomCampo;
	for (long i = 0 ; i < cantReg; i++) {

		reg.clear();

		for (unsigned r = 0; r < Organizacion::cantidadCampos() ; r++) {
			nomCampo = Organizacion::nombreCampo(r);
			if (nomCampo == "Vendedor")
				reg += vendedores[generarRandom(cantVendedores)];
			else if (nomCampo == "Sucursal")
				reg += sucursales[generarRandom(cantSucursales)];
			else if (nomCampo == "Fecha")
				reg += fechas[generarRandom(cantFechas)];
			else if (nomCampo == "Marca")
				reg += marcas[generarRandom(cantMarcas)];
			else if (nomCampo == "Producto")
				reg += productos[generarRandom(cantProductos)];
			else if (nomCampo == "PrecioLista" || nomCampo == "PrecioFinal" || Organizacion::esHecho(nomCampo))
				reg += u.convertirAString(generarRandom(1000));
			else
				reg += "CAMPOVACIO";

			reg += '\t';
		}


		archivo << reg;
		archivo << std::endl;
	}


	archivo.close();
}
