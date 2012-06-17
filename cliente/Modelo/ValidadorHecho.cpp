#include "ValidadorHecho.h"

ValidadorHecho::ValidadorHecho(char _tipo, const Glib::ustring& _nombre)
: Validador(_tipo, _nombre) {

}

Campos ValidadorHecho::getCampos(unsigned i) {
    if (i > 0)
        throw "Los hechos se componen de 1 campo acotado";

    Campos c;
    if (tipo == FILTRO) {
        c.push_back(">");
        c.push_back("<");
    } else if (tipo == RESULTADO) {
        c.push_back("NADA");
        c.push_back("SUM");
        c.push_back("MAX");
        c.push_back("MIN");
        c.push_back("PROM");
        c.push_back("CONT");
    }

    return c;
}

Glib::ustring ValidadorHecho::validar(Campos& acotados, Campos& noAcotados) {
    if (acotados.size() == 1 && noAcotados.size() == 1)
        return validar(*acotados.begin(), *noAcotados.begin());
    else
        throw "Los hechos se componen de 1 campo acotado y 1 no acotado";
}

Glib::ustring ValidadorHecho::validar(Glib::ustring& acotado,
                                      Glib::ustring& noAcotado) {
    Glib::ustring validacion = validarSoloNumeros(noAcotado);
    if (validacion != STR_NULA)
        return validacion;

    return validarPorRango(noAcotado, 0, std::string::npos/2);
}


Campos ValidadorHecho::getEstadoNoAcotados(Campos& acotados) {
    if (acotados.size() == 1) {
        Campos c;
        c.push_back(getEstadoNoAcotados(*acotados.begin()));
        return c;
    }
    else
        throw "Los hechos se componen de 1 campo acotado";
}


Glib::ustring ValidadorHecho::getEstadoNoAcotados(Glib::ustring& acotado) {
    if (tipo == FILTRO)
        return SHOW;
    else
        return HIDE;
}

