#include "ValidadorFecha.h"

#define CANT_COMBO 8
#define FEBRERO 2
#define AGOSTO  FEBRERO+6

Glib::ustring ValidadorFecha::valoresAcotados[CANT_COMBO] = {
    "Día", "Mes", "Bimestre", "Trimestre", "Cuatrimestre", "Semestre",
    "Semana del año", "Año"
};

ValidadorFecha::valMapa ValidadorFecha::valoresMapa[CANT_COMBO] = {
    DIA, MES, BIMESTRE, TRIMESTRE, CUATRIMESTRE, SEMESTRE,
    SEMANA_DEL_ANIO, ANIO
};

ValidadorFecha::ValidadorFecha(char _tipo, const Glib::ustring& _nombre)
: Validador(_tipo, _nombre) {
    for (unsigned i = 0; i < CANT_COMBO; ++i)
        valores[valoresAcotados[i]] = valoresMapa[i];
}

Campos ValidadorFecha::getCampos(unsigned i) {
    Campos camposAcotados;
    if (i != 0)
        return camposAcotados;

    camposAcotados.assign(valoresAcotados, valoresAcotados+CANT_COMBO);

    return camposAcotados;
}

Glib::ustring ValidadorFecha::validar(Campos& acotados, Campos& noAcotados) {
    Glib::ustring tipo = *(acotados.begin());
    std::map< Glib::ustring, valMapa >::iterator it = valores.find(tipo);
    if (it == valores.end()) {
        Glib::ustring msj = "Valor no válido para tipo de fecha: ";
        return msj + tipo;
    }

    switch(it->second) {
        case DIA:               return validarPorDia(noAcotados);
        case MES:               return validarPorMes(noAcotados);
        case BIMESTRE:          return validarPorBimestre(noAcotados);
        case TRIMESTRE:         return validarPorTrimestre(noAcotados);
        case CUATRIMESTRE:      return validarPorCuatrimestre(noAcotados);
        case SEMESTRE:          return validarPorSemestre(noAcotados);
        case SEMANA_DEL_ANIO:   return validarPorSemanaDelAnio(noAcotados);
        case ANIO:              return validarPorAnio(noAcotados);
        default: throw "WTF exception!";
    }
}

Glib::ustring ValidadorFecha::validar(Glib::ustring& acotado,
                                      Glib::ustring& noAcotado) {
    throw "Fecha tiene que tener 3 campos no acotados (día, mes, año)";
    return STR_NULA;
}

Campos ValidadorFecha::getEstadoNoAcotados(Campos& acotados) {
    Campos metadata;

    Glib::ustring tipo = *(acotados.begin());
    std::map< Glib::ustring, valMapa >::iterator it = valores.find(tipo);
    if (it == valores.end()) {
        throw "WTF exception!";
    }

    switch(it->second) {
        case DIA:               return getMetadata(true, true, true);
        case MES:
        case BIMESTRE:
        case TRIMESTRE:
        case CUATRIMESTRE:
        case SEMESTRE:
        case SEMANA_DEL_ANIO:   return getMetadata(false, true, true);
        case ANIO:              return getMetadata(false, false, true);
        default: throw "WTF exception!";
    }
}

Glib::ustring ValidadorFecha::getEstadoNoAcotados(Glib::ustring& acotado) {
    throw "Fecha tiene que tener 3 campos no acotados (día, mes, año)";
    return STR_NULA;
}

Campos ValidadorFecha::getMetadata(bool showDia, bool showMes, bool showAnio) {
    Campos metadata;
    if (showDia)
        metadata.push_back(SHOW);
    else
        metadata.push_back(HIDE);

    if (showMes)
        metadata.push_back(SHOW);
    else
        metadata.push_back(HIDE);

    if (showAnio)
        metadata.push_back(SHOW);
    else
        metadata.push_back(HIDE);

    return metadata;
}

Glib::ustring ValidadorFecha::validarAnio(Glib::ustring& anio) {
    if (anio.size() == 0)
        return STR_NULA;

    Glib::ustring validacion = validarSoloNumeros(anio);
    if (validacion != STR_NULA)
        return validacion;

    validacion = validarPorRango(anio, 1970, 2012); /**@todo año actual como máximo */
    if (validacion != STR_NULA)
        return validacion;

    return STR_NULA;
}

Glib::ustring ValidadorFecha::validarPorAnio(Campos& noAcotados) {
    Campos::iterator it = noAcotados.begin();
    Glib::ustring& anio = *(++++it);

    return validarAnio(anio);
}

Glib::ustring ValidadorFecha::validarPorMes(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 12);
}

Glib::ustring ValidadorFecha::validarPorBimestre(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 6);
}

Glib::ustring ValidadorFecha::validarPorTrimestre(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 4);
}

Glib::ustring ValidadorFecha::validarPorCuatrimestre(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 3);
}

Glib::ustring ValidadorFecha::validarPorSemestre(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 2);
}

Glib::ustring ValidadorFecha::validarPorSemanaDelAnio(Campos& noAcotados) {
    return validarGenericaPorRango(noAcotados, 1, 52);
}
#include <iostream>
Glib::ustring ValidadorFecha::validarPorDia(Campos& noAcotados) {
    Glib::ustring validacion = validarPorMes(noAcotados);
    if (validacion != STR_NULA)
        return validacion;


    Campos::iterator it = noAcotados.begin();
    Glib::ustring& dia =*(it++);
    Glib::ustring mes = *(it++);
    Glib::ustring anio = *(it);

    int mes_int;
    int anio_int;
    std::stringstream ss;
    if (mes.size() == 0)
        mes_int = 1;
    else {
        ss << mes;
        ss >> mes_int;
        ss.str(std::string());
        /** @todo hacerlo con el método genérico deconversión */
    }
    if (anio.size() == 0)
        anio_int = 1999;
    else {
        ss << anio;
        ss >> anio_int;
        /** @todo hacerlo con el método genérico deconversión */
    }

    validacion = validarSoloNumeros(dia);
    if (validacion != STR_NULA)
        return validacion;

    if (mes_int == FEBRERO) {
        // anio mod 4, para ver si es bisiesto
        if (anio_int & 0x3)
            validacion = validarPorRango(dia, 1, 28);
        else
            validacion = validarPorRango(dia, 1, 29);
    } else {
        if (mes_int < AGOSTO) {
            // mes mod 2 para ver si es impar
            if (mes_int & 0x1)
                validacion = validarPorRango(dia, 1, 31);
            else
                validacion = validarPorRango(dia, 1, 30);
        } else {
            if (mes_int & 0x1)
                validacion = validarPorRango(dia, 1, 30);
            else
                validacion = validarPorRango(dia, 1, 31);
        }
    }

    return validacion;
}

Glib::ustring ValidadorFecha::validarGenericaPorRango(Campos& noAcotados,
                                                      int min,
                                                      int max) {
    Campos::iterator it = noAcotados.begin();
    Glib::ustring& mes = *(++it);
    Glib::ustring& anio = *(++it);

    Glib::ustring validacion = validarAnio(anio);
    if (validacion != STR_NULA)
        return validacion;

    validacion = validarSoloNumeros(mes);
    if (validacion != STR_NULA)
        return validacion;

    return validarPorRango(mes, min, max);
}
