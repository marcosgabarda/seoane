#include "imprimirsobrecliente.h"
#include "../Negocio/CapaNegocio.h"
#include <list>
#include "../Negocio/Cliente.h"
#include "PrintWindow.h"
#include <QtGui>

ImprimirSobreCliente::ImprimirSobreCliente(QWidget *parent, CapaNegocio *cn)
    : QWidget(parent)
{
	ui.setupUi(this);
	capaNegocio = cn;
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(aceptar()));
}

ImprimirSobreCliente::~ImprimirSobreCliente()
{

}

void ImprimirSobreCliente::aceptar(){
	
	if(ui.lineEdit->text() == ""){
		QMessageBox::warning(this, "Aviso", "Debe especificar el rango del numero de clientes.");
	}
	else if(ui.lineEdit_2->text() == ""){
		QMessageBox::warning(this, "Aviso", "Debe especificar el rango del numero de clientes.");
	}
	
	int del, al;
	del = ui.lineEdit->text().toInt();
	al = ui.lineEdit_2->text().toInt();
	
	list<Cliente> l= capaNegocio->getClientesRango(del, al);
	
	if(l.size() == 0){
		QMessageBox::warning(this, "Aviso", "No hay clientes en el rango.");
		return;
	}
	else{
		PrintWindow* pq = new PrintWindow();
		pq->printListaClientes(l);
		this->close();
	}

}
