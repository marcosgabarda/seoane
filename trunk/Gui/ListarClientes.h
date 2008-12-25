#ifndef LISTARCLIENTES_H
#define LISTARCLIENTES_H

#include <QtGui>
#include "ui_ListarClientes.h"
#include <list>
#include "../Negocio/CapaNegocio.h"
#include "../Datos/CriterioBusqueda.h"

class ListarClientes : public QWidget
{
    Q_OBJECT

public:
    ListarClientes(CapaNegocio * const cn, QWidget *parent = 0, CriterioBusqueda* cb = 0);
    ~ListarClientes();
    void addRow();
    void actualizar();

private slots:
	void mostrar();
	void borrar();

private:
    Ui::ListarClientesClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    list<Cliente> lista;
    CriterioBusqueda *cb;

protected:
	void resizeEvent(QResizeEvent *event);    
};

#endif // LISTARCLIENTES_H
