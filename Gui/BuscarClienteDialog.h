#ifndef BUSCARCLIENTEDIALOG_H
#define BUSCARCLIENTEDIALOG_H

#include <QtGui>
#include "ui_BuscarClienteDialog.h"
#include "../Negocio/CapaNegocio.h"

class BuscarClienteDialog : public QDialog
{
    Q_OBJECT

public:
    BuscarClienteDialog(CapaNegocio *cn, QWidget *parent = 0);
    ~BuscarClienteDialog();

private slots:
	void accept();    
    
private:
    Ui::BuscarClienteDialogClass ui;
    CapaNegocio *capaNegocio;
    QWorkspace *padre;
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // BUSCARCLIENTEDIALOG_H
