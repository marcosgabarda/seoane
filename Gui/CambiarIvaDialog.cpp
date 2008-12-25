#include "CambiarIvaDialog.h"
#include "../Negocio/CapaNegocio.h"
#include <QtGui>

CambiarIvaDialog::CambiarIvaDialog(CapaNegocio * const cn, QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Cambiar IVA"));
	capaNegocio = cn;
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/Configuracion.PNG")));
	connect(ui.pushButton, SIGNAL(clicked()), this , SLOT(cambiarValor()));
	ui.spinBox->setValue(capaNegocio->obtenerIva());
}

CambiarIvaDialog::~CambiarIvaDialog()
{

}

void CambiarIvaDialog::cambiarValor() {
	int nuevo_valor = ui.spinBox->value();
	if (!capaNegocio->cambiarIva(nuevo_valor))
		QMessageBox::critical(this, tr("Error"),
			tr("El IVA no ha podido ser cambiado."));
}
