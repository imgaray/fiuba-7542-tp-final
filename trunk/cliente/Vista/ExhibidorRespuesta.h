/*
 * ExhibidorRespuesta.h
 *
 *  Created on: 20/06/2012
 *      Author: migue
 */

#ifndef EXHIBIDORRESPUESTA_H_
#define EXHIBIDORRESPUESTA_H_

#include "Consultante.h"

class FiltradoresPanel;

class ExhibidorRespuesta : public Consultante {
public:
	ExhibidorRespuesta(FiltradoresPanel& filtrador);

    virtual void hacerConsulta(ServidorRemoto& server) = 0;

    void actualizarTamanioMinimo(double x, double y) = 0;

    virtual FiltradoresPanel& getFiltrador() const = 0;

	virtual ~ExhibidorRespuesta();
protected:
};

#endif /* EXHIBIDORRESPUESTA_H_ */
