#ifndef BUSCARPRESUPUESTODIALOG_H
#define BUSCARPRESUPUESTODIALOG_H

#include <QtGui/QDialog>
#include <QtGui>
#include "../Negocio/CapaNegocio.h"
#include "ui_BuscarPresupuestoDialog.h"

class BuscarPresupuestoDialog : public QDialog
{
    Q_OBJECT

public:
    BuscarPresupuestoDialog(CapaNegocio *cn, QWidget *parent = 0);
    ~BuscarPresupuestoDialog();

private slots:
	void accept();
    
private:
    Ui::BuscarPresupuestoDialogClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    
protected:
	void resizeEvent(QResizeEvent *event);    
};

#endif // BUSCARPRESUPUESTODIALOG_H
