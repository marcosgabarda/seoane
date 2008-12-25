#ifndef BUSCARARTICULODIALOG_H
#define BUSCARARTICULODIALOG_H

#include <QtGui>
#include "ui_BuscarArticuloDialog.h"
#include "../Negocio/CapaNegocio.h"

class BuscarArticuloDialog : public QDialog
{
    Q_OBJECT

public:
    BuscarArticuloDialog(CapaNegocio *cn, QWidget *parent = 0);
    ~BuscarArticuloDialog();
private slots:
	void accept();    
    
private:
    Ui::BuscarArticuloDialogClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // BUSCARARTICULODIALOG_H
