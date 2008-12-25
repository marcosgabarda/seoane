#include <list>
#include "Factura.h"
#include "CapaNegocio.h"
#include <iostream>
using namespace std;

CapaNegocio::CapaNegocio()
{

}

void CapaNegocio::inicializar() {

	accesoADatos = new AccesoADatos();
	cout << "[Debug]Capa de acceso a datos inicializada correctamente." << endl;
	cout << "[Debug]Cargando capa de negocio..." << endl;
	listaFacturas = accesoADatos->listaFacturas();
	listaClientes = accesoADatos->listaClientes();
	listaPresupuestos = accesoADatos->listaPresupuestos();
	listaArticulos = accesoADatos->listaArticulos();

	list<Factura>::iterator iteri;
	for (iteri=listaFacturas.begin(); iteri != listaFacturas.end(); iteri++) {
		//ENLAZAMOS LOS CLIENTES A LAS FACTURAS
		int idcliente = accesoADatos->enlazaCliente((*iteri).getid());
		list<Cliente>::iterator iterj;
		for (iterj=listaClientes.begin(); iterj != listaClientes.end(); iterj++) {
			if ((*iterj).getid() == idcliente) {
				(*iteri).setcliente(&(*iterj));
			}
		}
		//RELLENAMOS LA FACTURA CON SUS ARTICULOS
		list<int> l = accesoADatos->getListaIdArticulos(&(*iteri));
		list<int>::iterator iterInt;
		for (iterInt=l.begin(); iterInt != l.end(); iterInt++) {
			Articulo *a = getArticuloId(*iterInt);
			iteri->addArticulo(*a, accesoADatos->getCantidadArticuloFactura(&(*iteri),a));
		}
	}

	list<Presupuesto>::iterator iteri2;
	for (iteri2=listaPresupuestos.begin(); iteri2 != listaPresupuestos.end(); iteri2++) {
		int idcliente = accesoADatos->enlazaClienteP((*iteri2).getid());
		list<Cliente>::iterator iterj;
		for (iterj=listaClientes.begin(); iterj != listaClientes.end(); iterj++) {
			if ((*iterj).getid() == idcliente) {
				(*iteri2).setcliente(&(*iterj));
			}
		}
	}
	//Para enlazar presupuestos con facturas
	list<Presupuesto>::iterator iteri3;
	for (iteri3=listaPresupuestos.begin(); iteri3 != listaPresupuestos.end(); iteri3++) {
		int idfactura = accesoADatos->enlazaFactura((*iteri3).getid());
		list<Factura>::iterator iterj;
		for (iterj=listaFacturas.begin(); iterj != listaFacturas.end(); iterj++) {
			if ((*iterj).getid() == idfactura) {
				(*iteri3).setfactura(&(*iterj));
			}
		}
	}
	cout << "[Debug]Capa de negocio cargada." << endl;	
}

CapaNegocio::~CapaNegocio()
{
	cout << "[Debug]Destrimos la capa de negocio." << endl;
	delete accesoADatos;
	cout << "[Debug]Capa de negocio destruida." << endl;
}

bool CapaNegocio::nuevaFactura(Factura *f) {
	int nuevoId = accesoADatos->dameIdFactura();
	if (nuevoId == -1) return false;
	f->setid(nuevoId);
	if ( accesoADatos->insertaFactura(*f) ) { // Insertamos en la base de datos.
		listaFacturas.push_back(*f); //Si ha habido éxito, se inserta en memoria.
		return true;
	}
	return false;
}
bool CapaNegocio::nuevoCliente(Cliente *c) {
	int nuevoId = accesoADatos->dameIdCliente();
	if (nuevoId == -1) return false;
	c->setid(nuevoId);
	if ( accesoADatos->insertaCliente(*c) ) {
		listaClientes.push_back(*c);
		return true;
	}
	return false;
}
bool CapaNegocio::nuevoArticulo(Articulo *a) {
	int nuevoId = accesoADatos->dameIdArticulo();
	if (nuevoId == -1) return false;
	a->setid(nuevoId);
	if ( accesoADatos->insertaArticulo(*a) ) {
		listaArticulos.push_back(*a);
		return true;
	}
	return false;
}
bool CapaNegocio::nuevoPresupuesto(Presupuesto *p) {
	int nuevoId = accesoADatos->dameIdPresupuesto();
	if (nuevoId == -1) return false;
	p->setid(nuevoId);
	if ( accesoADatos->insertaPresupuesto(*p) ) {
		listaPresupuestos.push_back(*p);
		return true;
	}
	return false;
}

list<Articulo> CapaNegocio::getArticulos() {
	list<Articulo> lista;
	list<Articulo>::iterator i;
	for(i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
		if (!i->gethistorico() && i->getcodigo() != 0)
			lista.push_back((*i));
	}
	return lista;
}
Articulo* CapaNegocio::getArticuloId(int id) {
	Articulo *a = new Articulo;
	list<Articulo>::iterator i;
	for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
		if(i->getid() == id) {
			*a = *i;
			return a;
		}
	}
	return 0;
}
Articulo* CapaNegocio::getArticuloCodigo(int cod) {
	Articulo *a = new Articulo;
	list<Articulo>::iterator i;
	for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
		if(i->getcodigo() == cod && !i->gethistorico()) {
			*a = *i;
			return a;
		}
	}
	return 0;
}

Articulo* CapaNegocio::getArticuloDescripcionPvp(string des, double pvp) {
	Articulo *a = new Articulo;
	list<Articulo>::iterator i;
	for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
		if(i->getdescripcion() == des && i->getpvp() == pvp) {
			*a = *i;
			return a;
		}
	}
	return 0;
}

list<Factura> CapaNegocio::getFacturas() {
	list<Factura> l = listaFacturas;
	return l;
}
Factura* CapaNegocio::getFacturaId(int id) {
	Factura *f = new Factura();
	list<Factura>::iterator i;
	for (i = listaFacturas.begin(); i != listaFacturas.end(); i++) {
		if(i->getid() == id) {
			*f = *i;
			return f;
		}
	}
	return 0;
}
Factura *CapaNegocio::getFacturaNumero(int n) {
	Factura *f = new Factura();
	list<Factura>::iterator i;
	for (i = listaFacturas.begin(); i != listaFacturas.end(); i++) {
		if(i->getn_factura() == n) {
			*f = *i;
			return f;
		}
	}
	return 0;
}
list<Cliente> CapaNegocio::getClientes() {
	list<Cliente> lista;
	list<Cliente>::iterator i;
	for(i = listaClientes.begin(); i != listaClientes.end(); i++) {
		if (!i->gethistorico())
			lista.push_back((*i));
	}
	return lista;
}
Cliente *CapaNegocio::getClienteId(int id) {
	Cliente *c = new Cliente;
	list<Cliente>::iterator i;
	for (i = listaClientes.begin(); i != listaClientes.end(); i++) {
		if(i->getid() == id) {
			*c = *i;
			return c;
		}
	}
	return 0;
}
Cliente *CapaNegocio::getClienteCodigo(int cod) {
	Cliente *c = new Cliente;
	list<Cliente>::iterator i;
	for (i = listaClientes.begin(); i != listaClientes.end(); i++) {
		if(i->getcodigo() == cod && !i->gethistorico()) {
			*c = *i;
			return c;
		}
	}
	return 0;
}
list<Presupuesto> CapaNegocio::getPresupuestos() {
	list<Presupuesto> l = listaPresupuestos;
	return l;
}
Presupuesto* CapaNegocio::getPresupuestoId(int id) {
	Presupuesto *p = new Presupuesto();
	list<Presupuesto>::iterator i;
	for (i = listaPresupuestos.begin(); i != listaPresupuestos.end(); i++) {
		if(i->getid() == id) {
			*p = *i;
			return p;
		}
	}
	return 0;
}
Presupuesto* CapaNegocio::getPresupuestoNumero(int n) {
	Presupuesto *p = new Presupuesto();
	list<Presupuesto>::iterator i;
	for (i = listaPresupuestos.begin(); i != listaPresupuestos.end(); i++) {
		if(i->getn_factura() == n) {
			*p = *i;
			return p;
		}
	}
	return 0;
}

list<pair<int, int> > CapaNegocio::getListaTelefonos() {
	return accesoADatos->getListaTelefonos();
}

void CapaNegocio::verClientes() {
	list<Cliente>::iterator i;
	cout << "[Debug]Lista de clientes en memoria:" << endl;
	for (i = listaClientes.begin(); i != listaClientes.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getnombre() << " | " << (*i).getapellidos() <<endl;
	}
	list<Cliente> l = accesoADatos->listaClientes();
	cout << "[Debug]Lista de clientes en bd:" << endl;
	for (i = l.begin(); i != l.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getnombre() << " | " << (*i).getapellidos() <<endl;
	}
}

void CapaNegocio::verFacturas() {
	list<Factura>::iterator i;
	cout << "[Debug]Lista de facturas en memoria:" << endl;
	for (i = listaFacturas.begin(); i != listaFacturas.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getaparato() << " | "<< i->getfecha() << endl;
	}
	list<Factura> l = accesoADatos->listaFacturas();
	cout << "[Debug]Lista de facturas en bd:" << endl;
	for (i = l.begin(); i != l.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getaparato() << " | "<< i->getfecha() << endl;
	}
}

void CapaNegocio::verArticulos() {
	list<Articulo>::iterator i;
	cout << "[Debug]Lista de articulos en memoria:" << endl;
	for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getdescripcion() <<endl;
	}
	list<Articulo> l = accesoADatos->listaArticulos();
	cout << "[Debug]Lista de articulos en bd:" << endl;
	for (i = l.begin(); i != l.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getdescripcion() <<endl;
	}


}
void CapaNegocio::verPresupuestos() {
	list<Presupuesto>::iterator i;
	cout << "[Debug]Lista de presupuestos en memoria:" << endl;
	for (i = listaPresupuestos.begin(); i != listaPresupuestos.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getaparato() <<endl;
	}
	list<Presupuesto> l = accesoADatos->listaPresupuestos();
	cout << "[Debug]Lista de presupuestos en bd:" << endl;
	for (i = l.begin(); i != l.end(); i++) {
		cout << (*i).getid() << " | " << (*i).getaparato() <<endl;
	}

}

bool CapaNegocio::modificarFactura(Factura *f) {
	if (accesoADatos->actualizaFactura(*f)) {
		list<Factura>::iterator i;
		for (i = listaFacturas.begin(); i != listaFacturas.end(); i++) {
			if(i->getid() == f->getid()) break;
		}
		if (i == listaFacturas.end()) {
			return nuevaFactura(f);
		}
		list<Factura>::iterator newpos = listaFacturas.erase(i);
		listaFacturas.insert(newpos,*f);
		return true;
	}
	return false;
}

bool CapaNegocio::modificarPresupuesto(Presupuesto *p) {
	if (accesoADatos->actualizaPresupuesto(*p)) {
		list<Presupuesto>::iterator i;
		for (i = listaPresupuestos.begin(); i != listaPresupuestos.end(); i++) {
			if(i->getid() == p->getid()) break;
		}
		if (i == listaPresupuestos.end()) {
			return nuevoPresupuesto(p);
		}
		list<Presupuesto>::iterator newpos = listaPresupuestos.erase(i);
		listaPresupuestos.insert(newpos,*p);
		return true;
	}
	return false;

}

bool CapaNegocio::modificarCliente(Cliente *c) {
	int nuevoId = accesoADatos->dameIdCliente();
	if (nuevoId == -1) return false;
	if (accesoADatos->actualizaCliente(*c)) {
		list<Cliente>::iterator i;
		for (i = listaClientes.begin(); i != listaClientes.end(); i++) {
			if(i->getid() == c->getid()) break;
		}
		if (i == listaClientes.end()) {
			return nuevoCliente(c);
		}
		//list<Cliente>::iterator newpos = listaClientes.erase(i);
		i->sethistorico(true);
		c->setid(nuevoId);
		listaClientes.push_back(*c);
		return true;
	}
	return false;

}

bool CapaNegocio::modificarArticulo(Articulo *a) {
	int nuevoId = accesoADatos->dameIdArticulo();
	if (nuevoId == -1) return false;
	if (accesoADatos->actualizaArticulo(*a)) {
		list<Articulo>::iterator i;
		for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
			if(i->getid() == a->getid()) break;
		}
		if (i == listaArticulos.end()) {
			return nuevoArticulo(a);
		}
		//list<Articulo>::iterator newpos = listaArticulos.erase(i);
		i->sethistorico(true);
		a->setid(nuevoId);
		listaArticulos.push_back(*a);
		return true;
	}
	return false;

}

bool CapaNegocio::borrarFactura(Factura *f) {
	if (accesoADatos->eliminarFactura(*f)) {
		list<Factura>::iterator i;
		for (i = listaFacturas.begin(); i != listaFacturas.end(); i++) {
			if(i->getid() == f->getid()) break;
		}
		listaFacturas.erase(i);
		return true;
	}
	return false;
}

bool CapaNegocio::borrarPresupuesto(Presupuesto *p) {
	if (accesoADatos->eliminarPresupuesto(*p)) {
		list<Presupuesto>::iterator i;
		for (i = listaPresupuestos.begin(); i != listaPresupuestos.end(); i++) {
			if(i->getid() == p->getid()) break;
		}
		listaPresupuestos.erase(i);
		return true;
	}
	return false;
}

bool CapaNegocio::borrarCliente(Cliente *c) {
	if (accesoADatos->eliminarCliente(*c)) {
		list<Cliente>::iterator i;
		for (i = listaClientes.begin(); i != listaClientes.end(); i++) {
			if(i->getid() == c->getid()) break;
		}
		//listaClientes.erase(i);
		i->sethistorico(true);
		return true;
	}
	return false;

}

bool CapaNegocio::borrarArticulo(Articulo *a) {
	if (accesoADatos->eliminarArticulo(*a)) {
		list<Articulo>::iterator i;
		for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) {
			if(i->getid() == a->getid()) break;
		}
		//listaArticulos.erase(i);
		i->sethistorico(true);
		return true;
	}
	return false;

}

int CapaNegocio::getTotalArticulos() {
	list<Articulo>::iterator i;
	int c = 0;
	for (i = listaArticulos.begin(); i != listaArticulos.end(); i++) 
		if (i->gethistorico() == false) c++;
	return c;
}
int CapaNegocio::getTotalClientes() {
	list<Cliente>::iterator i;
		int c = 0;
		for (i = listaClientes.begin(); i != listaClientes.end(); i++) 
			if (i->gethistorico() == false) c++;
		return c;
}
int CapaNegocio::getTotalFacturas() {
	return listaFacturas.size();
}
int CapaNegocio::getTotalPresupuestos() {
	return listaPresupuestos.size();
}

bool CapaNegocio::cambiarIva(int v) {
	if (accesoADatos->cambiarIva(v)) 
		return true;
	return false;
}

int CapaNegocio::obtenerIva() {
	return accesoADatos->obtenerIva();
}

int CapaNegocio::getUltimoCodigoFactura() {
	int anyo = QDate().currentDate().toString("yy").toInt();
	list<Factura>::iterator it = listaFacturas.begin();
	int max = 0;
	for (;it != listaFacturas.end(); it++) {
		if ((it->getn_factura() / 10000) == anyo ) {
			if (it->getn_factura() > max)
				max = it->getn_factura();
		}
	}
	return anyo*10000 + (max % 10000) + 1;
}
int CapaNegocio::getUltimoCodigoCliente() {
	list<Cliente>::iterator it = listaClientes.begin();
	int max = 0;
	for (;it != listaClientes.end(); it++) {
		if (it->gethistorico() == false && it->getcodigo() > max) {
			max = it->getcodigo();
		}
	}
	return max + 1;
}
int CapaNegocio::getUltimoCodigoPresupuesto() {
	list<Presupuesto>::iterator it = listaPresupuestos.begin();
	int max = 0;
	for (;it != listaPresupuestos.end(); it++) {
		if (it->getn_factura() > max) {
			max = it->getn_factura();
		}
	}
	return max + 1;
}

list<Cliente> CapaNegocio::getClientesRango(int del, int al){
	
	list<Cliente> l;
	
	if(del < 0 || al < 0 ){
		return l;
	}
	
	
	list<Cliente>::iterator it;

	for(it = listaClientes.begin(); it != listaClientes.end(); it++){
		int n = it->getcodigo();
		if(n >= del && n <= al){
			l.push_back(*it);
		}
	}
	return l;
}
