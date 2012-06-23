#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H

#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/toolbutton.h>
#include "../Modelo/ServidorRemoto.h"

class VentanaClienteDinamica;
class DialogoAutentif;
class VentanaAdminConfiguracion;

class VentanaCliente : public Gtk::Window {
    public:
        VentanaCliente(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaCliente();
        void personalizar(const char* archivo);
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        VentanaClienteDinamica* pVDinamica;
        DialogoAutentif* pDAutentifAdmin;
        VentanaAdminConfiguracion* pVAdminConfig;
        std::map< const char*, Gtk::ToolButton* > botones;
        ServidorRemoto server;

        void on_page_switched(GtkNotebookPage* page, guint page_num);
        void on_actualizacion_solicitada(Consultante* c);

        void on_conectar_button_clicked();
        void on_actualizar_button_clicked();
        void on_detenerActualizar_button_clicked();
        void on_exportarPDF_button_clicked();
        void on_configurar_button_clicked();
        void on_salir_button_clicked();

        bool on_timeout();
        bool on_idle();
};

#endif  // VENTANA_CLIENTE_H
