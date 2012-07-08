#ifndef __BLQUEUE_H__
#define __BLQUEUE_H__

#include <queue>
#include <iostream>
#include "Mutex.h"
#include <exception>

/** @class BLQueue
 * Implementacion thread safe de la queue de STL */

class BLQueueException: public std::exception {};

template <typename T>
class BLQueue {
	std::queue<T> c;
	Mutex m;
	bool bopen;
public:
	/** Verifica si la cola esta abierta o no. */
	bool open() {
		return bopen;
	}

	BLQueue() {bopen = true;}
	
	/** Agrega un elemento a la cola */
	void push(const T &i) {
		Lock l(m);
		c.push(i);
		m.signal();
	}
	
	/** saca el primer elemento de la pila. */
	void pop() {
		Lock l(m);
		c.pop();
	}
	
	/** muestra el primer elemento de la pila.
	 * @return devuelve el primer elemento de la pila. */
	T& front() {
		Lock l(m);
		return c.front();
	}
	
	/** Devuelve el tamaño de la pila
	 * @return cantidad de elementos apilados */
	size_t size() {
		Lock l(m);
		return c.size();
	}

	/** Cierra la pila. Es decir, avisa a todos los elementos bloqueados
	 * en pop2 que esta pila no se usará mas. @see pop2 */
	void close() {
		Lock l(m);
		bopen = false;
		m.signal();
	}

	/** Verifica si la pila está vacía */
	bool empty() {
		Lock l(m);
		return c.empty();
	}

	/** Saca el primer elemento de la pila, devolviéndolo. Este método es
	 * bloqueante, es decir, permanecerá bloqueado mientras no haya elementos
	 * en la pila y la misma esté abierta.
	 * @return El tope de la pila.
	 * @throw BLQueueException al cerrar la pila. */
	T pop2() {
		Lock l(m);
		while (c.size() == 0 && bopen) {
			m.wait();
		}
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
