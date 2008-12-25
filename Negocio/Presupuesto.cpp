#include "Presupuesto.h"
#include <string>

Presupuesto::Presupuesto()
{
	n_factura = -1;
	n_fabricacion = -1;
	fecha = "";
	aparato = "";
	marca = "";
	modelo = "";
	aceptado = 0;
	lugar_reparacion = 0;
	cliente = 0;
	factura = 0;
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

Presupuesto::~Presupuesto()
{
	//if(aceptado) delete aceptado;
	//if(lugar_reparacion) delete lugar_reparacion;
}

//Metodos get

int Presupuesto::getid(){
	return id;
}

bool* Presupuesto::getaceptado(){
	return aceptado;
}

Cliente* Presupuesto::getcliente(){
	return cliente;
}

Factura* Presupuesto::getfactura(){
	return factura;
}

int Presupuesto::getn_factura(){
	return n_factura;
}

string Presupuesto::getfecha(){
	return fecha;
}

string Presupuesto::getaparato(){
	return aparato;
}

string Presupuesto::getmarca(){
	return marca;
}

string Presupuesto::getmodelo(){
	return modelo;
}

int Presupuesto::getn_fabricacion(){
	return n_fabricacion;
}

bool *Presupuesto::getlugar_reparacion(){
	return lugar_reparacion;
}
list<LineaArticulo> Presupuesto::getlista_articulos() {
	return lista_articulos;
}
string Presupuesto::getaveria() {
	return averia;
}
string Presupuesto::gettrabajo_realizado() {
	return trabajo_realizado;
}
string Presupuesto::gettiempo_empleado() {
	return tiempo_empleado;
}
string Presupuesto::getfecha_terminacion() {
	return fecha_terminacion;
}
string Presupuesto::getobservaciones() {
	return observaciones;
}
double Presupuesto::getprecio_materiales() {
	return precio_materiales;
}
double Presupuesto::getprecio_mano_obra() {
	return precio_mano_obra;
}
double Presupuesto::getprecio_desplazamiento() {
	return precio_desplazamiento;
}
double Presupuesto::getprecio_transporte() {
	return precio_transporte;
}
double Presupuesto::getiva() {
	return iva;
}
//Metodos set
void Presupuesto::setid(int iden){
	id=iden;
}

void Presupuesto::setaceptado(bool acep){
	if(!aceptado) aceptado = new bool;
	*aceptado=acep;
}

void Presupuesto::setcliente(Cliente *c){
	cliente=c;
}

void Presupuesto::setfactura(Factura *fact){
	factura=fact;
}

void Presupuesto::setn_factura(int n_fact){
	n_factura=n_fact;
}

void Presupuesto::setfecha(string fech){
	fecha=fech;
}

void Presupuesto::setaparato(string apar){
	aparato=apar;
}

void Presupuesto::setmarca(string marc){
	marca=marc;
}

void Presupuesto::setmodelo(string mod){
	modelo=mod;
}

void Presupuesto::setn_fabricacion(int n_fab){
	n_fabricacion=n_fab;
}

void Presupuesto::setlugar_reparacion(bool *lugar){
	lugar_reparacion=lugar;
}

void Presupuesto::setlista_articulos(list<LineaArticulo> l) {
	lista_articulos = l;
}
void Presupuesto::setaveria(string a) {
	averia = a;
}
void Presupuesto::settrabajo_realizado(string t) {
	trabajo_realizado = t;
}
void Presupuesto::settiempo_empleado(string t) {
	tiempo_empleado = t;
}
void Presupuesto::setfecha_terminacion(string f) {
	fecha_terminacion = f;
}
void Presupuesto::setobservaciones(string o) {
	observaciones = o;
}
void Presupuesto::setprecio_materiales(double p) {
	precio_materiales = p;
}
void Presupuesto::setprecio_mano_obra(double p) {
	precio_mano_obra = p;
}
void Presupuesto::setprecio_desplazamiento(double p) {
	precio_desplazamiento = p;
}
void Presupuesto::setprecio_transporte(double p) {
	precio_transporte = p;
}
void Presupuesto::setiva(double i) {
	iva = i;
}
void Presupuesto::addArticulo(LineaArticulo la) {
	lista_articulos.push_back(la);
}
void Presupuesto::addArticulo(Articulo a, int c) {
	LineaArticulo la;
	la.setarticulo(a);
	la.setcantidad(c);
	lista_articulos.push_back(la);
}
bool Presupuesto::eliminarArticulo(Articulo a) {
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		if ((*i).getarticulo().getid() == a.getid()) {
			lista_articulos.erase(i);
			return true;
		}
	}
	return false;
}

bool Presupuesto::modificarArticulo(Articulo a, int c) {
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
bool Presupuesto::modificarArticulo(LineaArticulo la) {
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
Presupuesto Presupuesto::operator=(Presupuesto p){
	if (&p != this) {
		id = p.getid();
		n_factura = p.getn_factura();
		fecha = p.getfecha();
		aparato = p.getaparato();
		marca =p.getmarca();
		modelo = p.getmodelo();
		n_fabricacion = p.getn_fabricacion();
		setlugar_reparacion(p.getlugar_reparacion());
		setcliente(p.getcliente());
		lista_articulos = p.getlista_articulos();
		setaceptado(p.getaceptado());
		setfactura(p.getfactura());
		setiva(p.getiva());
		averia = p.getaveria();
		trabajo_realizado = p.gettrabajo_realizado();
		tiempo_empleado = p.gettiempo_empleado();
		fecha_terminacion = p.getfecha_terminacion();
		observaciones = p.getobservaciones();
		precio_materiales = p.getprecio_materiales();
		precio_mano_obra =  p.getprecio_mano_obra();
		precio_desplazamiento = p.getprecio_desplazamiento();
		precio_transporte = p.getprecio_transporte();

	}
	return (*this);
}
double Presupuesto::getMateriales () {
	double s = 0.0;
	list<LineaArticulo>::iterator i;
	for (i=lista_articulos.begin(); i != lista_articulos.end(); i++) {
		s += i->getpreciototal();
	}
	return s;
}
double Presupuesto::getSubTotal(){
	return getMateriales() + getprecio_mano_obra() + getprecio_desplazamiento() + getprecio_transporte();
}
double Presupuesto::getTotal(){
	double total = getSubTotal();
	return total + (iva / 100.0) * total; 
}

