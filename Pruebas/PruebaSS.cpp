/*
 * PruebaSS.cpp
 *
 *  Created on: 15/06/2012
 *      Author: migue
 */

#include "PruebaSS.h"
#include <stdlib.h>

void testSS() {
	cout <<"============================================================"<< endl;
	cout << "inicia El test para Serializaciones a traves de Sockets" << endl;

	Consulta c[CANT_CONSULTAS_ENVIADAS];
	Respuesta r[CANT_RESPUESTAS_ENVIDAS];

	inicializarConsultas(c);
	inicializarRespuesta(r);


	ssEmisor emisor(c, r);
	ssReceptor receptor(c, r);

	receptor.iniciar();
	sleep(1);
	emisor.iniciar();

	emisor.sincronizar();
	receptor.sincronizar();


	int errores = emisor.cantErrores() + receptor.cantErrores();

	if (errores == 0) {
		cout << "Test Sin Errores++"<< endl;
	}
	else {
		cout << "Test con Errores: " << errores << endl;
		exit(0);
	}

	cout << "Fin de Test de Serializaciones a traves de Sockets"<< endl;
}


void inicializarConsultas(Consulta* cons) {

	cons[0].definirComoConsultaCliente();
	cons[0].definirID(12314);
	cons[0].agregarEntrada("Entrada", "ValorEntrada");


	cons[1].definirComoConsultaCliente();
	cons[1].definirID(0012);
	cons[1].definirConsultaDeTablaPivote();
	cons[1].agregarFiltro("Filtro", "ValorFiltro");
	cons[1].agregarXTablaP("ABSX1");
	cons[1].agregarYTablaP("ORDY1");
	cons[1].agregarXTablaP("ABSX2");
	cons[1].agregarYTablaP("ORDY2");
	cons[1].agregarResultado("HECHO");


	cons[2].definirComoConsultaAgente();
	cons[2].agregarCampo("HOLA");
	cons[2].agregarCampo("CHAU");
	cons[2].agregarCampo("TODOBIEN");
	cons[2].agregarCampo("SIBIEN");


	cons[3].definirComoConsultaCliente();
	cons[3].definirID(12313);
	cons[3].agregarFiltro("Filtro1", "ValorFiltro1");
	cons[3].agregarFiltro("Filtro2", "ValorFiltro2");
	cons[3].agregarEntrada("Entrada1", "valorEntrada1");
	cons[3].agregarEntrada("Entrada2", "valorEntrada2");

	cons[4].definirComoConsultaCliente();
	cons[4].definirID(1122);
	cons[4].agregarFiltro("Filtro1", "ValorFiltro1");
	cons[4].agregarFiltro("Filtro2", "ValorFiltro2");
	cons[4].agregarEntrada("Entrada1", "valorEntrada1");
	cons[4].agregarEntrada("Entrada2", "valorEntrada2");
	cons[4].agregarResultado("VENDODOR");
	cons[4].agregarResultado("COMPRADOR");

}

void inicializarRespuesta(Respuesta* resp) {
	resp[0].mensajeInterno("RESPUESTA NUM 1");
	resp[0].definirColumnas(2);
	resp[0].definirID(12312);
	resp[0].agregar("F11");
	resp[0].agregar("F12"); resp[0].filaCompletada();
	resp[0].agregar("F21");
	resp[0].agregar("F22");	resp[0].filaCompletada();
	resp[0].agregar("F31");
	resp[0].agregar("F32");


	resp[1].definirColumnas(4);
	resp[1].definirID(00312);
	resp[1].agregar("F11");
	resp[1].agregar("F12");
	resp[1].agregar("F13");
	resp[1].agregar("F14");	resp[1].filaCompletada();
	resp[1].agregar("F11");
	resp[1].agregar("F22");
	resp[1].agregar("F23");
	resp[1].agregar("F24"); resp[1].filaCompletada();



	resp[2].definirColumnas(4);
	resp[2].definirID(00312);
	resp[2].mensajeInterno("Respuesta Num 3");


	resp[3].definirColumnas(1);
	resp[3].definirID(1);
	resp[3].mensajeInterno("Respuesta Num 4");


	resp[4].definirID(23414);
	resp[4].definirColumnas(2);
	resp[4].mensajeInterno("Respuesta Num 5");
	resp[4].agregar("F11");
	resp[4].agregar("F12"); resp[4].filaCompletada();
	resp[4].agregar("F21");
	resp[4].agregar("F22");	resp[4].filaCompletada();
	resp[4].agregar("F31");
	resp[4].agregar("F32");
	resp[4].agregar("F41");
	resp[4].agregar("F42"); resp[4].filaCompletada();
	resp[4].agregar("F51");
	resp[4].agregar("F52");	resp[4].filaCompletada();
	resp[4].agregar("F61");
	resp[4].agregar("F62");
	resp[4].agregar("F71");
	resp[4].agregar("F72"); resp[4].filaCompletada();
	resp[4].agregar("F81");
	resp[4].agregar("F82");	resp[4].filaCompletada();
	resp[4].agregar("F91");
	resp[4].agregar("F92"); resp[4].filaCompletada();


}
