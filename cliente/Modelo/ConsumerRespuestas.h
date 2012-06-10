#ifndef __CONSUMERRESPUESTA_H
#define __CONSUMERRESPUESTA_H

#include "Definiciones.h"
#include "Consultante.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "BLQueue.h"
#include "Hilo.h"
#include "Mutex.h"

// TODO: hacer la clase consumer respuesta
class ConsumerRespuesta: public Hilo {
private:
	ColaRespuestas& respuestas;
	MapaConsultantes& consultantes;
public:
	void correr();
	ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons);
	~ConsumerRespuesta();
	
};

#endif
