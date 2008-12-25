#ifndef CRITERIOBUSQUEDA_H_
#define CRITERIOBUSQUEDA_H_

#include <QDate>
#include <QString>

class CriterioBusqueda
{	
public:
	CriterioBusqueda();
	CriterioBusqueda(QDate *fi, QDate *ff, QString *c, int *n, int *t);
	virtual ~CriterioBusqueda();

	QDate *fechaInicio;
	QDate *fechaFin;
	QString *cliente;
	int *numero;
	int *telefono;
	
	QString *nombreCliente;
	QString *direccionCliente;
	int *codigoCliente;

	QString *descripcionArticulo;
	int *codigoArticulo;
	
};

#endif /*CRITERIOBUSQUEDA_H_*/
