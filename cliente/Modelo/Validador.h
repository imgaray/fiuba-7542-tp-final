#ifndef VALIDADOR_H
#define VALIDADOR_H

#include "Filtrador.h"

#define HIDE "_hide_"
#define SHOW "_show_"

#ifndef STR_NULA
#define STR_NULA ""
#endif

class Validador {
    public:
        Validador(char tipo, const Glib::ustring& nombre);

        virtual Campos getCampos(unsigned i = 0) = 0;

        /**
         * @brief Valida el estado de los campos de un filtrador.
         * @param acotados      lista de los campos acotados
         * @param noAcotados    lista de los campos no acotados
         * @return mensaje para un tooltip, si hay error
         *
         * Los campos se pasan por referencia para que este método pueda
         * modificarlos. Por ejemplo, si un campo sólo admite caracteres
         * numéricos, y se ingresara una letra, este método se la saca y
         * devuelve un mensaje inormativo al respecto.
         */
        virtual Glib::ustring validar(Campos& acotados, Campos& noAcotados) = 0;

        /**
         * @brief sobrecarga simplificada del anterior
         * @param acotado   valor del campo acotado
         * @param noAcotado valor del campo no acotado
         * @return mensaje tooltip, si hubo error
         *
         * Sobrecarga para los casos de un sólo campo de cada tipo
         */
        virtual Glib::ustring validar(Glib::ustring& acotado,
                                      Glib::ustring& noAcotado) = 0;

        /**
         * @brief informa algo de los campos no acotados, según los no acotados
         * @param acotados    lista de los campos acotados
         * @return información sobre el estado de los no acotados
         *
         * En esa lista de metadata se escribirá HIDE o SHOW, según deban
         * ocultarse o no los campos. Naturalmente,
         * noAcotados.size() == metadataNoAcotados.size()
         */
        virtual Campos getEstadoNoAcotados(Campos& acotados) = 0;
        /**
         * @brief sobrecarga del anterior, para cuando hay sólo un campo
         */
        virtual Glib::ustring getEstadoNoAcotados(Glib::ustring& acotado) = 0;

    protected:
        Glib::ustring nombre;
        char tipo;
        Glib::ustring validarSoloNumeros(Glib::ustring& campo);
        Glib::ustring validarSoloLetras(Glib::ustring& campo);
        Glib::ustring validarSoloAlfanumericos(Glib::ustring& campo);
        /// asumiendo que ya se validó que sean sólo números
        /// verifica si min <= campo <= max
        Glib::ustring validarPorRango(Glib::ustring& campo, int min, int max);
};

#endif  // VALIDADOR_H
