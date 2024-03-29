/*
 * GenRegistros.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#include "GenRegistros.h"
#include "Consulta.h"
#include "Respuesta.h"

int generarRandom (int cantMax) {
	float  r = (float)random() / (float) RAND_MAX;
	r = r * cantMax;
	int res = (int) r;

	return res;
}

void generarRegistros(BaseDeDatos& bdd, long cantReg) {
	int cantVendedores = 15;
	std::string vendedores[] =
	{
	 "Luciano", "Francisco", "Sebastian", "Ricardo", "Augusto",
	 "Leonardo" ,"Ezequiel", "Oscar", "Miguel", "Alberto",
	 "Juan", "Santiago" , "Ignacio" , "Joaquin", "Pedro"
	};


	int cantSucursales = 15;
	std::string sucursales[] = {
	"San Justo", "San Pedro", "San Salvador" ,"San Martin" , "Santo Thomas",
	"San Agustin", "San Nicolas", "San Escoliozios", "San Remo", "San Procto",
	"San Miguel", "San Gabriel", "San Julian", "San Mateo", "Avellaneda"
	};

	int cantProductos = 10;
	std::string productos[] = {
	"laptop e221", "IBM 386", "Iphone Xirix", "boligrafo Hp", "Marcapaso x86",
	"notebook intel","IBM Litium", "Commodore i400", "Mouse optico", "Teclado MS"
	};

	int cantFechas = 20;
	std::string fechas[] = {
	"20002005" , "20020508" ,"20000501", "20030205", "20040702",
	"20011101" , "20030119" ,"20020701", "20020405", "20040752",
	"20011110" , "20020120" ,"20050708", "20030206", "20030702",
	"20011021" , "20050107" ,"20010505", "20030505", "20040502",
	};


	int cantMarcas = 5;
	std::string marcas[] = { "Intel", "AMD", "Samsung", "Gateway", "Genius" };

	Consulta ca;
	std::string nomCampo;
	Utilitario util;
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
			else if (nomCampo == "Producto")
				ca.agregarCampo(productos[generarRandom(cantProductos)]);
			else if (nomCampo == "Marca")
				ca.agregarCampo(marcas[generarRandom(cantMarcas)]);
			else if (nomCampo == "PrecioLista" || nomCampo == "PrecioFinal" || Organizacion::esHecho(nomCampo))
				ca.agregarCampo(util.convertirAString(generarRandom(1000)));
			else
				ca.agregarCampo("CAMPOVACIO");
		}

		Respuesta res = bdd.agregarEntrada(ca);
		std::cout << "Msj Respuesta: " << res.mensajeInterno() << std::endl;

		std::cout << "RegNuevo: ";
		for (unsigned r = 0; r < ca.cantidadCampos() ; r++) {
			std::cout.width(15);
			std::cout.fill('.');
			std::cout << ca.campo(r);
			std::cout << "||";
		}
		std::cout << std::endl;

	}

	std::cout << "+++++Se termino el Generar Registros+++++" << std::endl;
}
