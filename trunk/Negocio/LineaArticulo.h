#ifndef LINEAARTICULO_H_
#define LINEAARTICULO_H_
#include "Articulo.h"

class LineaArticulo
{
private:
	int cantidad;
	Articulo articulo;
public:
	LineaArticulo();
	virtual ~LineaArticulo();

	int getcantidad();
	Articulo getarticulo();
	double getpreciototal();

	void setcantidad(int c);
	void setarticulo(Articulo a);

};

#endif /*LINEAARTICULO_H_*/
