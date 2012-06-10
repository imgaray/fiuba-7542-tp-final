#include "ServidorRemoto.h"

ServidorRemoto::ServidorRemoto():
			crespuesta(respuestas, consultantes) {
	for (int i = 0; i < MAX_OPEN_PORTS; ++i) {
		cconsultas.push_back(new ConsumerConsulta(consultas, respuestas));
	}
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

ServidorRemoto::~ServidorRemoto()  {
	consultas.close();
	respuestas.close();
	std::list<ConsumerConsulta*>::iterator iter;
	for (iter = cconsultas.begin(); iter != cconsultas.end(); ++iter) {
		(*iter)->detener_hilo();
		(*iter)->sincronizar();
		delete *iter;
	}
}
