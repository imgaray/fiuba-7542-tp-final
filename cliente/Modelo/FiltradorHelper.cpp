#include "FiltradorHelper.h"
#include "Utilitario.h"
#include "M_Fechas.h"

FiltradorHelper FiltradorHelper::instancia;

#define CANT_COMBO_FECHA 8
#define CANT_COMBO_HECHO 3
#define CANT_COMBO_AGREGACIONES 6

#define VALOR_COMBO_FECHA_NAVEGACION 7
Glib::ustring FiltradorHelper::comboFecha[CANT_COMBO_FECHA] = {
    "Año", "Mes", "Bimestre", "Trimestre", "Cuatrimestre", "Semestre",
    "Semana del año", "Día"
};
Glib::ustring FiltradorHelper::comboHechoInput[CANT_COMBO_HECHO] = {
    ">", "=", "<"
};
Glib::ustring FiltradorHelper::agregPosibles[CANT_COMBO_AGREGACIONES] = {
    "NADA", "SUM", "MAX", "MIN", "PROM", "CONT"
};

const FiltradorHelper& FiltradorHelper::getInstancia() {
    return instancia;
}

FiltradorHelper::FiltradorHelper() {}

void FiltradorHelper::popularComboFecha(Gtk::ComboBoxText* combo) const {
    popularCombo(combo, comboFecha, CANT_COMBO_FECHA);
}

void FiltradorHelper::popularComboHechoInput(Gtk::ComboBoxText* combo) const {
    popularCombo(combo, comboHechoInput, CANT_COMBO_HECHO);
}

void FiltradorHelper::popularComboAgregaciones(
    Gtk::ComboBoxText* combo) const {
    popularCombo(combo, agregPosibles, CANT_COMBO_AGREGACIONES);
}

int FiltradorHelper::perteneceAlComboFecha(const Glib::ustring& valor) const {
    return perteneceAlCombo(valor, comboFecha, CANT_COMBO_FECHA);
}

int FiltradorHelper::perteneceAlComboHechoInput(
    const Glib::ustring& valor) const {
    return perteneceAlCombo(valor, comboHechoInput, CANT_COMBO_HECHO);
}

int FiltradorHelper::perteneceAlAgregacionesPosibles(
    const Glib::ustring& valor) const {
    return perteneceAlCombo(valor, agregPosibles, CANT_COMBO_AGREGACIONES);
}

Fecha FiltradorHelper::validarFecha(int i_combo,
                                    const Glib::ustring& valor) const {
    Utilitario u;
    M_Fechas m_fechas;

    Fecha f_validada;
    Glib::ustring pri_str = u.separar(valor, '-', 0);
    Glib::ustring seg_str = u.separar(valor, '-', 1);
    Glib::ustring terc_str = u.separar(valor, '-', 2);

    int pri_int = -1;
    int seg_int = -1;
    int terc_int = -1;
    if (pri_str != STR_NULA)
        pri_int = u.convertirAEntero(pri_str);
    if (seg_str != STR_NULA)
        seg_int = u.convertirAEntero(seg_str);
    if (terc_str != STR_NULA)
        terc_int = u.convertirAEntero(terc_str);

    switch (i_combo) {
        // Año
        case 0: f_validada = m_fechas.anio(pri_str); break;
        // Mes
        case 1: f_validada = m_fechas.mes(pri_int, seg_str); break;
        // Bimestre
        case 2: f_validada = m_fechas.bimestre(pri_int, seg_str); break;
        // Trimestre
        case 3: f_validada = m_fechas.trimestre(pri_int, seg_str); break;
        // Cuatrimestre
        case 4: f_validada = m_fechas.cuatrimestre(pri_int, seg_str); break;
        // Semestre
        case 5: f_validada = m_fechas.semestre(pri_int, seg_str); break;
        // Semana del año
        case 6: f_validada = m_fechas.semana(pri_int, seg_str); break;
        // Día
        case 7: f_validada = m_fechas.fecha(pri_int, seg_int, terc_int); break;
        default: break;
    }
    return f_validada;
}

Glib::ustring FiltradorHelper::validarHecho(int i_combo,
                                            const Glib::ustring& valor) const {
    Utilitario u;
    int val_int = u.convertirAEntero(valor);
    if (val_int < 0)
        return STR_NULA;

    Glib::ustring val = comboHechoInput[i_combo];
    val += u.convertirAString(val_int);
    return val;
}

Agregacion FiltradorHelper::getAgregacion(int i_combo) const {
//
//    //@todo sacar los cout
//    std::cout << "\n\n\n\n\n\n\n\n\n\n";
//    std::cout << "Valor i_combo: "<< i_combo <<std::endl;
//    std::cout << "\n\n\n\n\n\n\n\n\n\n";

    switch (i_combo) {
        case 0:  return NADA;
        case 1:  return SUM;
        case 2:  return MAX;
        case 3:  return MIN;
        case 4:  return PROM;
        case 5:  return CONT;
        default: return NADA;
    }

}

Glib::ustring FiltradorHelper::getValorComboFechaParaNavegacion() const {
    return comboFecha[VALOR_COMBO_FECHA_NAVEGACION];
}

void FiltradorHelper::popularCombo(Gtk::ComboBoxText* combo,
                                   Glib::ustring valores[], int size) const {
    combo->clear_items();
    for (int i = 0; i < size; ++i)
        combo->append_text(valores[i]);
}

int FiltradorHelper::perteneceAlCombo(const Glib::ustring& valor,
                                      Glib::ustring valores[],
                                      int size) const {
    bool pertenece = false;
    int i = 0;
    while (!pertenece && i < size)
        pertenece = valor == valores[i++];

    if (pertenece)
        return --i;
    else
        return NO_PERTENECE;
}
