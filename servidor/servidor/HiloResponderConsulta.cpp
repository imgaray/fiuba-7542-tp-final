#include <iostream>
#include "HiloResponderConsulta.h"
#include <iostream>

HiloResponderConsulta::HiloResponderConsulta(ConsultasClientesServidor& ccons, ResolvedorConsultas& res): 
	cconsultas(ccons), resolvedor(res) {}

HiloResponderConsulta::~HiloResponderConsulta() {
	parar();
}

void HiloResponderConsulta::correr() {
	while (corriendo()) {
		try {
		ConsultaClienteServidor par = cconsultas.pop2();
		std::cout << "HRC: saque una consulta de la cola" << std::endl;
		std::cout << "serializacion = " << par.second.serializar() << std::endl;
		Respuesta r = resolvedor.resolver(par.second);
		std::cout << "HRC: la respuesta fue " << r.serializar() << std::endl;
		par.first->enviarRespuesta(r);
		} catch (BLQueueException& e) {
			parar();
		}
	}
}
