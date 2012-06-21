#ifndef FILTRADOR_RESULTADO_FECHA_H
#define FILTRADOR_RESULTADO_FECHA_H

#include "FiltradorResultado.h"

class FiltradorResultadoFecha : public FiltradorResultado {
    public:
        FiltradorResultadoFecha(const Glib::ustring& fecha,
                                const Glib::ustring& valorCombo,
                                const Glib::ustring& valorEntrada);
        virtual ~FiltradorResultadoFecha();

        (Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
        int i;  // iésimo valor del combobox posible
        Fecha f;
};

#endif  // FILTRADOR_RESULTADO_FECHA_H

