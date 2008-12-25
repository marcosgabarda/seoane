#include "CriterioBusqueda.h"

#include <QDate>
#include <QString>

CriterioBusqueda::CriterioBusqueda()
{
	fechaFin = 0;
	fechaInicio = 0;
	numero = 0;
	cliente = 0;
	nombreCliente = 0;
	direccionCliente = 0;
	codigoCliente = 0;
	codigoArticulo =0;
	descripcionArticulo = 0;
	telefono = 0;
}

CriterioBusqueda::CriterioBusqueda(QDate *fi, QDate *ff, QString *c, int *n, int *t) : 
	fechaInicio(fi), 
	fechaFin(ff), 
	cliente(c), 
	numero(n), 
	telefono(t)
{
}

CriterioBusqueda::~CriterioBusqueda()
{
}
