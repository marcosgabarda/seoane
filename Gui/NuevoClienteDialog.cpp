#include "NuevoClienteDialog.h"
#include "../Negocio/CapaNegocio.h"
#include "../Negocio/Cliente.h"
#include <QtGui>
#include <string>

NuevoClienteDialog::NuevoClienteDialog(CapaNegocio * const cn, QWidget *parent, Cliente *c)
    : QDialog(parent)
{
	padre = (ListarClientes *)parent;
	capaNegocio = cn;
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/NCliente.PNG")));
	ui.setupUi(this);
	connect(ui.guardarButton, SIGNAL(clicked()), this, SLOT(guardar()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(nuevoTelefono()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(borrarTelefono()));
	cliente = c;
	
	int cod = capaNegocio->getUltimoCodigoCliente();
	ui.lineEdit_4->setText(QString::number(cod));
	
	if (cliente) {
		ui.lineEdit_4->setText(tr("%1").arg(c->getcodigo()));
		ui.lineEdit_5->setText(c->getnif().c_str());
		ui.lineEdit->setText(c->getnombre().c_str());
		ui.lineEdit_2->setText(c->getapellidos().c_str());
		ui.lineEdit_3->setText(c->getdireccion().c_str());
		ui.lineEdit_6->setText(c->getpoblacion().c_str());
		setWindowTitle(tr("Editar Cliente"));
		list<int> lista_telefonos = c->gettelefonos();
		list<int>::iterator it;
		int row;
		for (it = lista_telefonos.begin(), row = 0; it != lista_telefonos.end(); it++, row++) {
			addRow();
			ui.tabla->item(row, 0)->setText(tr("%1").arg(*it));
		}
	} else {
		//addRow();
	}
	
}

NuevoClienteDialog::~NuevoClienteDialog()
{

}
bool NuevoClienteDialog::comprobarDatos(){
	bool estado=true;
	if(ui.lineEdit->text()==""){
		QMessageBox::information(this, tr("Atención"),
			     tr("El campo nombre es necesario"));
		estado=false;
	}
	if(ui.lineEdit_2->text()==""){
		QMessageBox::information(this, tr("Atención"),
			 tr("El campo apellido es necesario"));
		estado=false;
	}
	/*if(ui.lineEdit_5->text()==""){
		QMessageBox::information(this, tr("Atención"),
			 tr("El campo NIF es necesario"));
		estado=false;
	}*/
	if (!cliente && ui.lineEdit_4->text() != "" && capaNegocio->getClienteCodigo(ui.lineEdit_4->text().toInt()) != 0 ) {
		QMessageBox::information(this, tr("Atención"),
						tr("Código repetido."));
		estado=false;
	}
	bool ok;
	ui.lineEdit_4->text().toInt(&ok);
	if(!ok){
		QMessageBox::information(this, tr("Atención"),
			tr("El campo codigo ha de ser numerico"));
		estado=false;
	}
	int rows = ui.tabla->rowCount();
	for (int i = 0; i < rows; i++) {
		ui.tabla->item(i,0)->text().toInt(&ok);
		if(!ok){
			QMessageBox::information(this, tr("Atención"),
				tr("Hay un teléfono demasiado largo."));
			estado=false;
		}		
	}
	return estado;
}
void NuevoClienteDialog::guardar() {
	if(!cliente && comprobarDatos()){
		Cliente c;
		c.setnombre(ui.lineEdit->text().toStdString());
		c.setapellidos(ui.lineEdit_2->text().toStdString());
		c.setcodigo(ui.lineEdit_4->text().toInt());
		c.setnif(ui.lineEdit_5->text().toStdString());
		c.setdireccion(ui.lineEdit_3->text().toStdString());
		c.setpoblacion(ui.lineEdit_6->text().toStdString());
		
		list<int> lista_telefonos;
 		for (int i = 0; i < ui.tabla->rowCount(); i++) {
			lista_telefonos.push_back(ui.tabla->item(i,0)->text().toInt());
		}
		c.settelefonos(lista_telefonos);
		
		if (capaNegocio->nuevoCliente(&c)) {
			//QMessageBox::information(this, tr("Atencion"),
		      //       tr("Cliente guardado."));
			this->close();
		} else {
			QMessageBox::warning(this, tr("Error"),
		             tr("Error al guardar."));
		}
	} else if (cliente && comprobarDatos()) {
		Cliente c;
		c = *cliente;
		c.setnombre(ui.lineEdit->text().toStdString());
		c.setapellidos(ui.lineEdit_2->text().toStdString());
		c.setcodigo(ui.lineEdit_4->text().toInt());
		c.setnif(ui.lineEdit_5->text().toStdString());
		c.setdireccion(ui.lineEdit_3->text().toStdString());
		c.setpoblacion(ui.lineEdit_6->text().toStdString());
		
		list<int> lista_telefonos;
		for (int i = 0; i < ui.tabla->rowCount(); i++) {
			lista_telefonos.push_back(ui.tabla->item(i,0)->text().toInt());
		}
		c.settelefonos(lista_telefonos);
				
		if (capaNegocio->modificarCliente(&c)) {
			//QMessageBox::information(this, tr("Atencion"),
				//	tr("Cliente editado."));
			//padre->actualizar();
			this->close();
		} else {	
			QMessageBox::warning(this, tr("Error"),
					tr("Error al editar."));
		}
	}
}

void NuevoClienteDialog::addRow(){
	int row = ui.tabla->rowCount();
	ui.tabla->insertRow(row);
	
	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tabla->setItem(row, 0, item0);
		
}

void NuevoClienteDialog::nuevoTelefono () {
	int row = ui.tabla->currentRow();
	if (row == -1) {
		addRow();
		ui.tabla->setCurrentCell(0,0);
	} else if (ui.tabla->item(row,0)->text() != "") {
		addRow();
		ui.tabla->setCurrentCell(row + 1,0);
	}
}

void NuevoClienteDialog::borrarTelefono() {
	int row = ui.tabla->currentRow();
	if (row == -1)
		QMessageBox::warning(this, "Aviso", "No se ha seleccionado ningun telefono.");
	else 
		ui.tabla->removeRow(row);	
}

void NuevoClienteDialog::resizeEvent(QResizeEvent *event) {
	ui.gridLayout->setGeometry(QRect(10, 0, event->size().width() - 40, event->size().height()));
}

void NuevoClienteDialog::keyPressEvent(QKeyEvent* event) {
	if ((event->key() == Qt::Key_Down) && ui.tabla->item(ui.tabla->currentRow(),0)->text() != "") {
		addRow();
		ui.tabla->setCurrentCell(ui.tabla->rowCount() - 1,0);
	}
}

