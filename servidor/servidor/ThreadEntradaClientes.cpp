#include "ThreadEntradaClientes.h"

void ThreadEntradaClientes::correr() {
	while (corriendo()) {
		Socket* scliente = entradaClientes->escucharConexion();
		if (scliente) {
			ClienteRemoto* ag = new ClienteRemoto(scliente, rc);
			cc.agregarCliente(ag);
			ag->iniciar();
		} else {
			detener_entrada();
		}
	}
}

void ThreadEntradaClientes::detener_entrada() {
	if (corriendo())
		parar();
	if (entradaClientes)
		entradaClientes->desconectar();
	sincronizar();
}

ThreadEntradaClientes::ThreadEntradaClientes(ContenedorClientes& ccli, ResolvedorConsultas& rcons):
	cc(ccli), rc(rcons) {
	entradaClientes = new Socket(PORT_CLIENTE);
	entradaClientes->enlazar();
}

ThreadEntradaClientes::~ThreadEntradaClientes() {
	if (corriendo())	
		detener_entrada();
	if (entradaClientes)
		delete entradaClientes;
}
