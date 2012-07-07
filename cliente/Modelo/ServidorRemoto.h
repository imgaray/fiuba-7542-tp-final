#ifndef __SERVIDORREMOTO_H
#define __SERVIDORREMOTO_H

#include "Definiciones.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "ConsumerConsultas.h"
#include "ConsumerRespuestas.h"
#include "BLQueue.h"
#include "BLMap.h"
#include <utility>
#include <list>
#include "Socket.h"
#include <string>

class Consultante;

/** @class ServidorRemoto

	Esta clase es el proxy del servidor. A través de la misma es que el
cliente se puede comunicar con el servidor. Tiene la responsabilidad de
enviar consultas y recibir las respuestas. Esto lo logra a traves de sus
workers. Posee dos colas, una de consultas y una de respuestas. Al llegar
un pedido de consulta, lo encola en la cola correspondiente. Al llegar un
pedido por respuestas, intenta sacar de la cola de respuestas.

	Cabe destacar que las respuestas no van a respetar el orden de las consultas
enviadas. Es decir, si se enviaron las consultas 1, 2 y 3, puede darse el
caso en que se reciban las respuestas en el orden 2, 3, 1 o cualquier
otra combinación. Esto dependerá de los tiempos de respuesta del servidor
y de la amplitud de cada consulta enviada.
	
	El servidor remoto también es capaz de aceptar pedidos de cancelación
de alguna consulta dada. Es decir, si se canceló una consulta pedida con
anterioridad, se rechazará la misma ya sea cuando llegue o cuando se intente
enviar. */

class ServidorRemoto {
private:
	// atributos contenedores
	ColaConsultas consultas; /* Esta cola contendra todas las consultas pendientes
	de envio. De esta cola consumira el hilo que se encarga del envio de
	consultas. */
	
	ColaRespuestas respuestas; /* Esta cola contendra todas las respuestas
	producidas por el hilo encargado de la recepcion de las mismas. El
	servidor, al recibir un pedido de obtenerRespuesta, intentara desencolar
	de la misma. */
	
	MapaConsultantes consultantes; /* (deprecated) Es un mapa de consultantes.
	Todo Consultante que haya hecho una consulta queda registrado. En un
	primer momento sirvio para distribucion de respuestas. */
	
	BitmapCancelados cancelados; /* Es el bitmap que contiene las consultas
	canceladas. En escencia, es un map<unsigned, bool>. El primer elemento
	es el ID del Consultante que haya hecho la consulta. El segundo valor
	corresponde a un valor de true o false, que dice si la consulta debe cancelarse
	o no. */
	
	ConsumerRespuesta crespuesta; /*  Es el encargado de "producir" las
	respuestas que popularan la cola de respuestas. */
	
	ConsumerConsulta cconsulta; /* Es el consumer encargado de enviar las
	consultas pendientes de la cola de consultas. */

	Socket* sock; /* Es el socket utilizado para conectar con el servidor.
	Este puntero es compartido tanto por crespuesta como por cconsulta.
	El encargado de cerrar este socket es unicamente el servidorRemoto. */ 

	std::string sdireccion; /* Atributo que se utiliza unicamente para
	conectar el socket al servidor. Contiene la direccion del mismo. */

public:
	
	/** Al construirse, verifica la configuración de puerto de servRemoto.conf.
	No inicia ningun consumer. */
	ServidorRemoto();
	
	/** Detiene todo lo que tiene que detener, vacía todo lo que tiene que vaciar.
	 *	Desconecta la conexion */
	~ServidorRemoto();
	
	/**	Método que sirve para iniciar tanto la conexion como los hilos.
	 * @throw char* si no puede conectar, lanza un mensaje de error. */
	void conectar() throw(char* );
	
	/** Este método es el encargado de recibir la consulta por parte del
		cliente. En el mismo, lo que se hace es encolar la consulta en la
		cola de consultas pendientes. Luego, el hilo correspondiente se
		encargara del envío de la misma. */
	void enviarConsulta(Consultante* consultante, Consulta consulta);
	
	/** Devuelve la cantidad de respuestas que posee en la cola de respuestas */
	unsigned cantidadRespuestas();
	
	/**
		Es el encargado de sacar una respuesta de la cola de
		respuestas recibidas. Lo utiliza el hilo de gtk para obtener las
		respuestas.
	*/
	Respuesta obtenerRespuesta();
	
	/** Recibe un IDcons y lo marca en el BitMap como consulta
		cancelada. De esta forma, la próxima consulta que se reciba o intente
		mandar con ese ID, será descartada.
	*/
	void cancelarConsulta(unsigned IDcons);
	
	/** Sirve para verificar si el servidor esta conectado o
		no.
	*/
	bool conectado();
};

#endif
