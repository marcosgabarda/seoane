#include "LineaArticulo.h"
#include <iostream>

using namespace std;

LineaArticulo::LineaArticulo()
{
	cantidad = 0;
}

LineaArticulo::~LineaArticulo()
{
}

int LineaArticulo::getcantidad() {
	return cantidad;
}
Articulo LineaArticulo::getarticulo() {
	return articulo;
}
double LineaArticulo::getpreciototal() {
	if (articulo.getid() != -1) {
		return (articulo.getpvp() -(articulo.getpvp())*(articulo.getdescuento()/100.0))*cantidad ;
	}
	return 0;
}

void LineaArticulo::setcantidad(int c) {
	cantidad = c;
}
void LineaArticulo::setarticulo(Articulo a){
	articulo = a;
}
