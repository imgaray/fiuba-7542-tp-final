#include "HiloResponderEntrada.h"

HiloResponderEntrada::HiloResponderEntrada(ConsultasAgentesServidor& cagt, ResolvedorEntradas& res): 
	centradas(cagt), resolvedor(res) {}

HiloResponderEntrada::~HiloResponderEntrada() {
	parar();
}

void HiloResponderEntrada::correr() {
	while (corriendo()) {
		try {
		ConsultaAgenteServidor par = centradas.pop2();
		Respuesta r = resolvedor.resolverEntrada(par.second);
		par.first->enviarRespuesta(r);
		} catch (BLQueueException& e) {
			parar();
		}
	}
}
