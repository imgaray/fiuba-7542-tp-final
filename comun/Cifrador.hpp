#ifndef CIFRADOR_H
#define CIFRADOR_H

#include <string>

#define DEFAULT 115

class Cifrador {
public:
	void cifrar(std::string& obj, int clave = DEFAULT) {
		for (int i = 0; i < (int)obj.size(); ++i) {
			obj[i] += clave;
		}
	}
	
	void descifrar(std::string& obj, int clave = DEFAULT) {
		cifrar(obj, -clave);
	}
	
	Cifrador(){}
	~Cifrador(){}
};

#endif
