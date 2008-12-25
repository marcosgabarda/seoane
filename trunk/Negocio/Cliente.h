#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <string>
#include <list>
using namespace std;

class Cliente
{
private:
	int id;
	int codigo;
	string nombre;
	string apellidos;
	string direccion;
	string nif;
	string poblacion;
	bool historico;
	list<int> telefonos;

public:
	Cliente();
	virtual ~Cliente();

	//metodos get
    int getid();
    int getcodigo();
	string getnombre();
	string getapellidos();
	string getdireccion();
	string getnif();
	string getpoblacion();
	bool gethistorico();
	list<int> gettelefonos();
	
	//metodos set
	void setid(int id);
	void setcodigo(int codigo);
	void setnombre(string nombre);
	void setapellidos(string apellidos);
	void setdireccion(string direccion);
	void setnif(string nif);
	void setpoblacion(string poblacion);
	void sethistorico(bool h);
	void settelefonos(list<int> t);

	//sobrecarga de operador igual
	Cliente operator=(Cliente c);

};

#endif /*CLIENTE_H_*/
