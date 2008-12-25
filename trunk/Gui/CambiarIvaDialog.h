#ifndef CAMBIARIVADIALOG_H
#define CAMBIARIVADIALOG_H

#include <QtGui/QDialog>
#include "ui_CambiarIvaDialog.h"
#include "../Negocio/CapaNegocio.h"

class CambiarIvaDialog : public QDialog
{
    Q_OBJECT

public:
    CambiarIvaDialog(CapaNegocio * const cn, QWidget *parent = 0);
    ~CambiarIvaDialog();

private slots:
    void cambiarValor();

private:
    Ui::CambiarIvaDialogClass ui;
    CapaNegocio *capaNegocio;
};

#endif // CAMBIARIVADIALOG_H
