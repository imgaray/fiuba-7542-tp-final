#include "ArchivoConfiguracion.h"
#include <iostream>
#include "Pruebas.h"
using namespace std;

int __main(int argc, char** argv) {
	testGeneradorRegistros();
	char ruta[] = "configuracionprueba";
	ArchivoConfiguracion archivo(ruta);
	ArchivoConfiguracion::iterator iter;
	for (iter = archivo.begin(); iter != archivo.end(); ++iter) {
		cout << "atributo: " << iter->first << " valor = " << iter->second << endl;
	}
	return 0;
}
