#ifndef FILTRADOR_CONFIG_MODELO_H
#define FILTRADOR_CONFIG_MODELO_H

#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/toolbutton.h>

#include "Serializable.h"

class FiltradoresTab;
class FiltradoresPanel;


/** @class FiltradorConfigModelo
 * Clase base para los modelos que están detrás de las vistas de configuración
 * de filtradores.
 *
 * Es identificable por un número, pero sólo sirve para cuando está en memoria.
 * Al persistirse, queda definido por el valor de tres strings:
 * -el campo de la base de datos por el que filtra
 * -un valor auxiliar, que sólo sirve cuando es seleccionado un hecho o fecha,
 * ingresado por combobox
 * -otro valor auxiliar, que sólo sirve para Filtro y Resultado, ingresado por
 * entry
 *
 * Para evitar elegir campos repetidos, cada vez que cambia su selección emite
 * una señal. Trabajando en conjunto con FiltradorConfigManager, la señal se
 * difunde y todos sus filtradores hermanos actualizan sus campos disponibles.
 *
 * Un método importante, en paralelo a los "concretarConfig" de las clases para
 * configurar paneles y tabs, es setFiltradorEn(), sobrecargado para actuar
 * distinto según se agregue a FiltradoresTab o FiltradoresPanel. Lo que hacen
 * es concretar su configuración como filtrador, agregando al conjunto de
 * filtradores.
 */
class FiltradorConfigModelo : public Serializable {
    public:
        /**
         * Constructor.
         * @param ID identificador de la instancia
         * @param camposDisponibles lista de los campos disponibles, para
         * popular su combobox
         */
        FiltradorConfigModelo(unsigned ID,
                            const std::list< std::string >& camposDisponibles);
        /**
         * Destructor.
         */
        ~FiltradorConfigModelo();

        void setVista(Gtk::ComboBoxText* comboDimension,
                      Gtk::ComboBoxText* comboFecha,
                      Gtk::ComboBoxText* comboHecho,
                      Gtk::Entry* entryExtra,
                      Gtk::ToolButton* botonEliminar);

        unsigned getID() const;

        /**
         * Actualiza los campos disponibles para elegir.
         * @param remover campo a remover de su combobox
         * @param agregar campo a agregar a su combobox
         */
        void actualizarCampos(const Glib::ustring& remover,
                              const Glib::ustring& agregar);

        sigc::signal< void, unsigned > signal_delete_filtrador();
        sigc::signal< void, Glib::ustring, Glib::ustring > signal_campo_changed();

        virtual void setFiltradorEn(FiltradoresTab* filtTab) = 0;
        virtual void setFiltradorEn(FiltradoresPanel* filtPanel) = 0;


        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    protected:

        virtual void completarAtributos() = 0;

        Gtk::ComboBoxText* comboDimension;
        Gtk::ComboBoxText* comboFecha;
        Gtk::ComboBoxText* comboHecho;
        Gtk::Entry* entryExtra;

        void conectarComboHecho();

        Glib::ustring campoSelecc, campoSeleccNuevo;
        Glib::ustring _valorCampo;
        Glib::ustring _campoAux;
    private:
        Gtk::ToolButton* botonEliminar;

        unsigned ID;

        sigc::signal< void, unsigned > _signal_delete_filtrador;
        sigc::signal< void, Glib::ustring, Glib::ustring > _signal_campo_changed;

        std::list< std::string > camposDisponibles;

        void setComboDimension(Gtk::ComboBoxText* comboDim);
        void setComboFecha(Gtk::ComboBoxText* comboFecha);
        virtual void setComboHecho(Gtk::ComboBoxText* comboHecho);
        void setEntryExtra(Gtk::Entry* entryExtra);
        void setBotonEliminar(Gtk::ToolButton* botonEliminar);
        virtual void especializarVista() = 0;

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de campo.
         *
         * Emite la señal _signal_campo_changed con el campo anteriormente
         * seleccionado y el nuevo. Además, especializa estados de la vista.
         */
        virtual void on_combo_dimension_changed() = 0;

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox auxiliar.
         *
         * Almacena en _campoAux la selección actual de pCombo.
         * @param pCombo puntero al combobox que emitió la señal
         */
        void on_combo_aux_changed(Gtk::ComboBoxText* pCombo);

        /**
         * Signal handler para el click del botón eliminar
         *
         * Emite la señal _signal_campo_changed para liberar su selección
         * actual, y la señal _signal_delete_filtrador(ID).
         */
        void on_boton_eliminar_clicked();
};

#endif  // FILTRADOR_CONFIG_MODELO_H
