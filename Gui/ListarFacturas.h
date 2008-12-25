#ifndef LISTARFACTURAS_H
#define LISTARFACTURAS_H

#include <QtGui>
#include <list>
#include "../Negocio/CapaNegocio.h"
#include "../Datos/CriterioBusqueda.h"
#include "ui_ListarFacturas.h"


class ListarFacturas : public QWidget
{
    Q_OBJECT

public:
    ListarFacturas(CapaNegocio * const cn, QWidget *parent = 0, CriterioBusqueda* cb = 0);
    ~ListarFacturas();
    void addRow();
    void actualizar();

private slots:
	void mostrar();
	void borrar();
    
private:
    Ui::ListarFacturasClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    list<Factura> lista;
    CriterioBusqueda *cb;
    
protected:
	void resizeEvent(QResizeEvent *event);
    
};

#endif // LISTARFACTURAS_H
