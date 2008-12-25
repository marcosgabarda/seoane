#ifndef PRESUPUESTO_H_
#define PRESUPUESTO_H_
#include "Factura.h"
#include <iostream>
#include <string>

using namespace std;

class Presupuesto
{

private:
	int id;
	bool *aceptado;
	Cliente* cliente;
	Factura* factura;
	int n_factura;
	string fecha;
	string aparato;
	string marca;
	string modelo;
	int n_fabricacion;
	bool *lugar_reparacion;
	list <LineaArticulo> lista_articulos;
	string averia;
	string trabajo_realizado;
	string tiempo_empleado;
	string fecha_terminacion;
	string observaciones;
	double precio_materiales;
	double precio_mano_obra;
	double precio_desplazamiento;
	double precio_transporte;
	double iva;

public:
	Presupuesto();
	virtual ~Presupuesto();

	//Metodos get
	int getid();
	bool *getaceptado();
	Cliente* getcliente();
	Factura* getfactura();
	int getn_factura();
	string getfecha();
	string getaparato();
	string getmarca();
	string getmodelo();
	int getn_fabricacion();
	bool *getlugar_reparacion();
	list<LineaArticulo> getlista_articulos();
	string getaveria();
	string gettrabajo_realizado();
	string gettiempo_empleado();
	string getfecha_terminacion();
	string getobservaciones();
	double getprecio_materiales();
	double getprecio_mano_obra();
	double getprecio_desplazamiento();
	double getprecio_transporte();
	double getiva();

	//Metodos set

	void setid(int id);
	void setaceptado(bool aceptado);
	void setcliente(Cliente* cliente);
	void setfactura(Factura* factura);
	void setn_factura(int n_factura);
	void setfecha(string fecha);
	void setaparato(string aparato);
	void setmarca(string marca);
	void setmodelo(string modelo);
	void setn_fabricacion(int n_fabricacion);
	void setlugar_reparacion(bool *lugar_reparacion);
	void setlista_articulos(list <LineaArticulo> l);
	void setaveria(string a);
	void settrabajo_realizado(string t);
	void settiempo_empleado(string t);
	void setfecha_terminacion(string f);
	void setobservaciones(string o);
	void setprecio_materiales(double p);
	void setprecio_mano_obra(double p);
	void setprecio_desplazamiento(double p);
	void setprecio_transporte(double p);
	void setiva(double i);

	//metodos para la lista de articulos
	void addArticulo(LineaArticulo la);
	void addArticulo(Articulo a, int c);
	bool eliminarArticulo(Articulo a);
	bool modificarArticulo(Articulo a, int c);
	bool modificarArticulo(LineaArticulo la);

	

	double getMateriales ();
	double getSubTotal();
	double getTotal();
	
	//sobrecrga del operador =
	Presupuesto operator=(Presupuesto p);
};

#endif /*PRESUPUESTO_H_*/
