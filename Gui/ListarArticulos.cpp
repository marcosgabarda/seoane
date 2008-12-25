#include "ListarArticulos.h"
#include "NuevoArticuloDialog.h"
#include <QtGui>
#include <QString>
#include <list>
#include "../Negocio/Articulo.h"
#include "../Negocio/CapaNegocio.h"
#include <iostream>
using namespace std;

ListarArticulos::ListarArticulos(CapaNegocio * const cn, QWidget *parent, CriterioBusqueda *cb)
    : QWidget(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("Listado de Articulos"));
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/LArticulo.PNG")));
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.pushButton_3->setText(tr("Mostrar"));
	
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(mostrar()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(borrar()));
	connect(ui.tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(mostrar()));
	
	padre = (QWorkspace *) parent;
	
	capaNegocio = cn;
	list<Articulo> lista_aux = capaNegocio->getArticulos();
	this->cb = cb;
	
	if (cb != 0) {
		if (cb->codigoArticulo) {
			list<Articulo>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				if (it->getcodigo() != *cb->codigoArticulo) {
					it = lista_aux.erase(it);
				}else {
					it++;
				}
			}
		}
		if (cb->descripcionArticulo) {
			QRegExp rx((tr("*") + *cb->descripcionArticulo) + "*");
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			rx.setPatternSyntax(QRegExp::Wildcard);
			list<Articulo>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				QString nombre(it->getdescripcion().c_str());
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
	cout << "[Debug]Numero de articulos: " << n_elem << endl;  
	list<Articulo>::iterator i;
	i = lista.begin();
	for (int row = 0; row  < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getdescripcion()));
		ui.tableWidget->item(row, 2)->setText(QString::number(i->getpvp()));
		i++;
	}
	
	
}

ListarArticulos::~ListarArticulos()
{

}
void ListarArticulos::resizeEvent(QResizeEvent *event) {
	ui.gridLayout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}

void ListarArticulos::addRow(){
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
	
}
void ListarArticulos::mostrar() {
	int row = ui.tableWidget->currentRow();
	int cod;
	
	if (row == -1) {
		QString mes = tr("No se selecciono ninguna fila.");
		QMessageBox::information(this, tr("Atencion"),mes);

	} else {
		cod = ui.tableWidget->item(row, 0)->text().toInt();
		QString mes = tr("Ahora se editara el articulo de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
		QDialog *edit = new NuevoArticuloDialog(capaNegocio,this,capaNegocio->getArticuloCodigo(cod));
		padre->addWindow(edit);
		edit->show();
	}
}

void ListarArticulos::actualizar() {
	list<Articulo> lista_aux = capaNegocio->getArticulos();
	if (cb != 0) {
		if (cb->codigoArticulo) {
			list<Articulo>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				if (it->getcodigo() != *cb->codigoArticulo) {
					it = lista_aux.erase(it);
				}else {
					it++;
				}
			}
		}
		if (cb->descripcionArticulo) {
			QRegExp rx((tr("*") + *cb->descripcionArticulo) + "*");
			rx.setCaseSensitivity(Qt::CaseInsensitive);
			rx.setPatternSyntax(QRegExp::Wildcard);
			list<Articulo>::iterator it;
			for (it = lista_aux.begin(); it != lista_aux.end(); ) {
				QString nombre(it->getdescripcion().c_str());
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
	cout << "[Debug]Numero de articulos: " << n_elem << endl;  
	list<Articulo>::iterator i;
	i = lista.begin();
	for (int row = 0; row  < n_row; row++) {
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getdescripcion()));
		ui.tableWidget->item(row, 2)->setText(QString::number(i->getpvp()));
		i++;
	}
	for (int row = n_row; row < n_elem; row++) {
		addRow();
		ui.tableWidget->item(row, 0)->setText(QString::number(i->getcodigo()));
		ui.tableWidget->item(row, 1)->setText(QString::fromStdString(i->getdescripcion()));
		ui.tableWidget->item(row, 2)->setText(QString::number(i->getpvp()));
		i++;
	}	
}
void ListarArticulos::borrar() {
	int row = ui.tableWidget->currentRow();
	int cod = ui.tableWidget->item(row, 0)->text().toInt();
	if (QMessageBox::question(this, tr("Borrar Articulo"), tr("Seguro que desea borrar el articulo de codigo %1?").arg(cod),tr("No"),tr("Si")) == 1) {
		QString mes = tr("Ahora se borrara el articulo de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
		if (capaNegocio->borrarArticulo(capaNegocio->getArticuloCodigo(cod))) {
			//QMessageBox::information(this, tr("Atencion"), tr("Borrado correcto."));
			ui.tableWidget->removeRow(row);
		} else {
			QMessageBox::warning(this, tr("Atencion"), tr("Error al borrar."));
		}
	} else {
		//QString mes = tr("No se borrara el articulo de la fila: %1.").arg(row);
		//QMessageBox::information(this, tr("Atencion"), mes);
	}
}
