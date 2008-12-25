#include "ListarPresupuestos.h"
#include "../Negocio/CapaNegocio.h"
#include <QtGui>
#include <QString>
#include "NuevoPresupuestoDialog.h"
#include "../Negocio/Presupuesto.h"
#include "../Datos/CriterioBusqueda.h"

ListarPresupuestos::ListarPresupuestos(CapaNegocio * const cn, QWidget *parent, CriterioBusqueda *cb)
    : QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Listar Presupuestos"));
	
	padre = (QWorkspace *) parent;
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/LPresupuesto.PNG")));
	capaNegocio = cn;
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(mostrar()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(borrar()));
	connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(mostrar()));

	list<Presupuesto> lista_aux = capaNegocio->getPresupuestos();	
	this->cb = cb;
	if (cb != 0) {	
		if (cb->numero) {
			list<Presupuesto>::iterator it;
			
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				if (it->getn_factura() != *cb->numero) {
					it = lista_aux.erase(it);
				}else {
					it++;
				}
			}
		}
		if (cb->cliente) {
			QRegExp rx((tr("*") + *cb->cliente) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				Cliente c = *it->getcliente();
				QString nombre(((c.getnombre() + " ") + c.getapellidos()).c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}		
		if (cb->fechaFin  && cb->fechaInicio) {
			list<Presupuesto>::iterator it;			
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				if (!(f <= *(cb->fechaFin) && f >= *(cb->fechaInicio))) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}			
		} else if (cb->fechaFin) {

			list<Presupuesto>::iterator it;					
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				if (!(f <= *(cb->fechaFin))) {
					it = lista_aux.erase(it);
				}else {
					it++;
				}
			}
		} else if (cb->fechaInicio) {
			list<Presupuesto>::iterator it;					
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				cout << f.toString("dd/MM/yyyy").toStdString() << endl;
				if (!(f >= *(cb->fechaInicio))) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
	} 
	lista = lista_aux;
	
	int n_elem = lista.size();
	cout << "[Debug]Numero de presupuestos: " << n_elem << endl;  
	list<Presupuesto>::iterator i;
	i = lista.begin();
	for (int row = 0; row  < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getn_factura()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getfecha()));
		if (i->getcliente()) {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString(i->getcliente()->getnombre()));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString(i->getcliente()->getapellidos()));
		} else {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString("-"));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString("-"));
		}
		ui.tableWidget->item(row, 4)->setText(QString::fromStdString(i->getaparato()));
		ui.tableWidget->item(row, 5)->setText(QString::fromStdString(i->getmarca()));
		i++;
	}
	connect(ui.pushButton_2, SIGNAL(clicked), this, SLOT(mostrar()));
}

ListarPresupuestos::~ListarPresupuestos()
{

}

void ListarPresupuestos::actualizar() {

	list<Presupuesto> lista_aux = capaNegocio->getPresupuestos();
	if (cb != 0) {
		if (cb->numero) {
			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				if (it->getn_factura() != *cb->numero) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
		if (cb->cliente) {
			QRegExp rx((tr("*") + *cb->cliente) + "*");
			rx.setPatternSyntax(QRegExp::Wildcard);
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				Cliente c = *it->getcliente();
				QString nombre(((c.getnombre() + " ") + c.getapellidos()).c_str());
				if (!rx.exactMatch(nombre)) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
		if (cb->fechaFin && cb->fechaInicio) {
			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				if (!(f <= *(cb->fechaFin) && f >= *(cb->fechaInicio))) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		} else if (cb->fechaFin) {

			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				if (!(f <= *(cb->fechaFin))) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		} else if (cb->fechaInicio) {
			list<Presupuesto>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end();) {
				QDate f = QDate::fromString(it->getfecha().c_str(), "dd/MM/yyyy");
				cout << f.toString("dd/MM/yyyy").toStdString() << endl;
				if (!(f >= *(cb->fechaInicio))) {
					it = lista_aux.erase(it);
				} else {
					it++;
				}
			}
		}
	}
	lista = lista_aux;
	list<Presupuesto>::iterator it;
	it = lista.begin();
	int n_elem = lista.size();
	int n_row = ui.tableWidget->rowCount();
	for (int row = 0; row < n_row; row++, it++) {
		ui.tableWidget->item(row, 0)->setText(QString::number(it->getn_factura()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(it->getfecha()));
		if (it->getcliente()) {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString(it->getcliente()->getnombre()));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString(it->getcliente()->getapellidos()));
		} else {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString("-"));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString("-"));
		}
		ui.tableWidget->item(row, 4)->setText(QString::fromStdString(it->getaparato()));
		ui.tableWidget->item(row, 5)->setText(QString::fromStdString(it->getmarca()));
	}
	for (int row = n_row; row < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(it->getn_factura()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(it->getfecha()));
		if (it->getcliente()) {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString(it->getcliente()->getnombre()));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString(it->getcliente()->getapellidos()));
		} else {
			ui.tableWidget->item(row, 2)->setText(QString::fromStdString("-"));
			ui.tableWidget->item(row, 3)->setText(QString::fromStdString("-"));
		}
		ui.tableWidget->item(row, 4)->setText(QString::fromStdString(it->getaparato()));
		ui.tableWidget->item(row, 5)->setText(QString::fromStdString(it->getmarca()));
		it++;
	}
	
}

void ListarPresupuestos::addRow(){
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
	
	QTableWidgetItem *item4 = new QTableWidgetItem;
	item4->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 4, item4);
		
	QTableWidgetItem *item5 = new QTableWidgetItem;
	item5->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tableWidget->setItem(row, 5, item5);
}

void ListarPresupuestos::resizeEvent(QResizeEvent *event) {
	ui.gridLayout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}
void ListarPresupuestos::mostrar() {
	int row = ui.tableWidget->currentRow();
	int cod;
	if (row == -1) {
		QString mes = tr("No se selecciono ninguna fila.");
		QMessageBox::warning(this, tr("Atencion"),mes);

	} else {
		cod = ui.tableWidget->item(row, 0)->text().toInt();
		NuevoPresupuestoDialog *nfd = new NuevoPresupuestoDialog(capaNegocio, this, capaNegocio->getPresupuestoNumero(cod));
		padre->addWindow(nfd);
		nfd->show();
	}
}
void ListarPresupuestos::borrar() {
	int row = ui.tableWidget->currentRow();
	int cod = ui.tableWidget->item(row, 0)->text().toInt();
	if (QMessageBox::question(this, tr("Borrar Presupuesto"), tr("Seguro que desea borrar el presupuesto de nuemero %1?").arg(cod),tr("No"),tr("Si")) == 1) {
		QString mes = tr("Ahora se borrara el presupuesto de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
		if (capaNegocio->borrarPresupuesto(capaNegocio->getPresupuestoNumero(cod))) {
			//QMessageBox::information(this, tr("Atencion"), tr("Borrado correcto."));
			ui.tableWidget->removeRow(row);
		} else {
			QMessageBox::warning(this, tr("Atencion"), tr("Error al borrar."));
		}
	} else {
		//QString mes = tr("No se borrara el presupuesto de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
	}
}
