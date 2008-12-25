#include "Cliente.h"
#include <string>
using namespace std;

Cliente::Cliente()
{
nombre = "";
apellidos="";
direccion="";
poblacion="";
nif="";
codigo = -1;
historico = false;
}

Cliente::~Cliente()
{
}
//metodos get

int  Cliente::getid(){
	return id;
}

int Cliente::getcodigo(){
	return codigo;
}

string Cliente::getnombre(){
	return nombre;
}

string Cliente::getapellidos(){
	return apellidos;
}

string Cliente::getdireccion(){
	return direccion;
}

string Cliente::getnif(){
	return nif;
}

string Cliente::getpoblacion(){
	return poblacion;
}

bool Cliente::gethistorico() {
	return historico;
}

list<int> Cliente::gettelefonos() {
	return telefonos;
}

//metodos set

void Cliente::setid(int ident){
	id=ident;
}

void Cliente::setcodigo(int cod){
	codigo=cod;
}

void Cliente::setnombre(string nom){
	nombre=nom;
}

void Cliente::setapellidos(string apell){
	apellidos=apell;
}

void Cliente::setdireccion(string dir){
	direccion=dir;
}

void Cliente::setnif(string ni){
	nif=ni;
}

void Cliente::setpoblacion(string pob){
	poblacion=pob;
}

void Cliente::sethistorico(bool h) {
	historico = h;
}

void Cliente::settelefonos(list<int> t) {
	telefonos = t;
}

//sobrecarga del operador =

Cliente Cliente::operator=(Cliente c){

	if (this != &c) {
		this->id = c.getid();
		this->codigo = c.getcodigo();
		this->nombre = c.getnombre();
		this->apellidos = c.getapellidos();
		this->direccion = c.getdireccion();
		this->nif = c.getnif();
		this->poblacion = c.getpoblacion();
		this->historico = c.gethistorico();
		this->telefonos = c.gettelefonos();
	}
	return *this;
}
