#ifndef VENTANA_ADMIN_CONFIGURACION_H
#define VENTANA_ADMIN_CONFIGURACION_H

#include <list>
#include <gtkmm/window.h>
#include "Buildable.h"

class TabAdminConfig;
class TabAdminConfigConsultas;
class TabAdminConfigPassword;
class VentanaClienteDinamica;

class VentanaAdminConfiguracion : public Gtk::Window, public Buildable  {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        VentanaAdminConfiguracion(BaseObjectType* cobject,
                                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaAdminConfiguracion();

        void setVDinamica(VentanaClienteDinamica* pVDinamica);
        void setArchivoPersonalizador(const char* archivo);
    private:
        TabAdminConfigConsultas* tabConsultas;
        TabAdminConfigPassword* tabPassword;
        VentanaClienteDinamica* pVDinamica;
        std::list< TabAdminConfig* > tabs;


        /**
         * @brief Signal handler para signal_show.
         *
         * Llama a Gtk::Window::on_show() y borra el texto en las entries
         * para cambiar el password en la tercer pestaña.
         */
        void on_show();

        /**
         * @brief Signal handler para el click sobre el botón "Aplicar cambios".
         *
         * Apica los cambios realizados en cada pestaña, si son todos válidos.
         * Si no lo son, informa con un mensaje de error la pestaña errónea.
         */
        void on_aplicar_button_clicked();

        /**
         * @brief Signal handler para el click sobre el botón "Cancelar".
         *
         * Esconde la ventana. Las modificaciones efectuadas permanecerán en
         * memoria.
         */
        void on_cancelar_button_clicked();
};

#endif  // VENTANA_ADMIN_CONFIGURACION_H
