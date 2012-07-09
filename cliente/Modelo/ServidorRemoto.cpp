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
												Consulta consulta) {
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

bool ServidorRemoto::conectado() {
    return sock->conectado();
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
