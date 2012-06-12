#include "ServidorRemoto.h"
#include "Consultante.h"

ServidorRemoto::ServidorRemoto():
			crespuesta(respuestas, consultantes) {
	for (int i = 0; i < MAX_OPEN_PORTS; ++i) {
		ConsumerConsulta* cc = new ConsumerConsulta(consultas, respuestas);
		cconsultas.push_back(cc);
		cc->iniciar();
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
	/** @todo remover este if, no tiene por qué estar */
	if (consultas.size())
        consultas.push(par);
}

void ServidorRemoto::cancelarConsulta(unsigned IDcons) {
    std::cout << "@todo void ServidorRemoto::cancelarConsulta(unsigned )" << std::endl;
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
	crespuesta.sincronizar();
}
