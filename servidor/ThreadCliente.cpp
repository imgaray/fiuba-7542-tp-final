#include "ThreadCliente.h"

bool ThreadCliente::mandarRespuesta(Respuesta& respuesta) {
	bool ret = false;
	if (cliente->conectado()) {
		ret = cliente->enviar(consulta);
	}
	return ret;
}

bool ThreadCliente::obtenerConsulta(Consulta& consulta) {
	bool ret = false;
	if (cliente->conectado()) {
		ret = cliente->recibir(consulta);
	}
	return ret;
}

ThreadCliente::ThreadCliente(Socket* scliente, ResolvedorConsulta* rsv):
						cliente(scliente), resolvedor(rsv) {
}

ThreadCliente::~ThreadCliente() {
	delete cliente;
}

void ThreadCliente::correr() {
	while (corriendo()) {
		Consulta consulta;
		bool fallo = true;;
		if (obtenerConsulta(consulta)) {
			if (mandarRespuesta(resolvedor->resolver(consulta)) {
				fallo = false;	
			}
		}
		if (fallo) {
			parar();
			cliente->desconectar();
		}
	}
}
