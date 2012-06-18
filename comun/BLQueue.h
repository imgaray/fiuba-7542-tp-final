#ifndef __BLQUEUE_H__
#define __BLQUEUE_H__

#include <queue>
#include <iostream>
#include "Mutex.h"
#include <exception>

class BLQueueException: public std::exception {};

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
		Lock l(m);
		c.push(i);
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
		return c.size();
	}

	void close() {
		Lock l(m);
		bopen = false;
		m.signal();
	}

	bool empty() {
		Lock l(m);
		return c.empty();
	}

	// pop bloqueante. Cuando se cierra la cola, lanza la excepcion pertinente
	T pop2() {
		Lock l(m);
		std::cout << "entre al pop2" << std::endl;
		while (c.size() == 0 && bopen) {
			std::cout << "estoy esperando en pop2" << std::endl;
			m.wait();
		}
		
		std::cout << "bloquee el hilo en pop2" << std::endl;
		if (!open()) {
			// aviso a los demas hilos que este se cayo
			m.signal();
			throw BLQueueException();
		}
		T t=c.front();
		c.pop();
		m.signal();
		return t;
	}
};

#endif
