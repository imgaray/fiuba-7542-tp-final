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
		Respuesta r = resolvedor.resolver(par.second);
		par.first->enviarRespuesta(r);
		} catch (BLQueueException& e) {
			parar();
		}
	}
}
