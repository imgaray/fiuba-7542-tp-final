#include "Servidor.h"
#include <string>
#include 
#define ARGS 2
#define ERR_ARGS 1
#define ERR_PERSISTENCIA 2
#define ERR_APERTURA 3
#define EXITO 0
#define CONDICION_SALIDA "Q"

/* Programa principal del servidor
 * Formato de uso:
 * ./server [puerto]
 * */
int main(int argc, char** argv) {
	if (argc != ARGS)
		return ERR_ARGS;
	try { 
		Servidor servidor();
	} catch (ErrorAperturaServidor err) {
		std::cerr << "Error en la apertura del servidor" << std::endl;
		return ERR_APERTURA;
	}
	servidor.comenzar();
	std::string aux("");
	std::string cmp(CONDICION_SALIDA);
	while (aux != cmp)
		getline(std::cin, aux);
	servidor.detener();
	try {
		servidor.persistir();
	} catch (ErrorPersistencia err) {
		std::cerr << "Error al persistir el servidor" << std::endl;
		return ERR_PERSISTENCIA;
	}
	return EXITO;
}
