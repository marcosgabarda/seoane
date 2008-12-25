#include "ListarClientes.h"
#include <list>
#include "../Negocio/Cliente.h"
#include "../Negocio/CapaNegocio.h"
#include "NuevoClienteDialog.h"
#include <QtGui>
#include <QString>
#include <iostream>
#include <QMutex>
using namespace std;

ListarClientes::ListarClientes(CapaNegocio * const  cn, QWidget *parent, CriterioBusqueda* cb)
    : QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Listado de Clientes"));
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/LCliente.PNG")));
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	ui.pushButton_3->setText(tr("Mostrar"));
	ui.pushButton_2->setText(tr("Borrar"));
	ui.pushButton->setText(tr("Cancelar"));
	
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(mostrar()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(borrar()));
	connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(mostrar()));
	
	padre = (QWorkspace *) parent;
	
	capaNegocio = cn;
	
	list<Cliente> lista_aux = capaNegocio->getClientes();
	this->cb = cb;
	
	if (cb != 0) {
		if (cb->telefono) {
			list<pair<int, int> > l = capaNegocio->getListaTelefonos();
			cout << "Numero de telefonos: " << l.size() << endl;
			list<Cliente> lc;
			list<pair<int, int> >::iterator it;
			for (it = l.begin(); it != l.end();) {
				if (it->first != *cb->telefono) {
					it = l.erase(it);
				} else {
					it++;
				}
			}
			for (it = l.begin(); it != l.end();it++) {
				Cliente *c = capaNegocio->getClienteId(it->second);
				lc.push_back(*c);
			}
			lista_aux = lc;
		}
		if (cb->nombreCliente) {
			QRegExp rx((tr("*") + *(cb->nombreCliente)) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				QString nombre(((it->getnombre() + " ") + it->getapellidos()).c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
		if (cb->codigoCliente){
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				if (it->getcodigo() != *cb->codigoCliente) {
					it = lista_aux.erase(it);
				} else {
					 it++;
				}
			}
		}
		if (cb->direccionCliente) {
			QRegExp rx((tr("*") + *cb->direccionCliente) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QString nombre(it->getdireccion().c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}	
		}		
	}
	
	lista = lista_aux;
	
	int n_elem = lista.size();
	cout << "[Debug]Numero de clientes: " << n_elem << endl;  
	list<Cliente>::iterator i;
	i = lista.begin();
	for (int row = 0; row  < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getnombre()));
		ui.tableWidget->item(row, 2)->setText(QString::fromStdString(i->getapellidos()));
		ui.tableWidget->item(row, 3)->setText(QString::fromStdString(i->getnif()));
		i++;
	}
}

ListarClientes::~ListarClientes()
{

}

void ListarClientes::addRow(){
	int row = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(row);
	
	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 0, item0);
	
	QTableWidgetItem *item1 = new QTableWidgetItem;
	item1->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 1, item1);
	
	QTableWidgetItem *item2 = new QTableWidgetItem;
	item2->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 2, item2);
	
	QTableWidgetItem *item3 = new QTableWidgetItem;
	item3->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 3, item3);
		
}

void ListarClientes::resizeEvent(QResizeEvent *event) {
	ui.gridLayout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}
void ListarClientes::mostrar() {
	int row = ui.tableWidget->currentRow();
	int cod;
	
	if (row == -1) {
		QString mes = tr("No se selecciono ninguna fila.");
		QMessageBox::information(this, tr("Atencion"),mes);

	} else {
		cod = ui.tableWidget->item(row, 0)->text().toInt();
		QString mes = tr("Ahora se editara el cliente de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
		QDialog *edit = new NuevoClienteDialog(capaNegocio, this, capaNegocio->getClienteCodigo(cod));
		padre->addWindow(edit);
		edit->show();
	}
}
void ListarClientes::actualizar() {

	list<Cliente> lista_aux = capaNegocio->getClientes();
	if (cb != 0) {
		if (cb->telefono) {
			list<pair<int, int> > l = capaNegocio->getListaTelefonos();
			cout << "Numero de telefonos: " << l.size() << endl;
			list<Cliente> lc;
			list<pair<int, int> >::iterator it;
			for (it = l.begin(); it != l.end();) {
				if (it->first != *cb->telefono) {
					it = l.erase(it);
				} else {
					it++;
				}
			}
			for (it = l.begin(); it != l.end();it++) {
				Cliente *c = capaNegocio->getClienteId(it->second);
				lc.push_back(*c);
			}
			lista_aux = lc;
		}
		if (cb->nombreCliente) {
			QRegExp rx((tr("*") + *(cb->nombreCliente)) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				QString nombre(((it->getnombre() + " ") + it->getapellidos()).c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
		if (cb->codigoCliente){
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				if (it->getcodigo() != *cb->codigoCliente) {
					it = lista_aux.erase(it);
				} else {
					 it++;
				}
			}
		}
		if (cb->direccionCliente) {
			QRegExp rx((tr("*") + *cb->direccionCliente) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Cliente>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QString nombre(it->getdireccion().c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}	
		}		
	}	
	lista = lista_aux;

	int n_elem = lista.size();
	int n_row = ui.tableWidget->rowCount();
	cout << "[Debug]Numero de clientes: " << n_elem << endl;  
	list<Cliente>::iterator i;
	i = lista.begin();
	for (int row = 0; row  < n_row; row++) {
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getnombre()));
		ui.tableWidget->item(row, 2)->setText(QString::fromStdString(i->getapellidos()));
		ui.tableWidget->item(row, 3)->setText(QString::fromStdString(i->getnif()));
		i++;
	}
	for (int row = n_row; row < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getnombre()));
		ui.tableWidget->item(row, 2)->setText(QString::fromStdString(i->getapellidos()));
		ui.tableWidget->item(row, 3)->setText(QString::fromStdString(i->getnif()));
		i++;
	}
	

}
void ListarClientes::borrar() {
	int row = ui.tableWidget->currentRow();
	int cod = ui.tableWidget->item(row, 0)->text().toInt();
	if (QMessageBox::question(this, tr("Borrar Cliente"), tr("Seguro que desea borrar el cliente de codigo %1?").arg(cod),tr("No"),tr("Si")) == 1) {
		QString mes = tr("Ahora se borrara el articulo de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
		if (capaNegocio->borrarCliente(capaNegocio->getClienteCodigo(cod))) {
			//QMessageBox::information(this, tr("Atencion"), tr("Borrado correcto."));
			ui.tableWidget->removeRow(row);
		} else {
			QMessageBox::warning(this, tr("Atencion"), tr("Error al borrar."));
		}
	} else {
		//QString mes = tr("No se borrara el cliente de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
	}
}

