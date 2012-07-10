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

/**
 * @class Agente
 * Esta clase cumple el rol completo de un agente. Encargandose de enviar registros
 * uno por uno a un Servidor o enviar Registros a travez de Archivos.
 */

class Agente {
public:

	/**
	 * @brief Constructor que recive la ruta del archivo de configuracion
	 * @param rutaConfig string que contiene la ruta del archivo de config.
	 */
	Agente(const std::string& rutaConfig = "");

	/**
	 * @brief Se intenta conectar con el servidor y luego se cargan registros
	 * uno por uno.
	 */
	void cargarDesdeConsola();

	/**
	 * @brief Se intenta conectar con el servidor y luego se cargar los registros
	 * directamente desde un archivo.
	 * @param rutaDatos string que contiene la ruta del archivo con lo registros
	 * a cargar.
	 */
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
