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

/**
 * @class Clase Abstracta que utilizada para manipular un Hilo.
 */

class Hilo {
public:
    /**
     * @brief Constructor sin argumentos de hilo
     */
    Hilo();
    
    /**
     * @brief Destructor de Hilo
     */
    virtual ~Hilo();
    
    /**
     * @brief Metodo que inicia la ejecucion del hilo
     */
    virtual void iniciar();
    
    /**
     * @brief Metodo que pone al hilo en estado de detener la ejecucion
     */
    virtual void parar();    
    
    /**
     * @brief Metodo virtual puro, que corre cuando se ejecuta el hilo
     */
    virtual void correr() = 0;
    
    /**
     * @brief Metodo que espera a que finalice el hilo
     */
    virtual void sincronizar();
    
    /**
     * @brief Metodo retornado true si el hilo esta corriendo o si esta
     * listo para correr.
     */
    bool corriendo();

    /**
     * @brief Retorna un bool indicando si el Hilo a sido sincronizado
     */
    bool sincronizado();

private:
    /**
     * @brief Constructor copia privado
     */
    Hilo(const Hilo& orig) {}
    void operator=(const Hilo &orig) {}
    
    /**
     * @brief Metodo estatico utilizado para llamar a la ejecucion del hilo.
     */
    static void* llamarHilo(void* hilo);
    
    pthread_t hilo;
    bool _correr;
    bool _sincronizado;
};

#endif	/* HILO_H */

