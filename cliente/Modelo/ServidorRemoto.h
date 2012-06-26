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

/* @DOC

	Clase ServidorRemoto

	Esta clase es el proxy del servidor. A traves de la misma es que el
cliente se puede comunicar con el servidor. Tiene la responsabilidad de
enviar consultas y recibir las respuestas. Esto lo logra a traves de sus
workers. Posee dos colas, una de consultas y una de respuestas. Al llegar
un pedido de consulta, lo encola en la cola correspondiente. Al llegar un
pedido por respuestas, intenta sacar de la cola de respuestas.

	Cabe destacar que las respuestas no van a respetar el orden de las consultas
enviadas. Es decir, si se enviaron las consultas 1, 2 y 3, puede darse el
caso en que se reciban las respuestas en el orden 2, 3, 1 o cualquier
otra combinacion. Esto dependera de los tiempos de respuesta del servidor
y de la magnitud de cada consulta enviada.
	
	El servidor remoto tambien es capaz de aceptar pedidos de cancelacion
de alguna consulta dada. Es decir, si se cancelo una consulta pedida con
anterioridad, se rechazara la misma ya sea cuando llegue o cuando se intente
enviar.

	Atributos:
	ColaConsultas consultas: Esta cola contendra todas las consultas pendientes
	de envio. De esta cola consumira el hilo que se encarga del envio de
	consultas.
	* 
	ColaRespuestas respuestas: Esta cola contendra todas las respuestas
	producidas por el hilo encargado de la recepcion de las mismas. El
	servidor, al recibir un pedido de obtenerRespuesta, intentara desencolar
	de la misma.
	* 
	MapaConsultantes consultantes(deprecated): Es un mapa de consultantes.
	Todo Consultante que haya hecho una consulta queda registrado. En un
	primer momento sirvio para distribucion de respuestas.
	* 
	BitmapCancelados cancelados: Es el bitmap que contiene las consultas
	canceladas. En escencia, es un map<unsigned, bool>. El primer elemento
	es el ID del Consultante que haya hecho la consulta. El segundo valor
	corresponde a un valor de true o false, que dice si la consulta debe cancelarse
	o no.
	* 
	ConsumerRespuesta crespuesta: Es el encargado de "producir" las
	respuestas que popularan la cola de respuestas.
	* 
	ConsumerConsulta cconsulta: Es el consumer encargado de enviar las
	consultas pendientes de la cola de consultas.
	* 
	Socket* sock: Es el socket utilizado para conectar con el servidor.
	Este puntero es compartido tanto por crespuesta como por cconsulta.
	El encargado de cerrar este socket es unicamente el servidorRemoto.
	
	std::string sdireccion: Atributo que se utiliza unicamente para
	conectar el socket al servidor. Contiene la direccion del mismo.
	
@END */

class ServidorRemoto {
private:
	// atributos contenedores
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	BitmapCancelados cancelados;
	ConsumerRespuesta crespuesta;
	ConsumerConsulta cconsulta;
	Socket* sock;
	std::string sdireccion;

public:

/* @DOC
	Metodos publicos

@END*/

	ServidorRemoto();
	~ServidorRemoto();
	/*@DOC
	void conectar() throw(char* ):
		Metodo que sirve para iniciar tanto la conexion como los hilos.
	@END*/
	void conectar() throw(char* );
	
	/*@DOC
	void enviarConsulta(Consultante* consultante, Consulta consulta):
		Este metodo es el encargado de recibir la consulta por parte del
		cliente. En el mismo, lo que se hace es encolar la consulta en la
		cola de consultas pendientes. Luego, el hilo correspondiente se
		encargara del envio de la misma.
		* 
@END*/
	void enviarConsulta(Consultante* consultante, Consulta consulta);
	unsigned cantidadRespuestas();
	
	/*@DOC
	void obtenerRespuesta():
		Este metodo es el encargado de sacar una respuesta de la cola de
		respuestas recibidas. Lo utiliza el hilo de gtk para obtener las
		respuestas.
		* 
@END*/
	Respuesta obtenerRespuesta();
	
	/*@DOC
	void cancelarConsulta(unsigned IDcons):
		Este metodo recibe un IDcons y lo marca en el BitMap como consulta
		cancelada. De esta forma, la proxima consulta que se reciba o intente
		mandar con ese ID, sera descartada.
				
		@END*/
	void cancelarConsulta(unsigned IDcons);
	
	/*@DOC
	bool conectado():
		Metodo que sirve para verificar si el servidor esta conectado o
		no.
	@END*/
	bool conectado();
};

#endif
