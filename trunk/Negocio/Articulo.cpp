#include "Articulo.h"
#include <string>
using namespace std;
Articulo::Articulo()
{
	codigo = -1;
	existencias = -1;
	existencias_minimas = -1;
	descuento = 0;
	pvp = -1.;
	precio_coste = -1.;
	descripcion = "";
	caja = "";
	historico = false;
}

Articulo::~Articulo()
{
}

//metodos get
int Articulo::getid(){
	return id;
}

int Articulo::getcodigo(){
	return codigo;
}

string Articulo::getdescripcion(){
	return descripcion;
}

string Articulo::getcaja(){
	return caja;
}

int Articulo::getexistencias(){
	return existencias;
}

int Articulo::getexistencias_minimas(){
	return existencias_minimas;
}

double Articulo::getpvp(){
	return pvp;
}

double  Articulo::getprecio_coste(){
	return precio_coste;
}

int Articulo::getdescuento(){
	return descuento;
}
bool Articulo::gethistorico() {
	return historico;
}

//metodos set

void Articulo::setid(int iden){
	id=iden;
}


void Articulo::setcodigo(int cod){
	codigo=cod;
}

void Articulo::setdescripcion(string descr){
	descripcion=descr;
}

void Articulo::setcaja(string caj){
	caja=caj;
}
void Articulo::setexistencias(int exis){
	existencias=exis;
}

void Articulo::setexistencias_minimas(int exis_min){
	existencias_minimas=exis_min;
}

void Articulo::setpvp(double pvppub){
	pvp=pvppub;
}

void Articulo::setprecio_coste(double precio_cos){
	precio_coste=precio_cos;
}

void Articulo::setdescuento(int desc){
	descuento=desc;
}

void Articulo::sethistorico(bool h) {
	historico = h;
}

Articulo Articulo::operator=(Articulo a) {
	if (this != &a) {
		this->id = a.getid();
		this->caja = a.getcaja();
		this->codigo = a.getcodigo();
		this->descripcion = a.getdescripcion();
		this->descuento = a.getdescuento();
		this->existencias = a.getexistencias();
		this->existencias_minimas = a.getexistencias_minimas();
		this->historico = a.gethistorico();
		this->precio_coste = a.getprecio_coste();
		this->pvp = a.getpvp();
	}
	return *this;
}
