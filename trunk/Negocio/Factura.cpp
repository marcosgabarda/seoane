#include "Factura.h"
#include "Articulo.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;

Factura::Factura()
{
	// Para que el puntero no este sin inicializar
	n_factura = -1;
	n_fabricacion = -1;
	cliente = 0;
	lugar_reparacion = 0;
	aparato = "";
	fecha ="";
	marca = "";
	modelo = "";
	averia = "";
	trabajo_realizado = "";
	tiempo_empleado = "";
	fecha_terminacion = "";
	observaciones = "";
	precio_materiales = 0.;
	precio_mano_obra = 0.;
	precio_desplazamiento = 0.;
	precio_transporte = 0.;


}

Factura::~Factura()
{
	//if(lugar_reparacion) delete lugar_reparacion;
}


int Factura::getid(){
	return id;
}

int Factura::getn_factura(){
	return n_factura;
}

string Factura::getfecha(){
	return fecha;
}

string Factura::getaparato(){
	return aparato;
}

string Factura::getmarca(){
	return marca;
}

string Factura::getmodelo(){
	return modelo;
}

int Factura::getn_fabricacion(){
	return n_fabricacion;
}

bool *Factura::getlugar_reparacion(){
	return lugar_reparacion;
}

Cliente *Factura::getcliente(){
	return cliente;
}
list<LineaArticulo> Factura::getlista_articulos() {
	return lista_articulos;
}
string Factura::getaveria() {
	return averia;
}
string Factura::gettrabajo_realizado() {
	return trabajo_realizado;
}
string Factura::gettiempo_empleado() {
	return tiempo_empleado;
}
string Factura::getfecha_terminacion() {
	return fecha_terminacion;
}
string Factura::getobservaciones() {
	return observaciones;
}
double Factura::getprecio_materiales() {
	return precio_materiales;
}
double Factura::getprecio_mano_obra() {
	return precio_mano_obra;
}
double Factura::getprecio_desplazamiento() {
	return precio_desplazamiento;
}
double Factura::getprecio_transporte() {
	return precio_transporte;
}
double Factura::getiva() {
	return iva;
}
//Metodos set
void Factura::setid(int iden){
	id=iden;
}

void Factura::setn_factura(int n_fact){
	n_factura=n_fact;
}

void Factura::setfecha(string fec){
	fecha=fec;
}

void Factura::setaparato(string aparat){
	aparato=aparat;
}

void Factura::setmarca(string marc){
	marca=marc;
}

void Factura::setmodelo(string mod){
	modelo=mod;
}

void Factura::setn_fabricacion(int n_fabric){
	n_fabricacion=n_fabric;
}

void Factura::setlugar_reparacion(bool *lugar){
	lugar_reparacion=lugar;
}

void Factura::setcliente(Cliente *cli){
	cliente=cli;
}
void Factura::setlista_articulos(list<LineaArticulo> l) {
	lista_articulos = l;
}
void Factura::setaveria(string a) {
	averia = a;
}
void Factura::settrabajo_realizado(string t) {
	trabajo_realizado = t;
}
void Factura::settiempo_empleado(string t) {
	tiempo_empleado = t;
}
void Factura::setfecha_terminacion(string f) {
	fecha_terminacion = f;
}
void Factura::setobservaciones(string o) {
	observaciones = o;
}
void Factura::setprecio_materiales(double p) {
	precio_materiales = p;
}
void Factura::setprecio_mano_obra(double p) {
	precio_mano_obra = p;
}
void Factura::setprecio_desplazamiento(double p) {
	precio_desplazamiento = p;
}
void Factura::setprecio_transporte(double p) {
	precio_transporte = p;
}

void Factura::addArticulo(LineaArticulo la) {
	lista_articulos.push_back(la);
}

void Factura::setiva(double i) {
	iva = i;
}
void Factura::addArticulo(Articulo a, int c) {
	LineaArticulo la;
	la.setarticulo(a);
	la.setcantidad(c);
	lista_articulos.push_back(la);
}
bool Factura::eliminarArticulo(Articulo a) {
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		cout << (*i).getarticulo().getid()<< endl;
		if ((*i).getarticulo().getid() == a.getid()) {
			lista_articulos.erase(i);
			return true;
		}
	}
	return false;
}

bool Factura::modificarArticulo(Articulo a, int c) {
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		if ((*i).getarticulo().getid() == a.getid()) {
			(*i).setarticulo(a);
			(*i).setcantidad(c);
			return true;
		}
	}
	return false;
}
bool Factura::modificarArticulo(LineaArticulo la) {
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		if ((*i).getarticulo().getid() == la.getarticulo().getid()) {
			list<LineaArticulo>::iterator newpos = lista_articulos.erase(i);
			lista_articulos.insert(newpos,la);
			return true;
		}
	}
	return false;

}
//sobrecarga del operador =
Factura Factura::operator=(Factura f){
	if (&f != this) {
		id = f.getid();
		n_factura = f.getn_factura();
		fecha = f.getfecha();
		aparato = f.getaparato();
		marca = f.getmarca();
		modelo = f.getmodelo();
		n_fabricacion = f.getn_fabricacion();
		setlugar_reparacion(f.getlugar_reparacion());
		cliente = f.getcliente();
		lista_articulos = f.getlista_articulos();
		averia = f.getaveria();
		trabajo_realizado = f.gettrabajo_realizado();
		tiempo_empleado = f.gettiempo_empleado();
		fecha_terminacion = f.getfecha_terminacion();
		observaciones = f.getobservaciones();
		precio_materiales = f.getprecio_materiales();
		precio_mano_obra =  f.getprecio_mano_obra();
		precio_desplazamiento = f.getprecio_desplazamiento();
		precio_transporte = f.getprecio_transporte();
		iva = f.getiva();
	}
	return (*this);
}
double Factura::getMateriales () {
	double s = 0.0;
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		s += i->getpreciototal();
	}
	return s;
}
double Factura::getSubTotal(){
	return getMateriales() + getprecio_mano_obra() + getprecio_desplazamiento() + getprecio_transporte();
}
double Factura::getTotal(){
	double total = getSubTotal();
	return total + (iva / 100.0) * total; 
}

