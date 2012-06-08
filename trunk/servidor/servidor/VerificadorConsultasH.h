#ifndef __VALIDADORCONSULTAS_H
#define __VALIDADORCONSULTAS_H

class VerificadorConsultasH {
public:
	bool verificarConsulta(const Consulta& consulta) {
		return true;
	}
	VerificadorConsultasH() {}
	~VerificadorConsultasH() {}
private:
	bool hayDimesionesEnRes(const Consulta& cons);
	bool hayHechosEnRes(const Consulta& cons);

	bool cClienteValida(const Consulta& cons);
	bool cAgenteValida(const Consulta& cons);
};

#endif
