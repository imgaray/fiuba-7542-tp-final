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

/*
 * Clase Estatica encargada de manejar fechas
 */
class M_Fechas {
public:

	/*
	 * Se ingresa fecha como "12-12-2012" y se retorna en el formato
	 * correcto utilazado para el indice
	 */
	static Fecha fecha(const std::string& fechaComun);
	static bool esFechaConvecional(const std::string& fecha);

	static Fecha rango(const Fecha& f1,const Fecha& f2);
	static Fecha fecha(int dia, int mes, int anio);

	static Fecha semestre(int sem, const std::string& anio);
	static Fecha cuatrimestre(int cuat, const std::string& anio);
	static Fecha trimestre(int tri, const std::string& anio);
	static Fecha bimestre(int bim, const std::string& anio);
	static Fecha mes(int mes, const std::string& anio);

	static bool esRango(const Fecha& fecha);

	static bool esSimple(const Fecha& fecha);

	static void desarmar(const Fecha& rango, Fecha& f1, Fecha& f2);
	/*
	 * Solo para fecha Normal
	 */
	static FechaNumerica convertir(const Fecha& fecha);
	static Fecha convertir(const FechaNumerica& fecha);
	static Fecha convertir(const FechaNumerica& fecha, int ancho);
private:

	static void desarmarMes(const Fecha& rango, Fecha& f1, Fecha& f2);
	static void desarmarBimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	static void desarmarTrimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	static void desarmarCuatrimes(const Fecha& rango, Fecha& f1, Fecha& f2);
	static void desarmarSemes(const Fecha& rango, Fecha& f1, Fecha& f2);

	static void desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul);
	static void armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha);

	M_Fechas() {}
	virtual ~M_Fechas() {}
};

#endif /* M_FECHAS_H_ */
