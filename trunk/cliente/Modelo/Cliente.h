/*
 * Cliente.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

class VentanaCliente;

/** @class Cliente
 * Clase que comprende la abstracción de la aplicación en sí, manejando la
 * ventana principal, la carga desde el archivo GLADE y de configuración
 * de pestañas, y el main loop de GTK+.
 */
class Cliente {
    public:
        /**
         * Constructor.
         * @param argc cantidad de argumentos del programa
         * @param argv vector de argumentos del programa
         */
        Cliente(int argc, char* argv[]);
        /**
         * Destructor.
         */
        ~Cliente();

        void run();

    private:
        VentanaCliente* pVentana;
        void initGtk(int argc, char* argv[]);
};

#endif /* CLIENTE_H_ */
