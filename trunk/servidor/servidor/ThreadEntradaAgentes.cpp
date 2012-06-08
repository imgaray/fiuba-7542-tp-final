#include "ThreadEntradaAgentes.h"

void ThreadEntradaAgentes::correr() {
	while (corriendo()) {
		Socket* sagente = entradaAgentes->escucharConexion();
		if (sagente) {	
			AgenteRemoto* ag = new AgenteRemoto(sagente, re);
			ca.agregarAgente(ag);
			ag->iniciar();
		} else {
			detener_entrada();
		}
	}
}

void ThreadEntradaAgentes::detener_entrada() {
	if (corriendo())
		parar();
	if (entradaAgentes)	
		entradaAgentes->desconectar();
//	sincronizar();
}

ThreadEntradaAgentes::ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent):
	ca(cag), re(rent) {
	entradaAgentes = new Socket(PORT_AGENTE);
	entradaAgentes->enlazar();
}

ThreadEntradaAgentes::~ThreadEntradaAgentes() {
	if (corriendo())	
		detener_entrada();
	if (entradaAgentes)
		delete entradaAgentes;
}
