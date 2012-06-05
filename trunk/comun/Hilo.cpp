/* 
 * File:   Hilo.cpp
 * Author: migue
 * 
 * Created on 25 de abril de 2012, 00:48
 */

#include "Hilo.h"

Hilo::Hilo() {
    this->_correr = false;
}

Hilo::~Hilo() {
}

void Hilo::iniciar() {
    this->_correr = true;
    // pthread_create(&this->hilo, 0, Hilo::llamarHilo, this);
}

void* Hilo::llamarHilo(void* hilo) {
    ((Hilo*)hilo)->correr();
    return NULL;
}

void Hilo::parar() {
    this->_correr = false;
}

void Hilo::sincronizar() {
   // pthread_join(this->hilo, NULL);
}

bool Hilo::corriendo() {
    return this->_correr;
}
