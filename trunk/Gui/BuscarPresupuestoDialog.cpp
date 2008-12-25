#include "BuscarPresupuestoDialog.h"
#include "../Datos/CriterioBusqueda.h"
#include "../Negocio/CapaNegocio.h"
#include "ListarPresupuestos.h"
#include <iostream>
using namespace std;

BuscarPresupuestoDialog::BuscarPresupuestoDialog(CapaNegocio *cn, QWidget *parent)
    : QDialog(parent)
{
	padre = (QWorkspace *)parent;
	ui.setupUi(this);
	capaNegocio = cn;
	setWindowTitle(tr("Buscar Presupuesto"));
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/BPresupuesto.PNG")));
	ui.checkBoxAl->setText("");
	ui.checkBoxDel->setText("");
	ui.dateEdit->setEnabled(false);
	ui.dateEdit_2->setEnabled(false);
	
	QDate hoy = QDate::currentDate();
	ui.dateEdit->setDate(hoy);
	ui.dateEdit_2->setDate(hoy);
}

BuscarPresupuestoDialog::~BuscarPresupuestoDialog()
{

}

void BuscarPresupuestoDialog::accept() {
	CriterioBusqueda *cb = new CriterioBusqueda();
	
	if (ui.lineEdit_2->text() != tr(""))
		cb->cliente = new QString(ui.lineEdit_2->text());
	if (ui.lineEdit->text() != tr("")) {
		cb->numero = new int;
		*cb->numero = ui.lineEdit->text().toInt();
	}
	if (ui.checkBoxAl->isChecked())
		cb->fechaFin = new QDate(ui.dateEdit_2->date());
	if (ui.checkBoxDel->isChecked())
		cb->fechaInicio = new QDate(ui.dateEdit->date());
		
	ListarPresupuestos *lf = new ListarPresupuestos(capaNegocio, padre , cb);
	padre->addWindow(lf);
	lf->show();
	
	this->close();
}
void BuscarPresupuestoDialog::resizeEvent(QResizeEvent *event) {
	setFixedSize(event->size());
}
