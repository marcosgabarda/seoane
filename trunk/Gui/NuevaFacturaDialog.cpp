#include "NuevaFacturaDialog.h"
#include "NuevoClienteDialog.h"
#include <QRegExp>
#include <list>
#include <iostream>
#include <QtGui>
#include <QThread>
#include <QMutex>
#include "PrintWindow.h"
#include "../Negocio/Articulo.h"

using namespace std;

QMutex mutex;

 void ActualizadorThread::setPadre(NuevaFacturaDialog* parent) {
	 nfd = parent;
 }
 void ActualizadorThread::run() {
	 while (true) {
		 usleep(10000);
		 nfd->actualizaPrecios();
	 }
 } 

NuevaFacturaDialog::NuevaFacturaDialog(CapaNegocio * const cn, QWidget *parent, Factura *f, bool dePresupuesto)
    : QDialog(parent)
{
	this->dePresupuesto = dePresupuesto;
	ui.setupUi(this);
	capaNegocio = cn;
	lClientes = capaNegocio->getClientes();
	lArticulos = capaNegocio->getArticulos();
	setWindowIcon(QIcon(QString::fromUtf8("Gui/images/NFactura.PNG")));
	
	cliente = 0;
	padre = 0;
	nuevaFactura = new Factura();
	
	//ui.lineEdit_7->installEventFilter(this);
	//ui.lineEdit_8->installEventFilter(this);
	//ui.lineEdit_9->installEventFilter(this);
	
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	ui.lineEdit_11->setText(tr("%1").arg(capaNegocio->obtenerIva()));
	QDate hoy = QDate::currentDate();
	ui.dateEdit->setDate(hoy);
	ui.dateEdit_2->setDate(hoy);
	ui.lineEdit_10->setEnabled(false);
	ui.lineEdit_12->setEnabled(false);
	int num = capaNegocio->getUltimoCodigoFactura();
	if (num < 100000) {
		ui.lineEdit_4->setText(tr("0%1").arg(num));
	} else {
		ui.lineEdit_4->setText(tr("%1").arg(num));
	}
	
	int cod = capaNegocio->getUltimoCodigoCliente();
	ui.codigoEdit->setText(QString::number(cod));
	
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(anyadirLineaArticulo()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(borrarArticulo()));
	connect(ui.pushButton_7, SIGNAL(clicked()), this, SLOT(limpiar()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(nuevoTelefono()));
	connect(ui.pushButton_8, SIGNAL(clicked()), this, SLOT(borrarTelefono()));
	connect(ui.checkBox_2, SIGNAL(clicked()), this, SLOT(cambiarEstadoDomicilio()));
	connect(ui.checkBox_3, SIGNAL(clicked()), this, SLOT(cambiarEstadoTaller()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(imprimir()));
	
	if (f != 0) {
		*nuevaFactura = *f;
		padre = (ListarFacturas *)parent;
		setWindowTitle(tr("Editar Factura"));
		cliente = new Cliente();		
		if (f->getcliente() != 0) {
			*cliente = *(f->getcliente());
			ui.nombreEdit->setText(cliente->getnombre().c_str());
			ui.nombreEdit->setEnabled(false);
			ui.lineEdit_13->setText(cliente->getapellidos().c_str());
			ui.lineEdit_13->setEnabled(false);
			ui.codigoEdit->setText(tr("%1").arg(cliente->getcodigo()));
			ui.codigoEdit->setEnabled(false);
			QString direccion;
			direccion.append(cliente->getdireccion().c_str());
			QTextDocument *direccionCompleta = new QTextDocument(direccion);
			ui.direccionEdit->setDocument(direccionCompleta);
			ui.direccionEdit->setEnabled(false);
			ui.lineEdit_14->setText(cliente->getpoblacion().c_str());
			ui.lineEdit_14->setEnabled(false);
			ui.nifEdit->setText(cliente->getnif().c_str());
			ui.nifEdit->setEnabled(false);
			ui.pushButton_6->setEnabled(false);
			ui.pushButton_8->setEnabled(false);
			list<int> lista_telefonos = cliente->gettelefonos();
			list<int>::iterator it2;
			int row;
			for (it2 = lista_telefonos.begin(), row = 0; it2 != lista_telefonos.end(); it2++, row++) {
				addRowTelefono();
				ui.tabla->item(row, 0)->setText(tr("%1").arg(*it2));
			}
			ui.tabla->setEnabled(false);
		} else {
			ui.nombreEdit->setEnabled(false);
			ui.lineEdit_13->setEnabled(false);
			ui.codigoEdit->setEnabled(false);
			ui.pushButton_6->setEnabled(false);
			ui.direccionEdit->setEnabled(false);
			ui.lineEdit_14->setEnabled(false);
			ui.nifEdit->setEnabled(false);
			ui.tabla->setEnabled(false);
		}
		if (f->getn_factura() < 100000) {
			ui.lineEdit_4->setText(tr("0%1").arg(f->getn_factura()));
		} else {
			ui.lineEdit_4->setText(tr("%1").arg(f->getn_factura()));
		}
		if (f->getfecha()!= "") {
			ui.checkBox->setChecked(true);
			ui.dateEdit->setEnabled(true);
			QDate fecha = QDate::fromString(f->getfecha().c_str(), "dd/MM/yyyy");
			ui.dateEdit->setDate(fecha);
		}
		if (f->getfecha_terminacion()!= "") {
			ui.checkBox_4->setChecked(true);
			ui.dateEdit_2->setEnabled(true);
			QDate fecha = QDate::fromString(f->getfecha_terminacion().c_str(), "dd/MM/yyyy");
			ui.dateEdit_2->setDate(fecha);
		} 
		ui.lineEdit_15->setText(f->getobservaciones().c_str());
		ui.lineEdit->setText(f->getaparato().c_str());
		ui.lineEdit_2->setText(f->getmarca().c_str());
		ui.lineEdit_3->setText(f->getmodelo().c_str());
		
		if (f->getlugar_reparacion() != 0)
			if (*(f->getlugar_reparacion())) {
				ui.checkBox_2->setChecked(true);
				ui.checkBox_3->setChecked(false);
			} else { 
				ui.checkBox_2->setChecked(false);
				ui.checkBox_3->setChecked(true);
			}
		else {
			ui.checkBox_2->setChecked(false);
			ui.checkBox_3->setChecked(false);
		}
		QString averia;
		averia.append(f->getaveria().c_str());
		QTextDocument *averiaC = new QTextDocument(averia);
		ui.textEdit->setDocument(averiaC);
		QString trabajo;
		trabajo.append(f->gettrabajo_realizado().c_str());
		QTextDocument *trabajoC = new QTextDocument(trabajo);
		ui.textEdit_2->setDocument(trabajoC);
		ui.lineEdit_5->setText(f->gettiempo_empleado().c_str());
		ui.lineEdit_6->setText(tr("%1").arg(f->getMateriales()));
		ui.lineEdit_7->setText(tr("%1").arg(f->getprecio_mano_obra()));
		ui.lineEdit_8->setText(tr("%1").arg(f->getprecio_desplazamiento()));
		ui.lineEdit_9->setText(tr("%1").arg(f->getprecio_transporte()));
		ui.lineEdit_10->setText(tr("%1").arg(f->getSubTotal()));
		ui.lineEdit_11->setText(tr("%1").arg(f->getiva()));
		ui.lineEdit_12->setText(tr("%1").arg(f->getTotal()));
		
		list<LineaArticulo> lista = f->getlista_articulos();
		list<LineaArticulo>::iterator it;
		for (it = lista.begin(); it != lista.end(); it++) {
			int row = ui.tableWidget->rowCount();
			int cantidad = it->getcantidad();			
			addRow();	
			ui.tableWidget->item(row, 0)->setText(tr("%1").arg(it->getarticulo().getcodigo()));
			ui.tableWidget->item(row, 1)->setText(it->getarticulo().getdescripcion().c_str());
			ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad));
			ui.tableWidget->item(row, 3)->setText(tr("%1").arg(it->getarticulo().getpvp()));
			ui.tableWidget->item(row, 4)->setText(tr("%1").arg(it->getarticulo().getpvp() * (double)cantidad));
		}
		if (!dePresupuesto) {
			ui.pushButton_7->setText(tr("Modificar"));
			connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(editar()));
		} else {
			connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(guardar()));
		}
	} else {
		connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(guardar()));
	}
	
	// Cosas de hilos
	actualizador = new ActualizadorThread();
	actualizador->setPadre(this);
	actualizador->start();
}

NuevaFacturaDialog::~NuevaFacturaDialog()
{
	actualizador->quit();
}

void NuevaFacturaDialog::buscarCliente() {		
	QString nombreParcial = (ui.nombreEdit->text() + "*" ) + ui.lineEdit_13->text();
	QRegExp rx(nombreParcial + "*");
	rx.setPatternSyntax(QRegExp::Wildcard);
	rx.setCaseSensitivity(Qt::CaseInsensitive);
	
	list<Cliente> lClientesEncontrados;
	list<Cliente>::iterator it;
	
	for (it = lClientes.begin(); it != lClientes.end(); it++) {
		QString nombre(((it->getnombre() + " ") + it->getapellidos()).c_str());
		if (rx.exactMatch(nombre)) {
			lClientesEncontrados.push_back(*it);
		}
	}
	
	if (lClientesEncontrados.size() == 1) {
		
		cliente = new Cliente();		 
		*cliente = lClientesEncontrados.front();
		ui.nombreEdit->setText(cliente->getnombre().c_str());
		ui.lineEdit_13->setText(cliente->getapellidos().c_str());
		ui.codigoEdit->setText(tr("%1").arg(cliente->getcodigo()));
		QString direccion;
		direccion.append(cliente->getdireccion().c_str());
		QTextDocument *direccionCompleta = new QTextDocument(direccion);
		ui.direccionEdit->setDocument(direccionCompleta);
		ui.lineEdit_14->setText(cliente->getpoblacion().c_str());
		ui.nifEdit->setText(cliente->getnif().c_str());
		while (ui.tabla->rowCount() > 0) {
			ui.tabla->removeRow(0);
		}
		list<int> lista_telefonos = cliente->gettelefonos();
		list<int>::iterator it;
		int row;
		for (it = lista_telefonos.begin(), row = 0; it != lista_telefonos.end(); it++, row++) {
			addRowTelefono();
			ui.tabla->item(row, 0)->setText(tr("%1").arg(*it));
		}
		cambiarCliente();	
	} 
	
}

void NuevaFacturaDialog::buscarArticulo() {	
	
	QString nombreParcial = ui.descripcionEdit->text();
	QRegExp rx(nombreParcial + "*");
	rx.setPatternSyntax(QRegExp::Wildcard);
	rx.setCaseSensitivity(Qt::CaseInsensitive);
	
	list<Articulo> lArticulosEncontrados;
	list<Articulo>::iterator it;
	
	if (ui.referenciaEdit->hasFocus()) {
		for (it = lArticulos.begin(); it != lArticulos.end(); it++) {
			if (ui.referenciaEdit->text().toInt() == it->getcodigo()) {
				lArticulosEncontrados.push_back(*it);
			}
		}
	} else {
		for (it = lArticulos.begin(); it != lArticulos.end(); it++) {
			QString nombre((it->getdescripcion()).c_str());
			if (rx.exactMatch(nombre)) {
				lArticulosEncontrados.push_back(*it);
			}
		}
	}
	
	if (lArticulosEncontrados.size() == 1) {
		articuloActual = lArticulosEncontrados.front();
		ui.descripcionEdit->setText(articuloActual.getdescripcion().c_str());
		ui.referenciaEdit->setText(tr("%1").arg(articuloActual.getcodigo()));
		ui.pvpEdit->setText(tr("%1").arg(articuloActual.getpvp() - articuloActual.getpvp()*(articuloActual.getdescuento() / 100.0)));
		ui.cantidadEdit->setValue(1);
	} 
	
}

void NuevaFacturaDialog::addRow(){
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
}

void NuevaFacturaDialog::anyadirLineaArticulo() {
	
	int cantidadPrev = ui.cantidadEdit->value();
	buscarArticulo();
	ui.cantidadEdit->setValue(cantidadPrev);
	
	if (articuloActual.getcodigo() != -1) {
		/**
		 * Caso para un artículo de la base de datos.
		 */
		int row = ui.tableWidget->rowCount();
		int cantidad = ui.cantidadEdit->value();

		list<pair<pair<string, double>, int> >::iterator it;
		for (it = lArticuloFila.begin(); it != lArticuloFila.end(); it++) {
			if (articuloActual.getdescripcion() == it->first.first && articuloActual.getpvp() == it->first.second) {
				break;
			}
		}

		if (it == lArticuloFila.end()) {
			// No encuentra
			addRow();	
			ui.tableWidget->item(row, 0)->setText(ui.referenciaEdit->text());
			ui.tableWidget->item(row, 1)->setText(ui.descripcionEdit->text());
			ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad));
			ui.tableWidget->item(row, 3)->setText(ui.pvpEdit->text());
			ui.tableWidget->item(row, 4)->setText(tr("%1").arg(ui.pvpEdit->text().toDouble() * (double)cantidad));
			pair <string, double> tmp(articuloActual.getdescripcion(), articuloActual.getpvp()); 
			lArticuloFila.push_back(pair<pair<string, double>, int>(tmp, row));
			nuevaFactura->addArticulo(articuloActual, cantidad);
		} else {
			// Encuentra
			row = it->second;
			int cantidad_prev = ui.tableWidget->item(row, 2)->text().toInt();
			nuevaFactura->modificarArticulo(articuloActual, cantidad_prev + cantidad);
			ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad_prev + cantidad));
			ui.tableWidget->item(row, 4)->setText(tr("%1").arg(ui.pvpEdit->text().toDouble() * (double)(cantidad_prev + cantidad)));
			actualizaPrecios();
		}

		actualizaPrecios();	
	} else if (ui.referenciaEdit->text() == "" && ui.pvpEdit->text() != "") {
		/**
		 * Caso para un articulo temporal, que tendrá que guardarse en la base de datos para poder recuperar la factura, 
		 * pero con un código de 0 igual que el resto. Esto supone un problema a la hora de la búsqueda, esto supondrá un 
		 */
		bool ok;
		ui.pvpEdit->text().toDouble(&ok);
		if(!ok){
			QMessageBox::information(this, tr("Atencion"),
					tr("El precio ha de ser numerico"));
		} else {
			int cantidad = ui.cantidadEdit->value();
				
			list<pair<pair<string, double>, int> >::iterator it;
			for (it = lArticuloFila.begin(); it != lArticuloFila.end(); it++) {
				if (ui.descripcionEdit->text().toStdString() == it->first.first && ui.pvpEdit->text().toDouble() == it->first.second) {
					break;
				}
			}
			
			if (it == lArticuloFila.end()) {
				// No encuentra
				// Nuevo artículo
				Articulo *a_tmp = capaNegocio->getArticuloDescripcionPvp(ui.descripcionEdit->text().toStdString(), ui.pvpEdit->text().toDouble());
				
				Articulo a;
				a.setcodigo(0); //Código generico de artículos temporales.
				a.setdescripcion(ui.descripcionEdit->text().toStdString());
				a.setpvp(ui.pvpEdit->text().toDouble());
				a.sethistorico(true);
				
				if (a_tmp != 0) {
					int row = ui.tableWidget->rowCount();
					addRow();	
					ui.tableWidget->item(row, 0)->setText("0");
					ui.tableWidget->item(row, 1)->setText(ui.descripcionEdit->text());
					ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad));
					ui.tableWidget->item(row, 3)->setText(ui.pvpEdit->text());
					ui.tableWidget->item(row, 4)->setText(tr("%1").arg(ui.pvpEdit->text().toDouble() * (double)cantidad));
					pair <string, double> tmp(a_tmp->getdescripcion(), a_tmp->getpvp()); 
					lArticuloFila.push_back(pair<pair<string, double>, int>(tmp, row));
					nuevaFactura->addArticulo(*a_tmp,cantidad);
					actualizaPrecios();
				} else {
					if (capaNegocio->nuevoArticulo(&a)) {
						int row = ui.tableWidget->rowCount();
						addRow();	
						ui.tableWidget->item(row, 0)->setText("0");
						ui.tableWidget->item(row, 1)->setText(ui.descripcionEdit->text());
						ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad));
						ui.tableWidget->item(row, 3)->setText(tr("%1").arg(a.getpvp(), 0, 'f', 2));
						ui.tableWidget->item(row, 4)->setText(tr("%1").arg(a.getpvp() * (double)cantidad, 0, 'f', 2));
						pair <string, double> tmp(a.getdescripcion(), a.getpvp()); 
						lArticuloFila.push_back(pair<pair<string, double>, int>(tmp, row));
						nuevaFactura->addArticulo(a,cantidad);
						actualizaPrecios();
					} else {
						QMessageBox::warning(this, "Aviso", "Fallo al guardar el nuevo articulo.");
					}		
				}
			} else {
				// Encuentra
				Articulo *a_tmp = capaNegocio->getArticuloDescripcionPvp(ui.descripcionEdit->text().toStdString(), ui.pvpEdit->text().toDouble());
				cout << "[Debug]" << a_tmp->getid() << endl;
				int row = it->second;
				int cantidad_prev = ui.tableWidget->item(row, 2)->text().toInt();
				nuevaFactura->modificarArticulo(*a_tmp, cantidad_prev + cantidad);
				ui.tableWidget->item(row, 2)->setText(tr("%1").arg(cantidad_prev + cantidad));
				ui.tableWidget->item(row, 4)->setText(tr("%1").arg(ui.pvpEdit->text().toDouble() * (double)(cantidad_prev + cantidad)));
				actualizaPrecios();
			}
			
		}		
	} else {
		QMessageBox::warning(this, "Aviso", "Articulo no encontrado.");
	}
	Articulo aux;
	articuloActual = aux;
}

void NuevaFacturaDialog::keyPressEvent(QKeyEvent* event) {
	//mutex.lock();
	if ((ui.nombreEdit->hasFocus() || ui.lineEdit_13->hasFocus()) && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
		buscarCliente();
	else if ((ui.descripcionEdit->hasFocus() || ui.referenciaEdit->hasFocus() ) && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
		buscarArticulo();
}
void NuevaFacturaDialog::keyReleaseEvent(QKeyEvent* event) {
	//mutex.unlock();
}

void NuevaFacturaDialog::borrarArticulo() {
	int row = ui.tableWidget->currentRow();
	if (row < 0) {
		QMessageBox::warning(this, tr("Aviso"), tr("Ha de haber una fila seleccionada."));
		return;
	}

	string des = ui.tableWidget->item(row, 1)->text().toStdString();
	double pvp = ui.tableWidget->item(row, 3)->text().toDouble();
	int cod = ui.tableWidget->item(row, 0)->text().toInt();
	
	cout << "[Debug]Borrando el articulo de descripcion: " << des << endl;
	
	Articulo *a;
	if ( cod == 0 )
		a = capaNegocio->getArticuloDescripcionPvp(des, pvp);
	else 
		a = capaNegocio->getArticuloCodigo(cod);
	
	if (a == 0) {
		cout << "[Debug]Articulo no encontrado en la CapaNegocio" << endl;
	}
	
	list<pair<pair<string, double>, int> >::iterator it;
	for (it = lArticuloFila.begin(); it != lArticuloFila.end(); it++) {
		if (a->getdescripcion() == it->first.first && a->getpvp() == it->first.second) {
			break;
		}
	}
	lArticuloFila.erase(it);

	if (!nuevaFactura->eliminarArticulo(*a))
		cout << "[Debug]No se borra el articulo de la factura." << a->getid() << endl;
	
	ui.tableWidget->removeRow(row);
	
	actualizaPrecios();
}

void NuevaFacturaDialog::actualizaPrecios() {
	mutex.lock();
	double materiales = nuevaFactura->getMateriales();
	double mano_obra = ui.lineEdit_7->text().toDouble();
	double desplazamiento = ui.lineEdit_8->text().toDouble();
	double transporte = ui.lineEdit_9->text().toDouble();
	double subtotal = materiales + mano_obra + desplazamiento + transporte;
	double total = subtotal + (ui.lineEdit_11->text().toDouble() / 100.0 )*subtotal; 
	
	ui.lineEdit_10->setText(tr("%1").arg(subtotal, 0, 'f', 2));
	ui.lineEdit_6->setText(tr("%1").arg(materiales, 0, 'f', 2));
	ui.lineEdit_12->setText(tr("%1").arg(total, 0, 'f', 2));
	mutex.unlock();
}

bool NuevaFacturaDialog::comprobarDatos () {
	bool flag = true;
	if (cliente == 0) {
		if(ui.nombreEdit->text()==""){
			QMessageBox::information(this, tr("Atencion"),
					tr("El campo nombre es necesario"));
					flag=false;
			}
			if(ui.lineEdit_13->text()==""){
				QMessageBox::information(this, tr("Atencion"),
					 tr("El campo apellido es necesario"));
				flag=false;
			}			
			bool ok;
			ui.codigoEdit->text().toInt(&ok);
			if(!ok){
				QMessageBox::information(this, tr("Atencion"),
					tr("El campo codigo ha de ser numerico"));
				flag=false;
			}
			int rows = ui.tabla->rowCount();
			for (int i = 0; i < rows; i++) {
				ui.tabla->item(i,0)->text().toInt(&ok);
				if(!ok && ui.tabla->item(i,0)->text()!=""){
					QMessageBox::information(this, tr("Atención"),
							tr("Hay un teléfono incorrecto."));
					flag=false;
				}		
			}
	}
	bool ok;
	ui.lineEdit_4->text().toInt(&ok);
	if(!ok && ui.lineEdit_4->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El campo codigo ha de ser numerico"));
		flag=false;
	}
	ui.lineEdit_5->text().toDouble(&ok);
	if(!ok && ui.lineEdit_5->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El tiempo empleado ha de ser numerico"));
		flag=false;
	}
	ui.lineEdit_7->text().toDouble(&ok);
	if(!ok && ui.lineEdit_7->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("La mano de obra ha de ser numerica"));
		flag=false;
	}
	ui.lineEdit_8->text().toDouble(&ok);
	if(!ok && ui.lineEdit_8->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El desplazamiento ha de ser numerico"));
		flag=false;
	}
	ui.lineEdit_9->text().toDouble(&ok);
	if(!ok && ui.lineEdit_9->text() != ""){
		QMessageBox::information(this, tr("Atencion"),
				tr("El transporte ha de ser numerico"));
		flag=false;
	}
	if (nuevaFactura->getn_factura() == -1 && ui.lineEdit_4->text() != "" && capaNegocio->getFacturaNumero(ui.lineEdit_4->text().toInt()) != 0 ) {
		QMessageBox::information(this, tr("Atención"),
						tr("Nº de factura repetido."));
		flag=false;
	}
	return flag;
}

bool NuevaFacturaDialog::guardarSinSalir() {
	
	bool clienteOk;
	
	if (comprobarDatos()) {
		
		nuevaFactura->setaparato(ui.lineEdit->text().toStdString());
		nuevaFactura->setaveria(ui.textEdit->document()->toPlainText().toStdString());
		
		if (ui.checkBox->isChecked()) { 
			nuevaFactura->setfecha(ui.dateEdit->text().toStdString());
		} else {
			nuevaFactura->setfecha(tr("").toStdString());
		}
		
		//nuevaFactura->setfecha_terminacion(ui.lineEdit_->text());
		if (ui.checkBox_4->isChecked()) { 
			nuevaFactura->setfecha_terminacion(ui.dateEdit_2->text().toStdString());
		} else {
			nuevaFactura->setfecha_terminacion(tr("").toStdString());
		}
				
		if (!ui.checkBox_2->isChecked() && !ui.checkBox_3->isChecked()) 
			nuevaFactura->setlugar_reparacion(0);
		else {
			bool *s = new bool;
			*s = ui.checkBox_2->isChecked();
			nuevaFactura->setlugar_reparacion(s);
		}
		
		nuevaFactura->setmarca(ui.lineEdit_2->text().toStdString());
		nuevaFactura->setmodelo(ui.lineEdit_3->text().toStdString());
		
		//nuevaFactura->setn_fabricacion(ui.lineEdit_->text());
		
		if (ui.lineEdit_4->text() == "") {
			nuevaFactura->setn_factura(-1);
		} else {
			nuevaFactura->setn_factura(ui.lineEdit_4->text().toInt());
		}
		
		nuevaFactura->setiva(ui.lineEdit_11->text().toInt());

		nuevaFactura->setobservaciones(ui.textEdit->document()->toPlainText().toStdString());
		nuevaFactura->setprecio_desplazamiento(ui.lineEdit_8->text().toDouble());
		nuevaFactura->setprecio_mano_obra(ui.lineEdit_7->text().toDouble());
		nuevaFactura->setprecio_materiales(ui.lineEdit_6->text().toDouble());
		nuevaFactura->setprecio_transporte(ui.lineEdit_9->text().toDouble());
		
		nuevaFactura->settiempo_empleado(ui.lineEdit_5->text().toStdString());
		nuevaFactura->settrabajo_realizado(ui.textEdit_2->document()->toPlainText().toStdString());
		
		if (cliente == 0) {
			cliente = new Cliente();
			cliente->setnombre(ui.nombreEdit->text().toStdString());
			cliente->setapellidos(ui.lineEdit_13->text().toStdString());
			cliente->setcodigo(ui.codigoEdit->text().toInt());
			cliente->setdireccion(ui.direccionEdit->document()->toPlainText().toStdString());
			cliente->setpoblacion(ui.lineEdit_14->text().toStdString());
			cliente->setnif(ui.nifEdit->text().toStdString());
			clienteOk = capaNegocio->nuevoCliente(cliente);
		} else {
			clienteOk = true;
		}

		if (clienteOk)
			nuevaFactura->setcliente(cliente);
		else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar el nuevo cliente."));
			
		if (capaNegocio->nuevaFactura(nuevaFactura) && clienteOk) {
			if (padre != 0)
				padre->actualizar();
			return true;
			//this->accept();
		} else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar la factura."));
	}
	return false;
}

void NuevaFacturaDialog::guardar() {
	
	bool clienteOk;
	
	if (comprobarDatos()) {
		
		nuevaFactura->setaparato(ui.lineEdit->text().toStdString());
		nuevaFactura->setaveria(ui.textEdit->document()->toPlainText().toStdString());
		
		if (ui.checkBox->isChecked()) { 
			nuevaFactura->setfecha(ui.dateEdit->text().toStdString());
		} else {
			nuevaFactura->setfecha(tr("").toStdString());
		}
		if (ui.checkBox_4->isChecked()) { 
			nuevaFactura->setfecha_terminacion(ui.dateEdit_2->text().toStdString());
		} else {
			nuevaFactura->setfecha_terminacion(tr("").toStdString());
		}
		
		//nuevaFactura->setfecha_terminacion(ui.lineEdit_->text());
		
		if (!ui.checkBox_2->isChecked() && !ui.checkBox_3->isChecked()) 
			nuevaFactura->setlugar_reparacion(0);
		else {
			bool *s = new bool;
			*s = ui.checkBox_2->isChecked();
			nuevaFactura->setlugar_reparacion(s);
		}
		
		nuevaFactura->setmarca(ui.lineEdit_2->text().toStdString());
		nuevaFactura->setmodelo(ui.lineEdit_3->text().toStdString());
		
		//nuevaFactura->setn_fabricacion(ui.lineEdit_->text());
		
		if (ui.lineEdit_4->text() == "") {
			nuevaFactura->setn_factura(-1);
		} else {
			nuevaFactura->setn_factura(ui.lineEdit_4->text().toInt());
		}
		
		nuevaFactura->setiva(ui.lineEdit_11->text().toInt());
		nuevaFactura->setobservaciones(ui.lineEdit_15->text().toStdString());
		nuevaFactura->setprecio_desplazamiento(ui.lineEdit_8->text().toDouble());
		nuevaFactura->setprecio_mano_obra(ui.lineEdit_7->text().toDouble());
		nuevaFactura->setprecio_materiales(ui.lineEdit_6->text().toDouble());
		nuevaFactura->setprecio_transporte(ui.lineEdit_9->text().toDouble());
		
		nuevaFactura->settiempo_empleado(ui.lineEdit_5->text().toStdString());
		nuevaFactura->settrabajo_realizado(ui.textEdit_2->document()->toPlainText().toStdString());
		
		if (cliente == 0) {
			cliente = new Cliente();
			cliente->setnombre(ui.nombreEdit->text().toStdString());
			cliente->setapellidos(ui.lineEdit_13->text().toStdString());
			cliente->setcodigo(ui.codigoEdit->text().toInt());
			cliente->setdireccion(ui.direccionEdit->document()->toPlainText().toStdString());
			cliente->setpoblacion(ui.lineEdit_14->text().toStdString());
			cliente->setnif(ui.nifEdit->text().toStdString());
			/**
			 * Guardar los teléfonos.
			 */
			list<int> telefonos;
			int rows = ui.tabla->rowCount();
			for (int i = 0; i < rows; i++) {
				telefonos.push_back(ui.tabla->item(i, 0)->text().toInt());
			}
			cliente->settelefonos(telefonos);
			clienteOk = capaNegocio->nuevoCliente(cliente);
		} else {
			clienteOk = true;
		}

		if (clienteOk)
			nuevaFactura->setcliente(cliente);
		else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar el nuevo cliente."));
			
		if (capaNegocio->nuevaFactura(nuevaFactura) && clienteOk) {
			if (padre != 0 && !dePresupuesto)
				padre->actualizar();
			this->accept();
		} else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar la factura."));
	}
}

void NuevaFacturaDialog::editar() {
	
	bool clienteOk;
	
	if (comprobarDatos()) {
		
		nuevaFactura->setaparato(ui.lineEdit->text().toStdString());
		nuevaFactura->setaveria(ui.textEdit->document()->toPlainText().toStdString());
		
		if (ui.checkBox->isChecked()) { 
			nuevaFactura->setfecha(ui.dateEdit->text().toStdString());
		} else {
			nuevaFactura->setfecha(tr("").toStdString());
		}
		
		//nuevaFactura->setfecha_terminacion(ui.lineEdit_->text());
		
		if (!ui.checkBox_2->isChecked() && !ui.checkBox_3->isChecked()) 
			nuevaFactura->setlugar_reparacion(0);
		else {
			bool *s = new bool;
			*s = ui.checkBox_2->isChecked();
			nuevaFactura->setlugar_reparacion(s);
		}
		if (ui.checkBox_4->isChecked()) { 
			nuevaFactura->setfecha_terminacion(ui.dateEdit_2->text().toStdString());
		} else {
			nuevaFactura->setfecha_terminacion(tr("").toStdString());
		}
		nuevaFactura->setmarca(ui.lineEdit_2->text().toStdString());
		nuevaFactura->setmodelo(ui.lineEdit_3->text().toStdString());

		//nuevaFactura->setn_fabricacion(ui.lineEdit_->text());
		
		if (ui.lineEdit_4->text() == "") {
			nuevaFactura->setn_factura(-1);
		} else {
			nuevaFactura->setn_factura(ui.lineEdit_4->text().toInt());
		}
		
		nuevaFactura->setobservaciones(ui.lineEdit_15->text().toStdString());
		nuevaFactura->setprecio_desplazamiento(ui.lineEdit_8->text().toDouble());
		nuevaFactura->setprecio_mano_obra(ui.lineEdit_7->text().toDouble());
		nuevaFactura->setprecio_materiales(ui.lineEdit_6->text().toDouble());
		nuevaFactura->setprecio_transporte(ui.lineEdit_9->text().toDouble());
		
		nuevaFactura->settiempo_empleado(ui.lineEdit_5->text().toStdString());
		nuevaFactura->settrabajo_realizado(ui.textEdit_2->document()->toPlainText().toStdString());
		
		if (cliente == 0) {
			cliente = new Cliente();
			cliente->setnombre(ui.nombreEdit->text().toStdString());
			cliente->setapellidos(ui.lineEdit_13->text().toStdString());
			cliente->setcodigo(ui.codigoEdit->text().toInt());
			cliente->setdireccion(ui.direccionEdit->document()->toPlainText().toStdString());
			cliente->setpoblacion(ui.lineEdit_14->text().toStdString());
			cliente->setnif(ui.nifEdit->text().toStdString());
			list<int> lista_telefonos;
			for (int i = 0; i < ui.tabla->rowCount(); i++) {
				lista_telefonos.push_back(ui.tabla->item(i,0)->text().toInt());
			}
			cliente->settelefonos(lista_telefonos);
			clienteOk = capaNegocio->nuevoCliente(cliente);
		} else {
			clienteOk = true;
		}

		if (clienteOk)
			nuevaFactura->setcliente(cliente);
		else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar el nuevo cliente."));
			
		if (capaNegocio->modificarFactura(nuevaFactura) && clienteOk) {
			if (padre != 0)
				padre->actualizar();
			this->accept();
		} else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo editar la factura."));
	}
}


bool NuevaFacturaDialog::editarSinSalir() {
	
	bool clienteOk;
	
	if (comprobarDatos()) {
		
		nuevaFactura->setaparato(ui.lineEdit->text().toStdString());
		nuevaFactura->setaveria(ui.textEdit->document()->toPlainText().toStdString());
		
		if (ui.checkBox->isChecked()) { 
			nuevaFactura->setfecha(ui.dateEdit->text().toStdString());
		} else {
			nuevaFactura->setfecha(tr("").toStdString());
		}
		
		//nuevaFactura->setfecha_terminacion(ui.lineEdit_->text());
		
		if (!ui.checkBox_2->isChecked() && !ui.checkBox_3->isChecked()) 
			nuevaFactura->setlugar_reparacion(0);
		else {
			bool *s = new bool;
			*s = ui.checkBox_2->isChecked();
			nuevaFactura->setlugar_reparacion(s);
		}
		
		nuevaFactura->setmarca(ui.lineEdit_2->text().toStdString());
		nuevaFactura->setmodelo(ui.lineEdit_3->text().toStdString());

		//nuevaFactura->setn_fabricacion(ui.lineEdit_->text());
		
		if (ui.lineEdit_4->text() == "") {
			nuevaFactura->setn_factura(-1);
		} else {
			nuevaFactura->setn_factura(ui.lineEdit_4->text().toInt());
		}
		
		nuevaFactura->setiva(ui.lineEdit_11->text().toInt());
		nuevaFactura->setobservaciones(ui.textEdit->document()->toPlainText().toStdString());
		nuevaFactura->setprecio_desplazamiento(ui.lineEdit_8->text().toDouble());
		nuevaFactura->setprecio_mano_obra(ui.lineEdit_7->text().toDouble());
		nuevaFactura->setprecio_materiales(ui.lineEdit_6->text().toDouble());
		nuevaFactura->setprecio_transporte(ui.lineEdit_9->text().toDouble());
		
		nuevaFactura->settiempo_empleado(ui.lineEdit_5->text().toStdString());
		nuevaFactura->settrabajo_realizado(ui.textEdit_2->document()->toPlainText().toStdString());
		
		if (cliente == 0) {
			cliente = new Cliente();
			cliente->setnombre(ui.nombreEdit->text().toStdString());
			cliente->setapellidos(ui.lineEdit_13->text().toStdString());
			cliente->setcodigo(ui.codigoEdit->text().toInt());
			cliente->setdireccion(ui.direccionEdit->document()->toPlainText().toStdString());
			cliente->setpoblacion(ui.lineEdit_14->text().toStdString());
			cliente->setnif(ui.nifEdit->text().toStdString());
			list<int> lista_telefonos;
			for (int i = 0; i < ui.tabla->rowCount(); i++) {
				lista_telefonos.push_back(ui.tabla->item(i,0)->text().toInt());
			}
			cliente->settelefonos(lista_telefonos);
			clienteOk = capaNegocio->nuevoCliente(cliente);
		} else {
			clienteOk = true;
		}

		if (clienteOk)
			nuevaFactura->setcliente(cliente);
		else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo guardar el nuevo cliente."));
			
		if (capaNegocio->modificarFactura(nuevaFactura) && clienteOk) {
			if (padre != 0)
				padre->actualizar();
			return true;
			//this->accept();
		} else 
			QMessageBox::critical(this, tr("Error"), tr("No se pudo editar la factura."));
	}
	return false;
}

void NuevaFacturaDialog::addRowTelefono(){
	int row = ui.tabla->rowCount();
	ui.tabla->insertRow(row);
	
	QTableWidgetItem *item0 = new QTableWidgetItem;
	item0->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	ui.tabla->setItem(row, 0, item0);
		
}

void NuevaFacturaDialog::nuevoTelefono () {
	int row = ui.tabla->currentRow();
	if (row == -1) {
		addRowTelefono();
		ui.tabla->setCurrentCell(0,0);
	} else if (ui.tabla->item(row,0)->text() != "") {
		addRowTelefono();
		ui.tabla->setCurrentCell(row + 1,0);
	}
}

void NuevaFacturaDialog::borrarTelefono() {
	int row = ui.tabla->currentRow();
	if (row == -1)
		QMessageBox::warning(this, "Aviso", "No se ha seleccionado ningun telefono.");
	else 
		ui.tabla->removeRow(row);
	
}

// Invierte el estado de "habilitado" de los campos de cliente
void NuevaFacturaDialog::cambiarCliente() {
	ui.nombreEdit->setEnabled(!ui.nombreEdit->isEnabled());
	ui.lineEdit_13->setEnabled(!ui.lineEdit_13->isEnabled());
	ui.codigoEdit->setEnabled(!ui.codigoEdit->isEnabled());
	ui.direccionEdit->setEnabled(!ui.direccionEdit->isEnabled());
	ui.lineEdit_14->setEnabled(!ui.lineEdit_14->isEnabled());
	ui.nifEdit->setEnabled(!ui.nifEdit->isEnabled());	
	ui.tabla->setEnabled(!ui.tabla->isEnabled());
	ui.pushButton_6->setEnabled(!ui.pushButton_6->isEnabled());
	ui.pushButton_8->setEnabled(!ui.pushButton_8->isEnabled());
}

void NuevaFacturaDialog::limpiar() {
	if (ui.nombreEdit->text() != "" ) {
		cambiarCliente();
	}
	ui.nombreEdit->setText("");
	ui.lineEdit_13->setText("");
	ui.codigoEdit->setText("");
	QString direccion;
	direccion.append("");
	QTextDocument *direccionCompleta = new QTextDocument(direccion);
	ui.direccionEdit->setDocument(direccionCompleta);
	ui.lineEdit_14->setText("");
	ui.nifEdit->setText("");
	cliente = 0;	
	while (ui.tabla->rowCount() > 0) {
		ui.tabla->removeRow(0);
	}
	
	int cod = capaNegocio->getUltimoCodigoCliente();
	ui.codigoEdit->setText(QString::number(cod));
}

void NuevaFacturaDialog::cambiarEstadoDomicilio() {
	if (ui.checkBox_2->isChecked()) {		
		if (ui.checkBox_3->isChecked()) {
			ui.checkBox_3->setChecked(false);
		}
	}
}

void NuevaFacturaDialog::cambiarEstadoTaller() {
	if (ui.checkBox_3->isChecked()) {		
		if (ui.checkBox_2->isChecked()) {
			ui.checkBox_2->setChecked(false);
		}
	}
}

void NuevaFacturaDialog::imprimir() {
	if (nuevaFactura->getid() == -1) {
		if (QMessageBox::question(this, tr("Imprimir Factura"), tr("Antes de imprimir es necesario guardar la factura.\n ¿Desea realmente guardarla?"),tr("Si"),tr("No")) == 0) {
			if(guardarSinSalir()) {
				PrintWindow* pq = new PrintWindow(*nuevaFactura);
				pq->printFactura();
				this->accept();
			}
		}
	} else {
		if (QMessageBox::question(this, tr("Imprimir Factura"), tr("Antes de imprimir es necesario guardar la factura.\n ¿Desea realmente guardarla?"),tr("Si"),tr("No")) == 0) {
			if(editarSinSalir()) {
				PrintWindow* pq = new PrintWindow(*nuevaFactura);
				pq->printFactura();
				this->accept();
			}
		}
	}

}

