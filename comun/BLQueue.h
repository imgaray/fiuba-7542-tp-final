#ifndef __BLQUEUE_H__
#define __BLQUEUE_H__

#include <queue>
#include <iostream>
#include "Mutex.h"

template <typename T>
class BLQueue {
	std::queue<T> c;
	Mutex m;
public:
	// constructor
	BLQueue() {}
	// agregar
	void push(const T &i) {
		Lock l(m);
		c.push(i);
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
	// pop bloqueante
	/*T pop2() {
		T t=c.front();
		c.pop();
		return t;
	}*/
};

#endif
