#ifndef ARTICULO_H_
#define ARTICULO_H_
#include <string>
using namespace std;

class Articulo
{

private:
	int id;
	int codigo;
	string descripcion;
	string caja;
	int existencias;
	int existencias_minimas;
	double pvp;
	double precio_coste;
	int descuento;
	bool historico;

public:
	Articulo();
	virtual ~Articulo();

	//metodos get
	int getid();
	int getcodigo();
	string getdescripcion();
	string getcaja();
	int getexistencias();
	int getexistencias_minimas();
	double getpvp();
	double getprecio_coste();
	int getdescuento();
	bool gethistorico();

	//metodos set
	void setid(int id);
	void setcodigo(int codigo);
	void setdescripcion(string descripcion);
	void setcaja(string caja);
	void setexistencias(int existencias);
	void setexistencias_minimas(int existencias_minimas);
	void setpvp(double pvp);
	void setprecio_coste(double precio_coste);
	void setdescuento(int descuento);
	void sethistorico(bool h);

	//sobrecarga de operador igual
	Articulo operator=(Articulo a);

};

#endif /*ARTICULO_H_*/
