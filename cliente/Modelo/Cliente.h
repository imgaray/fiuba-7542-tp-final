/*
 * Cliente.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "Personalizador.h"

class VentanaCliente;

class Cliente {
public:
    Cliente(int argc, char* argv[]);
    virtual ~Cliente();

    void run();

private:
    VentanaCliente* pVentana;
    void initGtk(int argc, char* argv[]);
};

#endif /* CLIENTE_H_ */
