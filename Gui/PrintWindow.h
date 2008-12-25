#ifndef PRINTWINDOW_H_
#define PRINTWINDOW_H_
#include <QString>
#include "../Negocio/Factura.h"
#include <QPrinter>
#include "../Negocio/Presupuesto.h"


class PrintWindow
{
public:
	PrintWindow ();
	PrintWindow(const Factura &f);
	PrintWindow(const Presupuesto &f);
	virtual ~PrintWindow();
	void printFactura();
	void printPresupuesto();
	void printListaClientes(list<Cliente> l);
private:
	QString cuadroFacturaCliente();
	QString cuadroPresupuestoCliente();
	QString cuadroClienteSobre(Cliente *c);
	
	QPrinter printer;
	Factura factura;
	Presupuesto presupuesto;
	bool manual;
	QString puerto;
	int largo;
	int ancho;
};

#endif /*PRINTWINDOW_H_*/

