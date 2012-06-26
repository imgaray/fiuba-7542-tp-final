/* 
 * File:   Hilo.h
 * Author: migue
 *
 * Created on 25 de abril de 2012, 00:48
 */

#ifndef HILO_H
#define	HILO_H

#include <pthread.h>
#include <iostream>

/*
 * @DOC:
						Clase Hilo

	Esta clase abstracta, .

Atributos:

    pthread_t hilo:
*
    bool _correr: booleano que indica si esta en estado de "corriendo"
*
    bool _sincronizado: booleano que indica si el hilo a sido sincronizado.

 * @END
 * */


class Hilo {
public:
    /*
     * Constructor sin argumentos de hilo
     */
    Hilo();
    
    /*
     * Destructor de Hilo
     */
    virtual ~Hilo();
    
    /*
     * Metodo que inicia la ejecucion del hilo
     */
    virtual void iniciar();
    
    /*
     * Metodo que pone al hilo en estado de detener la ejecucion
     */
    virtual void parar();    
    
    /*
     * Metodo virtual puro, que corre cuando se ejecuta el hilo
     */
    virtual void correr() = 0;
    
    /*
     * Metodo que espera a que finalice el hilo
     */
    virtual void sincronizar();
    
    /*
     * Metodo retornado true si el hilo esta corriendo o si esta 
     * listo para correr.
     */
    bool corriendo();

    /*
     * Retorna un bool indicando si el Hilo a sido sincronizado
     */
    bool sincronizado();

private:
    /*
     * Constructor copia privado
     */
    Hilo(const Hilo& orig) {}
    void operator=(const Hilo &orig) {}
    
    /*
     * Metodo estatico utilizado para llamar a la ejecucion del hilo.
     */
    static void* llamarHilo(void* hilo);
    
    pthread_t hilo;
    bool _correr;
    bool _sincronizado;
};

#endif	/* HILO_H */

