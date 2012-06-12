/*
 * Agente.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef AGENTE_H_
#define AGENTE_H_
#include <string>
#include <fstream>

class Socket;
class Consulta;

class Agente {
public:
	Agente(const std::string& rutaConfig = "");
	void cargarDesdeConsola();
	void cargarDesdeArchivo(const std::string& rutaDatos);
	virtual ~Agente();
private:

	void leerLinea(std::fstream& archivo, std::string& linea);
	void cargarConfiguracion(const std::string& rutaConfig);

	void enviarConsulta(const Consulta& consulta);
	void recibirRespuesta();

	Socket *_sck;
	std::string _huesped;
};

#endif /* AGENTE_H_ */
