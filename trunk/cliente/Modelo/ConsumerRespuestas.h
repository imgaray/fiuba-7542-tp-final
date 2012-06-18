#ifndef __CONSUMERRESPUESTA_H
#define __CONSUMERRESPUESTA_H

#include "Definiciones.h"
#include "BLQueue.h"
#include "Hilo.h"
#include "Mutex.h"
#include "Socket.h"

// TODO: hacer la clase consumer respuesta
class ConsumerRespuesta: public Hilo {
private:
	ColaRespuestas& respuestas;
	MapaConsultantes& consultantes;
	Socket* servidor;
	BitmapCancelados& cancelados;
public:
	void correr();
	ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons,
							Socket* conexion, BitmapCancelados& canc);
	~ConsumerRespuesta();

};

#endif
