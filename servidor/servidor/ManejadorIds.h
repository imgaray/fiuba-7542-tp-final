#ifndef __MANEJADORIDS_H
#define __MANEJADORIDS_H

#include <list>

class ManejadorIds {
private:
	typedef std::list<unsigned int> llibres;
	llibres libres;
	unsigned int ultimo;
public:
	ManejadorIds(): ultimo(0) {}
	
	unsigned int obtenerId() {
		unsigned int ret;
		if (llibres.empty())
			ret = ++ultimo;
		else
			ret = llibres.pop_back();
		return ret;
	}
	
	void addLibre(unsigned int id) {
		llibres.push_back(id);
	}
	
	~ManejadorIds() {}
};

#endif
