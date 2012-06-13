#include "ServidorRemoto.h"
#include "Consultante.h"
#include <string>
#define RUTACONFIGURACIONSR "servRemoto.conf"
#define ATRIBPUERTO "puerto_servidor"
#define ATRIBDIRECCION "direccion_servidor"

template <class T, class Y>
void convertir(T& objetivo, Y& destino) {
	std::stringstream st;
	st << objetivo;
	st >> destino;
}

void imprimirRespuesta(Respuesta& r) {

	std::cout << ">>>Datos de Respuesta: " << r.serializar() << std::endl;
	if (r.mensajeInterno() == Respuesta::respuestaValida) {
		std::cout <<">>> Cant Filas: " << r.cantidadFilas()<< std::endl;
		std::cout <<">>> Cant Columnas: " << r.cantidadColumnas()<< std::endl;
	}
	std::cout << std::endl << "Mensaje Respuesta: " << r.mensajeInterno() << std::endl;
	for (unsigned i = 0; i < r.cantidadFilas(); i++) {
		std::cout << "::";
		for (unsigned j = 0; j < r.cantidadColumnas(); j++) {
			std::cout.width(11);
			std::cout.fill('.');
			std::cout << r.dato(i,j) << "|";
		}
		std::cout << std::endl;
	}
}

ServidorRemoto::ServidorRemoto():
		crespuesta(respuestas, consultantes)/*,
		cconsulta(consultas, respuestas)*/
		 {
	for(unsigned i = 0; i < MAX_OPEN_PORTS; ++i) {
		cconsultas.push_back(new ConsumerConsulta(consultas, respuestas));
	}
	conectar();
}

void ServidorRemoto::conectar() throw() {	
	/*cconsulta.conectar();
	cconsulta.iniciar();*/
	std::list<ConsumerConsulta*>::iterator iter;
	for (iter = cconsultas.begin(); iter != cconsultas.end(); ++iter) {
		(*iter)->conectar();
		(*iter)->iniciar();
	}
	crespuesta.iniciar();
}

void ServidorRemoto::enviarConsulta(Consultante* consultante, Consulta consulta) {
	if (!consultantes.has(consultante->getID())) {
		consultantes[consultante->getID()] = consultante;
	}
	ParConsulta par;
	par.first = consultante->getID();
	par.second = new Consulta(consulta);
	consultas.push(par);
}

void ServidorRemoto::cancelarConsulta(unsigned IDcons) {
    std::cout << "@todo void ServidorRemoto::cancelarConsulta(unsigned )" << std::endl;
}

ServidorRemoto::~ServidorRemoto()  {
	consultas.close();
	respuestas.close();
	/*if (cconsulta.corriendo())
		cconsulta.sincronizar();*/
	std::list<ConsumerConsulta*>::iterator iter;
	for (iter = cconsultas.begin(); iter != cconsultas.end(); ++iter) {
		if ((*iter)->corriendo())
			(*iter)->sincronizar();
		delete *iter;
	}
	if (crespuesta.corriendo())	
		crespuesta.sincronizar();
}
