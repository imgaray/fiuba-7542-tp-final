#ifndef FILTRADOR_RESULTADO_FECHA_H
#define FILTRADOR_RESULTADO_FECHA_H

#include "FiltradorResultado.h"

class FiltradorResultadoFecha : public FiltradorResultado {
    public:
        FiltradorResultadoFecha(const Glib::ustring& fecha,
                                const Glib::ustring& valorCombo,
                                const Glib::ustring& valorEntrada);
        virtual ~FiltradorResultadoFecha();

        Consulta& filtrar(Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
};

#endif  // FILTRADOR_RESULTADO_FECHA_H

