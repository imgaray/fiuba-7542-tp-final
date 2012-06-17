#include "Validador.h"

#define ERROR_SOLO_NUMEROS              "Este campo sólo admite números"
#define ERROR_SOLO_NUMEROS_POSITIVOS    ERROR_SOLO_NUMEROS " positivos"
#define ERROR_SOLO_NUMEROS_NATURALES    ERROR_SOLO_NUMEROS " no decimales"
#define ERROR_SOLO_LETRAS               "Este campo sólo admite letras"
#define ERROR_SOLO_ALFANUMERICO         ERROR_SOLO_NUMEROS " y letras"
#define ERROR_FUERA_DE_RANGO            "El campo debe estar entre "

Validador::Validador(char _tipo, const Glib::ustring& _nombre)
:nombre(_nombre), tipo(_tipo) {}

Glib::ustring Validador::validarSoloNumeros(Glib::ustring& campo) {
    if (campo.size() == 0)
        return STR_NULA;

    unsigned pos = campo.find_first_of(".,");
    if (pos != Glib::ustring::npos) {
        campo.erase(pos);
        return ERROR_SOLO_NUMEROS_NATURALES;
    }

    pos = campo.find_first_of('-');
    if (pos != Glib::ustring::npos) {
        campo.erase(pos);
        return ERROR_SOLO_NUMEROS_POSITIVOS;
    }

    pos = campo.find_first_not_of("0123456789");
    if (pos != Glib::ustring::npos) {
        campo.erase(pos);
        return ERROR_SOLO_NUMEROS;
    }

    return STR_NULA;
}
Glib::ustring Validador::validarSoloLetras(Glib::ustring& campo) {
    std::string letras = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ "
                         "abcdefghijklmnñopqrstuvwxyz"
                         "ÁÉÍÓÚáéíóúü";
    unsigned pos = campo.find_first_not_of(letras);

    if (pos != Glib::ustring::npos) {
        campo.erase(pos);
        return ERROR_SOLO_LETRAS;
    }

    return STR_NULA;
}

Glib::ustring Validador::validarSoloAlfanumericos(Glib::ustring& campo) {
    std::string alfanumerico = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ "
                               "abcdefghijklmnñopqrstuvwxyz"
                               "ÁÉÍÓÚáéíóúü"
                               "01234567890";
    unsigned pos = campo.find_first_not_of(alfanumerico);

    if (pos != Glib::ustring::npos) {
        campo.erase(pos);
        return ERROR_SOLO_LETRAS;
    }

    return STR_NULA;
}
#include  <iostream>
Glib::ustring Validador::validarPorRango(Glib::ustring& campo,
                                         int min, int max) {
    if (campo.size() == 0)
        return STR_NULA;

    std::stringstream ss;
    std::string min_str;
    ss << min;
    min_str = ss.str();
    if (campo.size() < min_str.size())
        return STR_NULA;

    ss.str(std::string());
    int valorCampo;
    ss << campo;
    ss >> valorCampo;

    if (min > valorCampo ||
        max < valorCampo) {
        // asumiendo que se valida el ingreso con cada modificación,
        // borro el último char para asegurar que está en rango
        campo.erase(--campo.end());
        std::ostringstream oss;
        oss << min << " y " << max;
        Glib::ustring tooltip(ERROR_FUERA_DE_RANGO);
        tooltip += oss.str();

        return tooltip;
    }

    return STR_NULA;
}
