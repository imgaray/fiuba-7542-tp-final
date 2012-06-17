#include "ValidadorDimension.h"

ValidadorDimension::ValidadorDimension(char _tipo,
                                       const Glib::ustring& _nombre,
                                       bool _admiteNumeros)
: Validador(_tipo, _nombre), admiteNumeros(_admiteNumeros) {

}

/** @todo para probar, harcodeo, pero esto se tiene que resolver con una consulta */
Campos ValidadorDimension::getCampos(unsigned i) {
    if (i > 0)
        throw "Las dimensiones que no son fecha se componen de 1 campo acotado";

    Campos c;
    if (nombre == "Vendedor") {
        c.push_back("Migue");
        c.push_back("Nacho");
        c.push_back("Seba");
    } else if (nombre == "Sucursal") {
        c.push_back("Avellaneda");
        c.push_back("San Miguel");
        c.push_back("Villa Urquiza");
    } else if (nombre == "Marca") {
        c.push_back("Apple");
        c.push_back("Samsung");
        c.push_back("HP");
    } else if (nombre == "Producto") {
        c.push_back("Galaxy SII");
        c.push_back("iPod Nano");
        c.push_back("Tu hermana");
    }

    return c;
}

Glib::ustring ValidadorDimension::validar(Campos& acotados, Campos& noAcotados) {
    if (acotados.size() == 1 && noAcotados.size() == 1)
        return validar(*acotados.begin(), *noAcotados.begin());
    else
        throw "Las dimensiones que no son fecha se componen de 1 campo acotado y 1 no acotado";
}

Glib::ustring ValidadorDimension::validar(Glib::ustring& acotado,
                                          Glib::ustring& noAcotado) {
    if (admiteNumeros)
        return validarSoloAlfanumericos(noAcotado);
    else
        return validarSoloLetras(noAcotado);
}


Campos ValidadorDimension::getEstadoNoAcotados(Campos& acotados) {
    if (acotados.size() == 1) {
        Campos c;
        c.push_back(getEstadoNoAcotados(*acotados.begin()));
        return c;
    }
    else
        throw "Las dimensiones que no son fecha se componen de 1 campo acotado";
}


Glib::ustring ValidadorDimension::getEstadoNoAcotados(Glib::ustring& acotado) {
    return SHOW;
}
