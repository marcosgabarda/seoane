#ifndef NUEVOARTICULODIALOG_H
#define NUEVOARTICULODIALOG_H

#include <QtGui/QWidget>
#include "ui_NuevoArticuloDialog.h"
#include "ListarArticulos.h"
#include "../Negocio/CapaNegocio.h"

class NuevoArticuloDialog : public QDialog
{
    Q_OBJECT

public:
    NuevoArticuloDialog(CapaNegocio * const cn,QWidget *parent = 0, Articulo *a=0);
    ~NuevoArticuloDialog();
    
private slots:
	void guardar();

private:
    Ui::AltaArticuloDialogClass ui;
    bool comprobarDatos();
    CapaNegocio *capaNegocio;
    Articulo *articulo;
    ListarArticulos *padre;
};

#endif // ALTAARTICULODIALOG_H
