#include "BuscarClienteDialog.h"
#include "ListarClientes.h"

BuscarClienteDialog::BuscarClienteDialog(CapaNegocio *cn, QWidget *parent)
    : QDialog(parent)
{
	padre = (QWorkspace *)parent;
	ui.setupUi(this);
	capaNegocio = cn;
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/BCliente.PNG")));
}

BuscarClienteDialog::~BuscarClienteDialog()
{

}

void BuscarClienteDialog::accept() {
	CriterioBusqueda *cb = new CriterioBusqueda();
	
	if (ui.lineEdit_3->text() != tr(""))
		cb->nombreCliente = new QString(ui.lineEdit_3->text());
	if (ui.lineEdit_2->text() != tr("")) {
		cb->codigoCliente = new int;
		*cb->codigoCliente = ui.lineEdit_2->text().toInt();
	}
	if (ui.lineEdit->text() != tr(""))
		cb->direccionCliente = new QString(ui.lineEdit->text());
	if (ui.lineEdit_4->text() != tr("")) {
			cb->telefono = new int;
			*cb->telefono = ui.lineEdit_4->text().toInt();
	}
	
	ListarClientes *lf = new ListarClientes(capaNegocio, padre , cb);
	padre->addWindow(lf);
	lf->show();
	
	this->close();
}

void BuscarClienteDialog::resizeEvent(QResizeEvent *event) {
	setFixedSize(event->size());
}
