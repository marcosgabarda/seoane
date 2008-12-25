#ifndef LISTARARTICULOS_H
#define LISTARARTICULOS_H

#include <QtGui>
#include "../Negocio/CapaNegocio.h"
#include <list>
#include "ui_ListarArticulos.h"
#include "../Datos/CriterioBusqueda.h"

class ListarArticulos : public QWidget
{
    Q_OBJECT

public:
    ListarArticulos(CapaNegocio * const cn, QWidget *parent = 0, CriterioBusqueda* cb =0);
    ~ListarArticulos();
    void addRow();
    void actualizar();

private slots:
	void mostrar();
	void borrar();

private:
    Ui::ListarArticulosClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    list<Articulo> lista;
    CriterioBusqueda *cb;
    
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // LISTARARTICULOS_H
