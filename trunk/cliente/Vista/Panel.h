#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/frame.h>
#include <gtkmm/viewport.h>
#include <gtkmm/spinner.h>
#include <gtkmm/label.h>

class Grafico;
class Tabla;
class FiltradoresPanel;
class Consultante;

/** @class Panel
 * Clase que representa visualmente una consulta configurada. Además de
 * contener un consultante (sea gráfico o tabla), tiene un conjunto de
 * filtradores, y el título con que fue guardado.
 */
class Panel : public Gtk::Frame {
    public:
        /**
         * Constructor.
         * @param label título del panel
         */
        Panel(const Glib::ustring& label);
        /**
         * Destructor.
         */
        ~Panel();

        // Agrega también a los filtradores, pidiéndoselos al gráfico
        void setContenido(Grafico& g);
        void setContenido(Tabla& t);

        Consultante* getConsultante();

    private:
        Gtk::HBox etiquetaCompuesta;
        Gtk::Label etiqueta;
        Gtk::Spinner spinner;

        Gtk::VBox box;
        Gtk::ScrolledWindow scrWin;
        Gtk::Viewport* pViewport;

        Consultante* consultante;
};

#endif  // PANEL_H__

