#ifndef LISTARPRESUPUESTOS_H
#define LISTARPRESUPUESTOS_H

#include <QtGui>
#include "../Negocio/CapaNegocio.h"
#include "ui_ListarPresupuestos.h"
#include "../Datos/CriterioBusqueda.h"

class ListarPresupuestos : public QWidget
{
    Q_OBJECT

public:
    ListarPresupuestos(CapaNegocio * const cn, QWidget *parent = 0, CriterioBusqueda *cb = 0);
    ~ListarPresupuestos();
    void addRow();
    void actualizar();

private slots:
	void mostrar();
	void borrar();

private:
    Ui::ListarPresupuestosClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    list<Presupuesto> lista;
    CriterioBusqueda *cb;
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // LISTARPRESUPUESTOS_H
