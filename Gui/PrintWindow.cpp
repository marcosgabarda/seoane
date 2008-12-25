#include "PrintWindow.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QString>
#include <QPrintDialog>
#include <QtGui>
#include "../Negocio/Factura.h"
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <fstream>
#include "../Negocio/LineaArticulo.h"

using namespace std;

PrintWindow::PrintWindow() {
	
}

PrintWindow::PrintWindow(const Factura &f)
{
	printer.setPageSize(QPrinter::A4);
	printer.setOrientation(QPrinter::Portrait);
	printer.setPaperSource(QPrinter::Tractor);
	factura = f;
	fstream fileConfig;
	fileConfig.open("Gui/printer.cfg", fstream::in);
	if (fileConfig.fail()) {
		return ;
	}
	string name, value;
	while (!fileConfig.eof()) {
		fileConfig >> name >> value;
		if (name == "Manual") {
			if (value == "true") {
				manual = true;
			} else if (value == "false") {
				manual = false;
			} else {
				manual = false;
			}
		} else if (name == "Puerto") {
			puerto = QString(value.c_str());
		} else if (name == "Largo") {
			largo = atoi(value.c_str());
		} else if (name == "Ancho") {
			largo = atoi(value.c_str());
		}
	}
	fileConfig.close();
}

PrintWindow::PrintWindow(const Presupuesto &f)
{
	printer.setPageSize(QPrinter::A4);
	printer.setOrientation(QPrinter::Portrait);
	printer.setPaperSource(QPrinter::Tractor);
	presupuesto = f;	
}

PrintWindow::~PrintWindow()
{
}

QString PrintWindow::cuadroPresupuestoCliente() {
	QString cadenaCliente;
	Cliente *c = presupuesto.getcliente();
	cadenaCliente += c->getapellidos().c_str();
	cadenaCliente += ", ";
	cadenaCliente += c->getnombre().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getdireccion().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getpoblacion().c_str();
	cadenaCliente += "\n";
	cadenaCliente += "DNI: ";
	cadenaCliente += c->getnif().c_str();
	cadenaCliente += "\n";
	list<int> lTelefonos = c->gettelefonos();
	list<int>::iterator it;
	int i = 1;
	for (it = lTelefonos.begin(); it != lTelefonos.end(); it++, i++) {
		cadenaCliente += "Tel. ";
		cadenaCliente += QString::number(i,10).toStdString().c_str();
		cadenaCliente += ": ";
		cadenaCliente += QString::number(*it,10).toStdString().c_str();
		if (i%3 == 0)
			cadenaCliente += "\n";
		else 
			cadenaCliente += "\t";
	}
	return cadenaCliente;
}

QString PrintWindow::cuadroFacturaCliente() {
	QString cadenaCliente;
	Cliente *c = factura.getcliente();
	cadenaCliente += c->getapellidos().c_str();
	cadenaCliente += ", ";
	cadenaCliente += c->getnombre().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getdireccion().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getpoblacion().c_str();
	cadenaCliente += "\n";
	cadenaCliente += "DNI: ";
	cadenaCliente += c->getnif().c_str();
	cadenaCliente += "\n";
	list<int> lTelefonos = c->gettelefonos();
	list<int>::iterator it;
	int i = 1;
	for (it = lTelefonos.begin(); it != lTelefonos.end(); it++, i++) {
		cadenaCliente += "Tel. ";
		cadenaCliente += QString::number(i,10).toStdString().c_str();
		cadenaCliente += ": ";
		cadenaCliente += QString::number(*it,10).toStdString().c_str();
		if (i%3 == 0)
			cadenaCliente += "\n";
		else 
			cadenaCliente += "\t";
	}
	return cadenaCliente;
}


QString PrintWindow::cuadroClienteSobre(Cliente *c) {
	QString cadenaCliente;
	
	cadenaCliente += c->getapellidos().c_str();
	cadenaCliente += ", ";
	cadenaCliente += c->getnombre().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getdireccion().c_str();
	cadenaCliente += "\n";
	cadenaCliente += c->getpoblacion().c_str();
	cadenaCliente += "\n";
	
	
	return cadenaCliente;
}



void PrintWindow::printFactura() {
	if (!manual) {
		QString html = cuadroFacturaCliente();
		QPrintDialog printDialog(&printer, 0);
		if (printDialog.exec()) {
			QPainter painter(&printer);
			//QImage fondo("Gui/images/factura.png");
			 //if (fondo.isNull()) {
			 //cout << "Error al abrir la imgen." << endl;
			// }
			 //painter.drawImage(0,0,fondo);
			//QRect rect = painter.boundingRect(400,66,100,100,Qt::AlignLeft | Qt::TextWordWrap, html);
			painter.setFont(QFont("Arial", 10));
			painter.drawText(370, 66, 400, 100, Qt::AlignLeft
					| Qt::TextWordWrap, html);
			int y = 230;
			int x = 0;
			int incx = 115;
			painter.drawText(x, y, 100, 33, Qt::AlignLeft | Qt::TextWordWrap,
					QString("%1").arg(factura.getn_factura()));
			painter.drawText(x + incx, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getfecha().c_str()));
			painter.drawText(x + incx*2 + 15, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getaparato().c_str()));
			painter.drawText(x + incx*3 + 35, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getmarca().c_str()));
			painter.drawText(x + incx*4 + 55, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getmodelo().c_str()));
			painter.drawText(x + incx*5 + 70, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getn_fabricacion()));
			if (factura.getlugar_reparacion() != 0) {
				bool lugar = *factura.getlugar_reparacion();
				if (lugar) {
					painter.drawText(68, 185, 100, 100, Qt::AlignLeft
							| Qt::TextWordWrap, QString("X"));
				} else {
					painter.drawText(128, 185, 100, 100, Qt::AlignLeft
							| Qt::TextWordWrap, QString("X"));
				}
			}
			painter.drawText(180, 265, 600, 17, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getaveria().c_str()));
			list<LineaArticulo> l = factura.getlista_articulos();
			list<LineaArticulo>::iterator it;
			x = 0;
			y = 315;
			int i = 0;
			for (it = l.begin(); it != l.end() && i < 12; it++, i++) {
				painter.drawText(x, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getarticulo().getcodigo()));
				painter.drawText(x + 145, y, 350, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString(it->getarticulo().getdescripcion().c_str()));
				painter.drawText(x + 510, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getcantidad()));
				painter.drawText(x + 580, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getarticulo().getpvp() - it->getarticulo().getpvp()*it->getarticulo().getdescuento()));
				painter.drawText(x + 670, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getpreciototal()));
				y += 17;
			}
			painter.drawText(480, 502, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.gettiempo_empleado().c_str()));
			painter.drawText(0, 519, 550, 119, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.gettrabajo_realizado().c_str()));
			painter.drawText(670, 502, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getMateriales()));
			painter.drawText(670, 519, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getprecio_mano_obra()));
			painter.drawText(670, 536, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getprecio_desplazamiento()));
			painter.drawText(670, 553, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getprecio_transporte()));
			painter.drawText(670, 570, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getSubTotal()));
			painter.drawText(670, 587, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getiva()));
			painter.drawText(670, 604, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(factura.getTotal()));
			painter.drawText(470, 630, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getfecha_terminacion().c_str()));
			painter.drawText(0, 664, 550, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(factura.getobservaciones().c_str()));
		}
	} else {
		ofstream printer;
		printer.open(puerto.toStdString().c_str());
		printer << "Hola mundo\f" << endl;
		printer.close();
	}
}

void PrintWindow::printPresupuesto() {
	if (!manual) {
		QString html = cuadroPresupuestoCliente();
		QPrintDialog printDialog(&printer, 0);
		if (printDialog.exec()) {
			QPainter painter(&printer);
			//QImage fondo("Gui/images/factura.png");
			// if (fondo.isNull()) {
			// cout << "Error al abrir la imgen." << endl;
			// }
			// painter.drawImage(0,0,fondo);
			//QRect rect = painter.boundingRect(400,66,100,100,Qt::AlignLeft | Qt::TextWordWrap, html);
			painter.setFont(QFont("Arial", 10));
			painter.drawText(370, 66, 400, 100, Qt::AlignLeft
					| Qt::TextWordWrap, html);
			int y = 230;
			int x = 0;
			int incx = 115;
			painter.drawText(x, y, 100, 33, Qt::AlignLeft | Qt::TextWordWrap,
					QString("%1").arg(presupuesto.getn_factura()));
			painter.drawText(x + incx, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getfecha().c_str()));
			painter.drawText(x + incx*2 + 15, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getaparato().c_str()));
			painter.drawText(x + incx*3 + 35, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getmarca().c_str()));
			painter.drawText(x + incx*4 + 55, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getmodelo().c_str()));
			painter.drawText(x + incx*5 + 70, y, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getn_fabricacion()));
			if (presupuesto.getlugar_reparacion() != 0) {
				bool lugar = *presupuesto.getlugar_reparacion();
				if (lugar) {
					painter.drawText(68, 185, 100, 100, Qt::AlignLeft
							| Qt::TextWordWrap, QString("X"));
				} else {
					painter.drawText(128, 185, 100, 100, Qt::AlignLeft
							| Qt::TextWordWrap, QString("X"));
				}
			}
			painter.drawText(180, 265, 600, 17, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getaveria().c_str()));
			list<LineaArticulo> l = presupuesto.getlista_articulos();
			list<LineaArticulo>::iterator it;
			x = 0;
			y = 315;
			int i = 0;
			for (it = l.begin(); it != l.end() && i < 12; it++, i++) {
				painter.drawText(x, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getarticulo().getcodigo()));
				painter.drawText(x + 145, y, 350, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString(it->getarticulo().getdescripcion().c_str()));
				painter.drawText(x + 510, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getcantidad()));
				painter.drawText(x + 580, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getarticulo().getpvp() - it->getarticulo().getpvp()*it->getarticulo().getdescuento()));
				painter.drawText(x + 670, y, 100, 33, Qt::AlignLeft
						| Qt::TextWordWrap, QString("%1").arg(it->getpreciototal()));
				y += 17;
			}
			painter.drawText(480, 502, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.gettiempo_empleado().c_str()));
			painter.drawText(0, 519, 550, 119, Qt::AlignLeft
					| Qt::TextWordWrap,
					QString(presupuesto.gettrabajo_realizado().c_str()));
			painter.drawText(670, 502, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getMateriales()));
			painter.drawText(670, 519, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getprecio_mano_obra()));
			painter.drawText(670, 536, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getprecio_desplazamiento()));
			painter.drawText(670, 553, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getprecio_transporte()));
			painter.drawText(670, 570, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getSubTotal()));
			painter.drawText(670, 588, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getiva()));
			painter.drawText(670, 605, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString("%1").arg(presupuesto.getTotal()));
			painter.drawText(480, 630, 100, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getfecha_terminacion().c_str()));
			painter.drawText(0, 664, 550, 33, Qt::AlignLeft
					| Qt::TextWordWrap, QString(presupuesto.getobservaciones().c_str()));
						
			
		}
	} else {
		
	}
}


void PrintWindow::printListaClientes(list<Cliente> lClientes){
	
	printer.setPageSize(QPrinter::Letter);
	printer.setOrientation(QPrinter::Landscape);
	printer.setPaperSource(QPrinter::Auto);
	
	QPrintDialog printDialog(&printer, 0);
	QPainter painter(&printer);
	
	list<Cliente>::iterator it;
	if (printDialog.exec()) {
		for(it = lClientes.begin(); it!= lClientes.end(); it++){
			Cliente c = *it;
			QString html = cuadroClienteSobre(&c);
			
			//painter.begin();
			painter.drawText(0, 0, 500, 500, Qt::AlignLeft | Qt::TextWordWrap, html);
			//painter.end();
		}
	}
	
}
