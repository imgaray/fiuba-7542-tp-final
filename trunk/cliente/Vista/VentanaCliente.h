#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H

#include <gtkmm/window.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/aboutdialog.h>
#include "../Modelo/ServidorRemoto.h"
#include "Buildable.h"

class VentanaClienteDinamica;
class DialogoAutentif;
class VentanaAdminConfiguracion;

class VentanaCliente : public Gtk::Window , public Buildable {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        VentanaCliente(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        /**
         * @brief Destructor. Libera explícitamente las ventanas top-level.
         */
        ~VentanaCliente();

        /**
         * @brief Construye la parte dinámica y configurable de la aplicación.
         * @param archivo nombre del archivo con la configuración
         *
         * Si el archivo no existe, lo crea y empieza con una configuración vacía.
         */
        void personalizar(const char* archivo);
    private:
        VentanaClienteDinamica* pVDinamica;
        DialogoAutentif* pDAutentifAdmin;
        VentanaAdminConfiguracion* pVAdminConfig;
        Gtk::AboutDialog* pDAbout;
        std::map< const char*, Gtk::ToolButton* > botones;
        ServidorRemoto server;

        void initVentanas();
        void initBotones();
        void initBarraDeMenu();

        void on_puede_actualizar(bool puede);
        void on_actualizacion_solicitada(Consultante* c);

        void on_conectar_button_clicked();
        void on_actualizar_button_clicked();
        void on_detenerActualizar_button_clicked();
        void on_configurar_button_clicked();
        void on_salir_button_clicked();
        void on_acerca_de_button_clicked();

        bool on_timeout();
};

#endif  // VENTANA_CLIENTE_H
