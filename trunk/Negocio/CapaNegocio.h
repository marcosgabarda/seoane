#ifndef CAPANEGOCIO_H_
#define CAPANEGOCIO_H_
#include "../Datos/AccesoADatos.h"
#include "Factura.h"
#include "Cliente.h"
#include "Presupuesto.h"
#include "Articulo.h"
#include <list>

class CapaNegocio
{
	AccesoADatos* accesoADatos;
	list <Factura> listaFacturas;
	list <Cliente> listaClientes;
	list <Presupuesto> listaPresupuestos;
	list <Articulo> listaArticulos;
public:
	CapaNegocio();

	void inicializar();
	
	bool modificarFactura(Factura *f);
	bool modificarCliente(Cliente *f);
	bool modificarPresupuesto(Presupuesto *p);
	bool modificarArticulo(Articulo *a);

	bool borrarFactura(Factura *f);
	bool borrarPresupuesto(Presupuesto *p);
	bool borrarCliente(Cliente *c);
	bool borrarArticulo(Articulo *a);

	bool nuevaFactura(Factura *f);
	bool nuevoCliente(Cliente *c);
	bool nuevoPresupuesto(Presupuesto *p);
	bool nuevoArticulo(Articulo *a);

	list<Articulo> getArticulos();
	Articulo *getArticuloId(int id);
	Articulo *getArticuloCodigo(int cod);
	Articulo *getArticuloDescripcionPvp(string des, double pvp);
	int getTotalArticulos();
	list<Factura> getFacturas();
	Factura *getFacturaId(int id);
	Factura *getFacturaNumero(int n);
	int getTotalFacturas();
	list<Cliente> getClientes();
	Cliente *getClienteId(int id);
	Cliente *getClienteCodigo(int cod);
	int getTotalClientes();
	list<Presupuesto> getPresupuestos();
	Presupuesto *getPresupuestoId(int id);
	Presupuesto *getPresupuestoNumero(int n);
	int getTotalPresupuestos();

	void verClientes();
	void verFacturas();
	void verArticulos();
	void verPresupuestos();

	bool cambiarIva(int v);
	int obtenerIva();
	
	list<pair<int, int> > getListaTelefonos();
	int getUltimoCodigoFactura();
	int getUltimoCodigoCliente();
	int getUltimoCodigoPresupuesto();
	
	list<Cliente> getClientesRango(int del, int al);
	
	virtual ~CapaNegocio();
};

#endif /*CAPANEGOCIO_H_*/
