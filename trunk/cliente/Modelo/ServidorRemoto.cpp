#include "ServidorRemoto.h"
#include "Consultante.h"
#include <string>
#include <cerrno>
#include <cstring>
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
		crespuesta(respuestas, consultantes, sock, cancelados),
		cconsulta(consultas, respuestas, sock, cancelados) {
	std::string aux = RUTACONFIGURACIONSR;
	ArchivoConfiguracion archivo(aux.c_str());
	aux = ATRIBPUERTO;
	std::string spuerto = archivo.obtenerAtributo(aux);
	aux = ATRIBDIRECCION;
	sdireccion = archivo.obtenerAtributo(aux);
	Puerto puerto;
	convertir(spuerto, puerto);
	sock = new Socket(puerto);
}

void ServidorRemoto::conectar() throw(char* ) {
	sock->conectar(sdireccion);
	if (!sock->conectado()) {
		throw strerror(errno);
	}
	cconsulta.iniciar();
	crespuesta.iniciar();
}

void ServidorRemoto::enviarConsulta(Consultante* consultante,
												Consulta& consulta) {
	if (!consultantes.has(consultante->getID())) {
		consultantes[consultante->getID()] = consultante;
	}
	/// sdf
	ParConsulta par;
	par.first = consultante->getID();
	par.second = consulta;
	par.second.definirID(par.first);
	consultas.push(par);
}

void ServidorRemoto::cancelarConsulta(unsigned IDcons) {
	cancelados[IDcons] = true;
}

unsigned ServidorRemoto::cantidadRespuestas() {
	return respuestas.size();
}

Respuesta ServidorRemoto::obtenerRespuesta() {
	Respuesta ret = respuestas.front().second;
	respuestas.pop();
	return ret;
}

ServidorRemoto::~ServidorRemoto() {
	sock->desconectar();
	consultas.close();
	respuestas.close();
	if (cconsulta.corriendo())
		cconsulta.sincronizar();
	if (crespuesta.corriendo())
		crespuesta.sincronizar();
	delete sock;
}
