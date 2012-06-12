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
	this->parar();
}

ThreadEntradaAgentes::ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent, Puerto pag):
	ca(cag), re(rent), pagentes(pag) {
	entradaAgentes = new Socket(pagentes);
	entradaAgentes->enlazar();
}

ThreadEntradaAgentes::~ThreadEntradaAgentes() {
	if (corriendo())	
		detener_entrada();
	if (entradaAgentes)
		delete entradaAgentes;
}
