#include "ConsumerConsultas.h"
#include <sstream>
#include <iostream>

template <class T, class Y>
void convertir(T& objetivo, Y& destino) {
	std::stringstream st;
	st << objetivo;
	st >> destino;
}

void ConsumerConsulta::detener_hilo() {
	servidor->desconectar();
	parar();
}

void ConsumerConsulta::correr() {
	while (corriendo()) {
		if (servidor && servidor->conectado()) {
			try {
				std::cout << "estoy en consumer consulta, procesando" << std::endl;
				bool error = false;
				ParConsulta pconsulta = consultas.pop2();
				std::cout << "pase el pop2, tengo una consulta para " << pconsulta.first << std::endl;
				ParRespuesta parrta;
				parrta.first = pconsulta.first;
				parrta.second = new Respuesta();
				if (servidor->enviar(*pconsulta.second)) {
					error = servidor->recibir(*(parrta.second));
					std::cout << "recibi la respuesta para "<< parrta.first << std::endl;
				}
				delete pconsulta.second;
				if (error) {
					detener_hilo();
				} else {
					respuestas.push(parrta);
				}
			} catch(...) {
				std::cout << "estan deteniendo el consumer consulta" << std::endl;
				detener_hilo();
			}
		}
	}
}

ConsumerConsulta::ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp):
	consultas(cons), respuestas(resp) {
	std::string aux = RUTACONFIGURACIONSR;
	ArchivoConfiguracion archivo(aux.c_str());
	aux = ATRIBPUERTO;
	std::string spuerto = archivo.obtenerAtributo(aux);
	aux = ATRIBDIRECCION;
	std::string sdireccion = archivo.obtenerAtributo(aux);
	Puerto puerto;
	convertir(spuerto, puerto);
	servidor = new Socket(puerto);
	servidor->conectar(sdireccion);
}

ConsumerConsulta::~ConsumerConsulta() {
	if (corriendo())
		detener_hilo();
	delete servidor;
}
