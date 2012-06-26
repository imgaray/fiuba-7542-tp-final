/*
 * M_Fechas.h
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#ifndef M_FECHAS_H_
#define M_FECHAS_H_
#include "Definiciones.h"
#include <sstream>
#include "Utilitario.h"

/*
 * @DOC:
						Clase M_Fechas

	Esta clase es la encargada de manejar fechas, para un uso mas comodo guardando
	dia, semana, mes, bimestre , trimestre, cuatrimeste, semestre para algun anio.
	Se encarga de manejar fechas simple o fechas compuestas, siendo las fechas simples
	fechas con formato comun numerico y las fechas compuestas serian semana, mes,
	bimestes, etc.

 * @END
 * */

class M_Fechas {
public:

	M_Fechas() {}
	virtual ~M_Fechas() {}
	/*
	 * Se ingresa fecha como "12-12-2012" y se retorna en el formato
	 * correcto utilazado para el indice
	 */
	Fecha fecha(const std::string& fechaComun)  const;
	bool esFechaConvecional(const std::string& fecha)  const;

	Fecha rango(const Fecha& f1,const Fecha& f2) const;
	Fecha fecha(int dia, int mes, int anio) const;

    Fecha anio(const std::string& anio) const;
	Fecha semestre(int sem, const std::string& anio) const;
	Fecha cuatrimestre(int cuat, const std::string& anio) const;
	Fecha trimestre(int tri, const std::string& anio) const;
	Fecha bimestre(int bim, const std::string& anio) const;
	Fecha mes(int mes, const std::string& anio) const;
	Fecha semana(int semana, const std::string& anio) const;

	bool esRango(const Fecha& fecha) const;

	bool esSimple(const Fecha& fecha) const;

	void desarmar(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	/*
	 * Solo para fecha Normal
	 */
	FechaNumerica convertir(const Fecha& fecha) const;
	Fecha convertir(const FechaNumerica& fecha) const;
	Fecha convertir(const FechaNumerica& fecha, int ancho) const;
private:
    //Utilitario u;

	void desarmarMes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarBimes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarTrimes(const Fecha& rango, Fecha& f1, Fecha& f2) const;
	void desarmarCuatrimes(const Fecha& rango, Fecha& f1, Fecha& f2)  const;
	void desarmarSemes(const Fecha& rango, Fecha& f1, Fecha& f2)  const;
	void desarmarAnio(const Fecha& rango, Fecha& f1, Fecha& f2)  const;


	void desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul)  const;
	void armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha)  const;


	void calcularDia(const int& diaAnio,const FechaNumerica& anio, int& dia, int& mes) const;
};

#endif /* M_FECHAS_H_ */
