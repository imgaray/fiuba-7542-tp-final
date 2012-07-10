#ifndef HECHO_H
#define HECHO_H

#include <glibmm/ustring.h>

/** @class Hecho
 * Encapsula un par < etiqueta, valor >.
 */
class Hecho {
    public:
        /**
         * Constructor copia.
         * @param original el otro Hecho
         */
        Hecho(const Hecho& original);
        /**
         * Constructor.
         * @param etiqueta nombre del dato del área referente
         * @param valor valor del dato del área referente
         */
        Hecho(const Glib::ustring& etiqueta, double valor);
        /**
         * Destructor.
         */
        ~Hecho();

        Hecho& operator=(const Hecho& original);

        const Glib::ustring& getEtiqueta() const;
        double getValor() const;
    private:
        Glib::ustring etiqueta;
        double valor;
};

#endif  // HECHO_H
