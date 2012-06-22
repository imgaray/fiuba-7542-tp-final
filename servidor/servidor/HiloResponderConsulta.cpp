#include <iostream>
#include "HiloResponderConsulta.h"

HiloResponderConsulta::HiloResponderConsulta(ConsultasClientesServidor& ccons, ResolvedorConsultas& res): 
	cconsultas(ccons), resolvedor(res) {}

HiloResponderConsulta::~HiloResponderConsulta() {
	parar();
}

void HiloResponderConsulta::correr() {
	while (corriendo()) {
		try {
		ConsultaClienteServidor par = cconsultas.pop2();
		Respuesta r = resolvedor.resolver(par.second);
        std::cout << "void HiloResponderConsulta::correr() \n serialización: " << r.serializar() << std::endl;
		par.first->enviarRespuesta(r);
		} catch (BLQueueException& e) {
			parar();
		}
	}
}
