#include "ThreadEntradaClientes.h"
#include <iostream>

bool ThreadEntradaClientes::activo() {
	return entradaClientes->conectado();
}

void ThreadEntradaClientes::correr() {
	while (corriendo()) {
		Socket* scliente = entradaClientes->escucharConexion();
		if (scliente) {
			ClienteRemoto* ag = new ClienteRemoto(scliente, rc, cconsultas);
			cc.agregarCliente(ag);
			ag->iniciar();
		} else {
			detener_entrada();
		}
	}
}

void ThreadEntradaClientes::detener_entrada() {
	parar();
	entradaClientes->desconectar();
}

ThreadEntradaClientes::ThreadEntradaClientes(ContenedorClientes& ccli,
				ResolvedorConsultas& rcons, Puerto pcli, ConsultasClientesServidor& ccons):
	cc(ccli), rc(rcons), pclientes(pcli), cconsultas(ccons) {
	entradaClientes = new Socket(pcli);
	entradaClientes->enlazar();
}

ThreadEntradaClientes::~ThreadEntradaClientes() {
	detener_entrada();
	delete entradaClientes;
}
