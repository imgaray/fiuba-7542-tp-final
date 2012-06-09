#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H

#include <gtkmm/window.h>
#include <gtkmm/builder.h>

class VentanaClienteDinamica;

class VentanaCliente : public Gtk::Window {
    public:
        VentanaCliente(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaCliente();
        void personalizar(const char* archivo);
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        VentanaClienteDinamica* pVDinamica;
        void on_actualizar_button_clicked();
        void on_detenerActualizar_button_clicked();
        void on_exportarPDF_button_clicked();
        void on_configurar_button_clicked();
        void on_salir_button_clicked();
};

#endif  // VENTANA_CLIENTE_H
