#ifndef __BLQUEUE_H__
#define __BLQUEUE_H__

#include <queue>
#include <iostream>
#include "Mutex.h"

template <typename T>
class BLQueue {
	std::queue<T> c;
	Mutex m;
	bool bopen;
public:
	bool open() {
		return bopen;
	}

	// constructor
	BLQueue() {bopen = true;}
	// agregar
	void push(const T &i) {
		std::cout << "entre al push" << std::endl;
		Lock l(m);
		std::cout << "estoy bloqueado" << std::endl;
		c.push(i);
		std::cout << "estoy tirando signal para ver si algun otro tiene" << std::endl;
		m.signal();
	}
	// sacar de tope de pila
	void pop() {
		Lock l(m);
		c.pop();
	}
	// mirar tope
	T& front() {
		Lock l(m);
		return c.front();
	}
	// tamanio pila
	size_t size() {
		Lock l(m);
		std::cout << "estoy en size de cola" << std::endl;
		return c.size();
	}

	void close() {
		bopen = false;
		std::cout << "estoy en close " << std::endl;
		m.signal();
	}

	bool empty() {
		Lock l(m);
		std::cout << "estoy en el empty" << std::endl;
		return c.empty();
	}

	// pop bloqueante. Cuando se cierra la cola, lanza la excepcion pertinente
	T pop2() {
		Lock l(m);
		std::cout << "entre al pop2" << std::endl;
		while (c.size() == 0) {
			std::cout << "estoy esperando en pop2" << std::endl;
			m.wait();
		}
		
		std::cout << "bloquee el hilo en pop2" << std::endl;
		if (!open()) {
			// aviso a los demas hilos que este se cayo
			m.signal();
			throw "cola cerrada";
		}
		T t=c.front();
		c.pop();
		m.signal();
		return t;
	}
};

#endif
