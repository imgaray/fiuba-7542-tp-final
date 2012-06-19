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
 * Clase Estatica encargada de manejar fechas
 */
class M_Fechas {
public:

	M_Fechas() {}
	virtual ~M_Fechas() {}
	/*
	 * Se ingresa fecha como "12-12-2012" y se retorna en el formato
	 * correcto utilazado para el indice
	 */
	Fecha fecha(const std::string& fechaComun);
	bool esFechaConvecional(const std::string& fecha);

	Fecha rango(const Fecha& f1,const Fecha& f2);
	Fecha fecha(int dia, int mes, int anio);

    Fecha anio(const std::string& anio);
	Fecha semestre(int sem, const std::string& anio);
	Fecha cuatrimestre(int cuat, const std::string& anio);
	Fecha trimestre(int tri, const std::string& anio);
	Fecha bimestre(int bim, const std::string& anio);
	Fecha mes(int mes, const std::string& anio);
	Fecha semana(int semana, const std::string& anio);

	bool esRango(const Fecha& fecha);

	bool esSimple(const Fecha& fecha);

	void desarmar(const Fecha& rango, Fecha& f1, Fecha& f2);
	/*
	 * Solo para fecha Normal
	 */
	FechaNumerica convertir(const Fecha& fecha);
	Fecha convertir(const FechaNumerica& fecha);
	Fecha convertir(const FechaNumerica& fecha, int ancho);
private:
    Utilitario u;

	void desarmarMes(const Fecha& rango, Fecha& f1, Fecha& f2);
	void desarmarBimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	void desarmarTrimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	void desarmarCuatrimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	void desarmarSemes(const Fecha& rango, Fecha& f1, Fecha& f2);
	void desarmarAnio(const Fecha& rango, Fecha& f1, Fecha& f2);


	void desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul);
	void armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha);


	void calcularDia(const int& diaAnio,const FechaNumerica& anio, int& dia, int& mes);
};

#endif /* M_FECHAS_H_ */
