/*
 * BLmap.h
 *
 *  Created on: 17/05/2012
 *      Author: nacho
 */

#ifndef BLMAP_H_
#define BLMAP_H_

#include <map>
#include "Mutex.h"

// Clase que encapsula el comportamiento de map, solo que thread safe

template <class T, class Y>
class BLMap {
private:
	typedef std::map<T, Y> Mapa;
	Mapa mapa;
	Mutex m;
public:
	typedef typename Mapa::iterator iterator;
	iterator& find(const T& key) {
		Lock lock(m);
		return mapa.find(key);
	}

	Y& operator[](const T& key) {
		Lock lock(m);
		return mapa[key];
	}

	unsigned size() {
		Lock lock(m);
		return mapa.size();
	}

	iterator begin() {
		Lock lock(m);
		return mapa.begin();
	}

	iterator end() {
		Lock lock(m);
		return mapa.end();
	}

	bool empty(){
		Lock lock(m);
		return mapa.empty();
	}

	bool has(const T& key) {
		Lock lock(m);
		return mapa.find(key) != mapa.end();
	}

	BLMap() {

	}
	~BLMap() {

	}
};

#endif /* BLMAP_H_ */
