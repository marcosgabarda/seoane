#include "NuevoArticuloDialog.h"
#include "../Negocio/CapaNegocio.h"
#include "../Negocio/Articulo.h"

#include <QtGui>

NuevoArticuloDialog::NuevoArticuloDialog(CapaNegocio * const cn,QWidget *parent, Articulo *a)
    : QDialog(parent)
{
	padre = (ListarArticulos*) parent;
	capaNegocio = cn;
	ui.setupUi(this);
	setWindowTitle(tr("Nuevo Articulo"));
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/NArticulo.PNG")));
	connect(ui.guardarButton, SIGNAL(clicked()), this, SLOT(guardar()));
	articulo = a;
	if (articulo) {
		ui.lineEdit->setText(tr("%1").arg(a->getcodigo()));
		ui.lineEdit_2->setText(a->getdescripcion().c_str());
		ui.lineEdit_3->setText(a->getcaja().c_str());
		ui.lineEdit_8->setText(tr("%1").arg(a->getdescuento()));
		ui.lineEdit_4->setText(tr("%1").arg(a->getexistencias()));
		ui.lineEdit_5->setText(tr("%1").arg(a->getexistencias_minimas()));
		ui.lineEdit_6->setText(tr("%1").arg(a->getpvp()));
		ui.lineEdit_7->setText(tr("%1").arg(a->getprecio_coste()));
		setWindowTitle(tr("Editar Articulo"));
	}
}

NuevoArticuloDialog::~NuevoArticuloDialog()
{

}

bool NuevoArticuloDialog::comprobarDatos(){
	//comprobar
	bool estado=true;
	if(ui.lineEdit->text()==""){
		QMessageBox::information(this, tr("Atencion"),
			     tr("El campo codigo es necesario"));
		estado=false;
	}
		
	bool ok;
	ui.lineEdit->text().toInt(&ok);
	if(!ok && ui.lineEdit->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
			tr("El campo codigo ha de ser numerico"));
		estado=false;
	}	

	ui.lineEdit_8->text().toInt(&ok);
	if(!ok && ui.lineEdit_8->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo descuento ha de ser numerico"));
		estado=false;
	}	
	if (!articulo && ui.lineEdit->text() != "" && capaNegocio->getArticuloCodigo(ui.lineEdit->text().toInt()) != 0 ) {
		QMessageBox::information(this, tr("Atención"),
						tr("Código repetido."));
		estado=false;
	}
	ui.lineEdit_4->text().toInt(&ok);
	if(!ok && ui.lineEdit_4->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo existencias ha de ser numerico"));
		estado=false;
	}	
	
	ui.lineEdit_5->text().toInt(&ok);
	if(!ok && ui.lineEdit_5->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo existencias minimas ha de ser numerico"));
		estado=false;
		}	
	
	ui.lineEdit_6->text().toDouble(&ok);
	if(!ok && ui.lineEdit_6->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo PVP ha de ser numerico"));
		estado=false;
		}	
	
	ui.lineEdit_7->text().toDouble(&ok);
	if(!ok && ui.lineEdit_7->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo precio de coste ha de ser numerico"));
	estado=false;
		}	
	
	return estado;
}
void NuevoArticuloDialog::guardar() {
	if(!articulo && comprobarDatos()){
			Articulo a;
			a.setcodigo(ui.lineEdit->text().toInt());
			a.setdescripcion(ui.lineEdit_2->text().toStdString());
			a.setcaja(ui.lineEdit_3->text().toStdString());
			a.setdescuento(ui.lineEdit_8->text().toInt());
			a.setexistencias(ui.lineEdit_4->text().toInt());
			a.setexistencias_minimas(ui.lineEdit_5->text().toInt());
			a.setpvp(ui.lineEdit_6->text().toDouble());
			a.setprecio_coste(ui.lineEdit_7->text().toDouble());
									
			if (capaNegocio->nuevoArticulo(&a)) {
				QMessageBox::information(this, tr("Atencion"),
			             tr("Articulo guardado."));
				this->close();
			} else {
				QMessageBox::warning(this, tr("Error"),
			             tr("Error al guardar."));
			}
	} else if (articulo && comprobarDatos()) {
		Articulo a;
		a = *articulo;
		a.setcodigo(ui.lineEdit->text().toInt());
		a.setdescripcion(ui.lineEdit_2->text().toStdString());
		a.setcaja(ui.lineEdit_3->text().toStdString());
		a.setdescuento(ui.lineEdit_8->text().toInt());
		a.setexistencias(ui.lineEdit_4->text().toInt());
		a.setexistencias_minimas(ui.lineEdit_5->text().toInt());
		a.setpvp(ui.lineEdit_6->text().toDouble());
		a.setprecio_coste(ui.lineEdit_7->text().toDouble());
											
		if (capaNegocio->modificarArticulo(&a)) {
			//QMessageBox::information(this, tr("Atencion"),
				//	tr("Articulo editado."));
			padre->actualizar();
			this->close();
		} else {
			QMessageBox::warning(this, tr("Error"),
					tr("Error al editar."));
		}
	}
}

