#ifndef VENTANA_CLIENTE_H
#define VENTANA_CLIENTE_H

#include <map>
#include <gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include <gtkmm/table.h>
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Personalizador.h"

class VentanaCliente : public Gtk::Window {
    public:
        VentanaCliente(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& builder);
        ~VentanaCliente();
        void personalizar(const char* archivo);
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        Gtk::Notebook* pNotebook;
        Personalizador dynBuilder;
        void on_actualizar_button_clicked();
        void on_detenerActualizar_button_clicked();
        void on_exportarPDF_button_clicked();
        void on_configurar_button_clicked();
        void on_salir_button_clicked();
};

#endif  // VENTANA_CLIENTE_H
