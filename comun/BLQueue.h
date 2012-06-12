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
		bopen = false;
		m.signal();
	}

	bool empty() {
		Lock l(m);
		return c.empty();
	}

	// pop bloqueante. Cuando se cierra la cola, lanza la excepcion pertinente
	T pop2() {
		while ((c.size() == 0) && open())
			m.wait();
		if (!open()) {
			// aviso a los demas hilos que este se cayo
			m.signal();
			throw "cola cerrada";
		}
		T t=c.front();
		c.pop();
		return t;
	}
};

#endif
