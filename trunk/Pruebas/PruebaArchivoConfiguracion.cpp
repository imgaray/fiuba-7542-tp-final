#include "../comun/ArchivoConfiguracion.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	char ruta[] = "configuracionprueba";
	ArchivoConfiguracion archivo(ruta);
	ArchivoConfiguracion::iterator iter;
	for (iter = archivo.begin(); iter != archivo.end(); ++iter) {
		cout << "atributo: " << iter->first << " valor = " << iter->second << endl;
	}
	return 0;
}
