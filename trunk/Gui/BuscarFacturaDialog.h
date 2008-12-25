#ifndef BUSCARFACTURADIALOG_H
#define BUSCARFACTURADIALOG_H

#include <QtGui/QDialog>
#include <QtGui>
#include "../Negocio/CapaNegocio.h"
#include "ui_BuscarFacturaDialog.h"

class BuscarFacturaDialog : public QDialog
{
    Q_OBJECT

public:
    BuscarFacturaDialog(CapaNegocio *cn, QWidget *parent = 0);
    ~BuscarFacturaDialog();

private slots:
	void accept();
    
private:
    Ui::BuscarFacturaDialogClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
    
protected:
	void resizeEvent(QResizeEvent *event);    
};

#endif // BUSCARFACTURADIALOG_H
