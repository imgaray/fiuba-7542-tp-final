#ifndef FILTRADOR_RESULTADO_HECHO_H
#define FILTRADOR_RESULTADO_HECHO_H

#include "FiltradorResultado.h"
#include "Definiciones.h"

/** @class FiltradorResultadoHecho
 * Resultado de tipo hecho.
 */
class FiltradorResultadoHecho : public FiltradorResultado {
    public:
        /**
         * Constructor.
         * @param hecho nombre del campo
         * @param agregacion nombre de la agregación
         */
        FiltradorResultadoHecho(const Glib::ustring& hecho,
                                const Glib::ustring& agregacion);
        /**
         * Destructor.
         */
        virtual ~FiltradorResultadoHecho();

        void filtrar(Consulta& c);

    private:
        int i;
        Glib::ustring hecho;
        Agregacion agregacion;
};

#endif  // FILTRADOR_RESULTADO_HECHO_H
