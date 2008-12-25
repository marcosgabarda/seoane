#ifndef ACCESOADATOS_H_
#define ACCESOADATOS_H_
#include "../Negocio/Factura.h"
#include "../Negocio/Articulo.h"
#include "../Negocio/Cliente.h"
#include "../Negocio/Presupuesto.h"
#include <list>
#include <QtSql>

class AccesoADatos
{

private:
	QSqlDatabase db; //puntero a base de datos

public:
	AccesoADatos();
	virtual ~AccesoADatos();
	bool insertaFactura(Factura factura);
	bool insertaCliente(Cliente cliente);
	bool insertaArticulo(Articulo articulo);
	bool insertaPresupuesto(Presupuesto presupuesto);
	list <Factura> listaFacturas();
	list <Cliente> listaClientes();
	list <Articulo> listaArticulos();
	list <Presupuesto> listaPresupuestos();
	int enlazaCliente(int idf);
	int enlazaFactura(int idp);
	int enlazaClienteP(int idp);
	bool actualizaFactura(Factura f);
	int getCantidadArticuloFactura(Factura *f, Articulo *a);
	list<int> getListaIdArticulos(Factura *f);
	bool actualizaPresupuesto(Presupuesto p);
	bool actualizaArticulo(Articulo a);
	bool actualizaCliente(Cliente c);
	bool eliminarFactura(Factura f);
	bool eliminarPresupuesto(Presupuesto p);
	bool eliminarArticulo(Articulo a);
	bool eliminarCliente(Cliente c);

	//Devuelve el identificador siguiente del máximo
	int dameIdFactura();
	int dameIdCliente();
	int dameIdPresupuesto();
	int dameIdArticulo();
	
	bool cambiarIva(int v);
	int obtenerIva();
	
	list <pair<int, int> > getListaTelefonos();

};

#endif /*ACCESOADATOS_H_*/
