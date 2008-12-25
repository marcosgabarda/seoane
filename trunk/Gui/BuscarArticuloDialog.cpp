#include "BuscarArticuloDialog.h"
#include "ListarArticulos.h"

BuscarArticuloDialog::BuscarArticuloDialog(CapaNegocio *cn, QWidget *parent)
    : QDialog(parent)
{
	padre = (QWorkspace *)parent;
	ui.setupUi(this);
	capaNegocio = cn;
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/BArticulo.PNG")));
}

BuscarArticuloDialog::~BuscarArticuloDialog()
{

}

void BuscarArticuloDialog::accept() {
	CriterioBusqueda *cb = new CriterioBusqueda();
	
	if (ui.lineEdit->text() != tr("")) {
		cb->codigoArticulo = new int;
		*cb->codigoArticulo = ui.lineEdit->text().toInt();
	}
	if (ui.lineEdit_2->text() != tr(""))
		cb->descripcionArticulo = new QString(ui.lineEdit_2->text());
		
	ListarArticulos *lf = new ListarArticulos(capaNegocio, padre , cb);
	padre->addWindow(lf);
	lf->show();
	
	this->close();
}


void BuscarArticuloDialog::resizeEvent(QResizeEvent *event) {
	setFixedSize(event->size());
}

