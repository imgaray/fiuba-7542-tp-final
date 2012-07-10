#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H

#include <gtkmm/window.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/aboutdialog.h>
#include "../Modelo/ServidorRemoto.h"
#include "Buildable.h"
#include "gtkmm/misc.h"

class VentanaClienteDinamica;
class DialogoAutentif;
class VentanaAdminConfiguracion;


/** @class VentanaCliente
 * Ventana principal de la aplicación.
 *
 * De aquí se conectan las señales principales que dan lugar a otras ventanas,
 * y se muestran las consultas configuradas.
 */
class VentanaCliente : public Gtk::Window , public Buildable {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        VentanaCliente(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        /**
         * Destructor. Libera explícitamente las ventanas top-level.
         */
        ~VentanaCliente();

        /**
         * Construye la parte dinámica y configurable de la aplicación.
         *
         * Si el archivo no existe, lo crea y empieza con una configuración
         * vacía.
         * @param archivo nombre del archivo con la configuración
         * @throw ErrorSerializacionXML
         */
        void personalizar(const char* archivo);
    private:
        VentanaClienteDinamica* pVDinamica;
        DialogoAutentif* pDAutentifAdmin;
        VentanaAdminConfiguracion* pVAdminConfig;
        Gtk::AboutDialog* pDAbout;
        std::map< const char*, Gtk::ToolButton* > botones;
        ServidorRemoto server;


        /**
         * Inicializa los punteros a las ventanas y diálogos.
         */
        void initVentanas();

        /**
         * Inicializa el mapa de botones y conecta sus señales.
         */
        void initBotones();

        /**
         * Conecta las señales a los ítems de la barra de menú.
         */
        void initBarraDeMenu();

        /**
         * Signal handler para la solicitud explícita de actualización.
         * @param c el consultante que solicitó ser actualizado.
         */
        void on_actualizacion_solicitada(Consultante* c);


        /**
         * Signal handler para el click sobre el botón "Conectar".
         *
         * Conecta al cliente al servidor, mostrando un mensaje de error si
         * no lo consigue
         */
        void on_conectar_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Actualizar".
         *
         * Actualiza todas las consultas de la pestaña actual, excepto aquellas
         * no disponibles (alguna con input mal formado, por ejemplo).
         */
        void on_actualizar_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Detener actualización".
         *
         * Cancela todas las actualizaciones en proceso para la tab
         * seleccionada.
         */
        void on_detenerActualizar_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Configurar".
         *
         * Lanza un cuadro para ingresar la contraseña del administrador. Si
         * se la ingresa, abre la ventana de configuración de paneles.
         */
        void on_configurar_button_clicked();


        /**
         * Signal handler para el click sobre el botón "Salir".
         *
         * Cierra la aplicación.
         */
        void on_salir_button_clicked();

        /**
         * Signal handler para el click sobre el ítem de menú "Acerca de".
         *
         * Lanza la ventana "Acerca de...".
         */
        void on_acerca_de_button_clicked();


        /**
         * Signal handler para un evento cíclico.
         * @return true siempre, el manejo del evento termina acá.
         *
         * Procesa las respuestas que el servidor tenga disponibles.
         */
        bool on_timeout();
};

#endif  // VENTANA_CLIENTE_H
