#ifndef NUEVOCLIENTEDIALOG_H
#define NUEVOCLIENTEDIALOG_H

#include <QtGui/QDialog>
#include "ui_NuevoClienteDialog.h"
#include "../Negocio/CapaNegocio.h"
#include "ListarClientes.h"
#include <list>

class NuevoClienteDialog : public QDialog
{
    Q_OBJECT

public:
    NuevoClienteDialog(CapaNegocio * const cn, QWidget *parent = 0, Cliente *c = 0);
    ~NuevoClienteDialog();
    void addRow();
    
private slots:

	void guardar();
	void nuevoTelefono();
	void borrarTelefono();

protected:
	//Redefinicion del manejador del evento de cambio de tamanyo
	void resizeEvent(QResizeEvent *event);
	void keyPressEvent(QKeyEvent* event);
	
private:
    Ui::NuevoClienteDialogClass ui;
    CapaNegocio *capaNegocio;
    Cliente *cliente;
    ListarClientes *padre;
    bool comprobarDatos();
};

#endif // NUEVOCLIENTEDIALOG_H
