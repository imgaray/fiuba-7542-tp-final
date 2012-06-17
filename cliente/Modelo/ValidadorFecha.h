#ifndef VALIDADOR_FECHA_H
#define VALIDADOR_FECHA_H

#include <map>
#include "Validador.h"

class ValidadorFecha : public Validador {
    public:
        ValidadorFecha(char tipo, const Glib::ustring& nombre);

        Campos getCampos(unsigned i);

        Glib::ustring validar(Campos& acotados, Campos& noAcotados);

        Glib::ustring validar(Glib::ustring& acotado,
                              Glib::ustring& noAcotado);

        Campos getEstadoNoAcotados(Campos& acotados);
        Glib::ustring getEstadoNoAcotados(Glib::ustring& acotado);
    private:
        enum valMapa {
            ANIO,
            MES,
            BIMESTRE,
            TRIMESTRE,
            CUATRIMESTRE,
            SEMESTRE,
            SEMANA_DEL_ANIO,
            DIA
        };
        static Glib::ustring valoresAcotados[];
        static valMapa valoresMapa[];
        std::map< Glib::ustring, valMapa > valores;

        Glib::ustring validarAnio(Glib::ustring& anio);
        Glib::ustring validarPorAnio(Campos& noAcotados);
        Glib::ustring validarPorMes(Campos& noAcotados);
        Glib::ustring validarPorBimestre(Campos& noAcotados);
        Glib::ustring validarPorTrimestre(Campos& noAcotados);
        Glib::ustring validarPorCuatrimestre(Campos& noAcotados);
        Glib::ustring validarPorSemestre(Campos& noAcotados);
        Glib::ustring validarPorSemanaDelAnio(Campos& noAcotados);
        Glib::ustring validarPorDia(Campos& noAcotados);

        /// como las validaciones por mes, bimestre, trimestre, cuatrimestre
        /// semestre y semana del año sólo cambian en el rango del segundo
        /// campo, las meto todas en este método
        Glib::ustring validarGenericaPorRango(Campos& noAcotados,
                                              int min,
                                              int max);
        Campos getMetadata(bool showDia, bool showMes, bool showAnio);
};

#endif  // VALIDADOR_FECHA_H
