#include "AccesoADatos.h"
#include "utils.h"
#include "../Negocio/Factura.h"
#include "../Negocio/Cliente.h"
#include "../Negocio/Presupuesto.h"
#include "../Negocio/Articulo.h"
#include <cstdio>
#include <string>
#include <list>
#include <iostream>
#include <QtSql>
#include <QString>
#include <QtGui>

using namespace std;

AccesoADatos::AccesoADatos()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./Datos/seoane.s3db");
    bool ok = db.open();
    if (ok) {
    	cout << "[Debug]Base de datos abierta correctamente." << endl;
    } else {
    	cout << "[ERROR]Base de datos abierta incorrectamente." << endl;
    	QMessageBox::information(0,"Error","Error al acceder a la base de datos.");
    	qDebug()<< db.lastError();
    }
}

AccesoADatos::~AccesoADatos()
{
	cout << "[Debug]Destruimos el acceso a datos." << endl;
	db.close();
	cout << "[Debug]Acceso a datos destruida." << endl;
}
//METODOS  PARA INSERTAR EN LA BD
bool AccesoADatos::insertaFactura(Factura factura){
	db.transaction();
//insert into facturas(n_factura, fecha, aparato, marca, modelo,n_fabricacion,lugar_reparacion,id_cliente);
	string query="insert into Facturas(n_factura, fecha, aparato, marca, modelo,n_fabricacion,lugar_reparacion,id_cliente,averia,trabajo_realizado,tiempo_empleado,fecha_terminacion,observaciones,precio_materiales,precio_mano_obra,precio_desplazamiento,precio_transporte,iva) values (";//
	if(factura.getn_factura()==-1)
		query.append("NULL, ");
	else {
		query.append(itoa(factura.getn_factura()));
		query.append(", ");
	}
	if(factura.getfecha() == "")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append( factura.getfecha() + "\", ");
	}
	if(factura.getaparato()== "")
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append(factura.getaparato() + "\", ");
		}


	if(factura.getmarca()== "")
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append(factura.getmarca() + "\", ");
		}
	if(factura.getmodelo()== "")
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append(factura.getmodelo() + "\", ");
		}
	if(factura.getn_fabricacion()== -1)
			query.append("NULL, ");
	else {
		query.append(itoa(factura.getn_fabricacion()));
		query.append(", ");
	}
	if(factura.getlugar_reparacion()== 0)
			query.append("NULL, ");
		else {
			bool lr = *factura.getlugar_reparacion();
			if (lr) query.append("1, ");
			else query.append("0, ");
		}


	if(factura.getcliente() == 0)
			query.append("NULL, ");
		else {
			query.append(itoa(factura.getcliente()->getid()));
			query.append(", ");
		}
	if(factura.getaveria() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(factura.getaveria() + "\", ");

	}
	if(factura.gettrabajo_realizado() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(factura.gettrabajo_realizado() + "\", ");
	}
	if(factura.gettiempo_empleado() == "") {
			query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(factura.gettiempo_empleado() + "\", ");
	}
	if(factura.getfecha_terminacion() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(factura.getfecha_terminacion() + "\", ");
	}
	if(factura.getobservaciones() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(factura.getobservaciones() + "\", ");
	}
	if(factura.getprecio_materiales() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(factura.getprecio_materiales()));
		query.append(", ");
	}
	if(factura.getprecio_mano_obra() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(factura.getprecio_mano_obra()));
		query.append(", ");
	}
	if(factura.getprecio_desplazamiento() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(factura.getprecio_desplazamiento()));
		query.append(", ");
	}
	if(factura.getprecio_transporte() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(factura.getprecio_transporte()));
		query.append(", ");
	}
	query.append(ftoa(factura.getiva()));
	query.append(");");
	
	cout << query << endl;
	QSqlQuery qquery;
	bool ok = qquery.exec(query.c_str());

	list<LineaArticulo> l = factura.getlista_articulos();
	list<LineaArticulo>::iterator iter;
	for(iter=l.begin(); iter!=l.end();iter++) {
		query = " insert into Facturas_Articulos(id_factura, id_articulo, cantidad) values(";
		query.append(itoa(factura.getid()));
		query.append(", ");
		query.append(itoa(iter->getarticulo().getid()));
		query.append(", ");
		query.append(itoa(iter->getcantidad()));
		query.append(");");
		ok = ok && qquery.exec(query.c_str());
	}
	ok = ok && db.commit();
	return ok;
}

/////////////////////////////////
bool AccesoADatos::insertaCliente(Cliente cliente){
	db.transaction();
//insert into cliente(codigo,nombre,apellidos,direccion,nif,poblacion) values (";
	string query="insert into Clientes(codigo,nombre,apellidos,direccion,nif,poblacion) values(";//

	if(cliente.getcodigo() == 0)
		query.append("NULL, ");
	else {
		query.append(itoa(cliente.getcodigo()));
		query.append(", ");
	}

	if(cliente.getnombre() == "")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getnombre() + "\", ");
	}

	if(cliente.getapellidos() == "")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getapellidos() + "\", ");
	}

	if(cliente.getdireccion()=="")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getdireccion() + "\", " );
	}

	if(cliente.getnif()=="")
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append( cliente.getnif() + "\", ");
		}
	if(cliente.getpoblacion()=="")
			query.append("NULL);");
		else {
			query.append("\"");
			query.append( cliente.getpoblacion() + "\");");
		}

	cout << "[Debug]" << query << endl;
	QSqlQuery qquery;
	bool ok = qquery.exec(query.c_str());
	
	list<int> lista = cliente.gettelefonos();
	list<int>::iterator it;
	for (it = lista.begin(); it != lista.end(); it++){
		string queryTelefonos="insert into Telefonos(id_cliente,numero) values(";
		queryTelefonos.append(itoa(dameIdCliente()));
		queryTelefonos.append(", ");
		queryTelefonos.append(itoa(*it));
		queryTelefonos.append(");");
		cout << "[Debug]" << queryTelefonos << endl;
		QSqlQuery qqueryt;
		ok = ok && qqueryt.exec(queryTelefonos.c_str());
	}
	ok = ok && db.commit();
	return ok;
}

/////////////////////////////////////////////////
bool AccesoADatos::insertaPresupuesto(Presupuesto presupuesto){
	db.transaction();
//insert into Presupuesto(aceptado,id_cliente,factura,n_factura,fecha,aparato,marca,modelo,n_fabricacion,lugar_reparacion);
	string query="insert into Presupuestos(aceptado,id_cliente,id_factura,n_factura,fecha,aparato,marca,modelo,n_fabricacion,lugar_reparacion,averia,trabajo_realizado,tiempo_empleado,fecha_terminacion,observaciones,precio_materiales,precio_mano_obra,precio_desplazamiento,precio_transporte,iva) values (";

	if(presupuesto.getaceptado()==0)
		query.append("NULL, ");
	else {
		bool a = *presupuesto.getaceptado();
		if (a) query.append("1, ");
		else query.append("0, ");
	}

	if(presupuesto.getcliente()==0)
		query.append("NULL, ");
	else {
		query.append(itoa(presupuesto.getcliente()->getid()));
		query.append(", ");
	}

	if(presupuesto.getfactura()==0)
		   query.append("NULL, ");
		else {
			query.append(itoa(presupuesto.getfactura()->getid()));
			query.append(", ");
		}

	if(presupuesto.getn_factura()==-1)
			query.append("NULL, ");
		else {
			query.append(itoa(presupuesto.getn_factura()));
			query.append(", ");
		}

	if(presupuesto.getfecha()=="")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(presupuesto.getfecha() + "\", ");
	}

	if(presupuesto.getaparato()=="")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(presupuesto.getaparato() + "\", ");
	}

	if(presupuesto.getmarca()=="")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(presupuesto.getmarca() + "\", ");
	}

	if(presupuesto.getmodelo()=="")
			query.append("NULL, ");
	else {
		query.append("\"");
		query.append(presupuesto.getmodelo() + "\", ");
	}

	if(presupuesto.getn_fabricacion()==-1)
			query.append("NULL, ");
	else {
		query.append(itoa(presupuesto.getn_fabricacion()));
		query.append(", ");
	}

	if(presupuesto.getlugar_reparacion()==0)
		query.append("NULL, ");
	else {
		bool lr = presupuesto.getlugar_reparacion();
		if (lr) query.append("1, ");
		else query.append("0, ");
	}
	if(presupuesto.getaveria() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(presupuesto.getaveria() + "\", ");

	}
	if(presupuesto.gettrabajo_realizado() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(presupuesto.gettrabajo_realizado() + "\", ");
	}
	if(presupuesto.gettiempo_empleado() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(presupuesto.gettiempo_empleado() + "\", ");
	}
	if(presupuesto.getfecha_terminacion() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(presupuesto.getfecha_terminacion() + "\", ");
	}
	if(presupuesto.getobservaciones() == "") {
		query.append("NULL, ");
	} else {
		query.append("\"");
		query.append(presupuesto.getobservaciones() + "\", ");
	}
	if(presupuesto.getprecio_materiales() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(presupuesto.getprecio_materiales()));
		query.append(", ");
	}
	if(presupuesto.getprecio_mano_obra() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(presupuesto.getprecio_mano_obra()));
		query.append(", ");
	}
	if(presupuesto.getprecio_desplazamiento() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(presupuesto.getprecio_desplazamiento()));
		query.append(", ");
	}
	if(presupuesto.getprecio_transporte() == -1.) {
		query.append("NULL, ");
	} else {
		query.append(ftoa(presupuesto.getprecio_transporte()));
		query.append(", ");
	}
	query.append(ftoa(presupuesto.getiva()));
	query.append(");");
	QSqlQuery qquery;
	//QMessageBox::information(0,"Aviso",query.c_str());
	bool ok = qquery.exec(query.c_str());

	list<LineaArticulo> l = presupuesto.getlista_articulos();
	list<LineaArticulo>::iterator iter;
	for(iter=l.begin(); iter!=l.end();iter++) {
		query = " insert into Presupuestos_Articulos(id_presupuesto, id_articulo, cantidad) values(";
		query.append(itoa(presupuesto.getid()));
		query.append(", ");
		query.append(itoa(iter->getarticulo().getid()));
		query.append(", ");
		query.append(itoa(iter->getcantidad()));
		query.append(");");
		ok = ok && qquery.exec(query.c_str());
	}
	ok = ok && db.commit();
	return ok;
}
bool AccesoADatos::insertaArticulo(Articulo articulo){

	//insert into Articulos(codigo,descripcion,caja,existencias,existencias_minimas,pvp,precio_coste,descuento);
		string query="insert into Articulos(codigo,descripcion,caja,existencias,existencias_minimas,pvp,precio_coste,descuento,historico) values (";

		if(articulo.getcodigo() == -1)
			query.append("NULL, ");
		else {
			query.append(itoa(articulo.getcodigo()));
			query.append(", ");
		}

		if(articulo.getdescripcion() =="")
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append(articulo.getdescripcion() + "\", ");
		}
		if(articulo.getcaja() == "" )
			query.append("NULL, ");
		else {
			query.append("\"");
			query.append(articulo.getcaja() + "\", ");
		}
		if(articulo.getexistencias() == -1)
			query.append("NULL, ");
		else {
			query.append(itoa(articulo.getexistencias()));
			query.append(", ");
		}

		if(articulo.getexistencias_minimas() == -1)
			query.append("NULL, ");
		else {
			query.append(itoa(articulo.getexistencias_minimas()));
			query.append(", ");
		}
		if(articulo.getpvp() ==-1.)
			query.append("NULL, ");
		else {
			query.append(ftoa(articulo.getpvp()));
			query.append(", ");
		}

		if(articulo.getprecio_coste() == -1.)
			query.append("NULL, ");
		else {
            query.append(ftoa(articulo.getprecio_coste()));
            query.append(", ");

		}

		if(articulo.getdescuento() == -1)
			query.append("NULL, ");
		else {
			query.append(itoa(articulo.getdescuento()));
			query.append(", ");
		}
		
		if (articulo.gethistorico()) {
			query.append("1);");
		} else {
			query.append("0);");
		}

		cout << "[Debug]" << query << endl;
		QSqlQuery qquery;
		bool ok = qquery.exec(query.c_str());
		if (!ok) {
			qDebug() << qquery.lastError ();
			return false;
		}
		return true;


}
//METODOS PARA LISTAR

list <Factura> AccesoADatos::listaFacturas() {
	string squery = "select * from Facturas order by n_factura desc;";
	list <Factura> lista_facturas;
	QSqlQuery query;
	bool ok = query.exec(squery.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
			return lista_facturas;
	}
	while (query.next()) {
		Factura *f = new Factura();
		f->setid(query.value(0).toInt());
		f->setn_factura(query.value(1).toInt());
		f->setfecha(query.value(2).toString().toStdString());
		f->setaparato(query.value(3).toString().toStdString());
		f->setmarca(query.value(4).toString().toStdString());
		f->setmodelo(query.value(5).toString().toStdString());
		f->setn_fabricacion(query.value(6).toInt());
		
		if (!query.value(7).isNull()) {
			bool *b = new bool;
			*b = query.value(7).toBool();
			f->setlugar_reparacion(b);
		}
		f->setcliente(0);
		f->setaveria(query.value(9).toString().toStdString());
		f->settrabajo_realizado(query.value(10).toString().toStdString());
		f->settiempo_empleado(query.value(11).toString().toStdString());
		f->setfecha_terminacion(query.value(12).toString().toStdString());
		f->setobservaciones(query.value(13).toString().toStdString());
		f->setprecio_materiales(query.value(14).toDouble());
		f->setprecio_mano_obra(query.value(15).toDouble());
		f->setprecio_desplazamiento(query.value(16).toDouble());
		f->setprecio_transporte(query.value(17).toDouble());
		f->setiva(query.value(18).toDouble());
		
		lista_facturas.push_back(*f);
	}
	return lista_facturas;
}

list <Cliente> AccesoADatos::listaClientes() {
	string squery = "select * from Clientes;";
	list <Cliente> lista_clientes;
	QSqlQuery query;
	bool ok = query.exec(squery.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return lista_clientes;
	}	
	while (query.next()) {
		Cliente *c = new Cliente();
		c->setid(query.value(0).toInt());
		c->setcodigo(query.value(1).toInt());
		c->setnombre(query.value(2).toString().toStdString());
		c->setapellidos(query.value(3).toString().toStdString());
		c->setdireccion(query.value(4).toString().toStdString());
		c->setnif(query.value(5).toString().toStdString());
		c->setpoblacion(query.value(6).toString().toStdString());
		c->sethistorico(query.value(7).toBool());
		
		list<int> lista_telefonos;
		string tquery = "select numero from Telefonos where id_cliente=";
		tquery.append(itoa(c->getid()));
		tquery.append(";");
		QSqlQuery queryt;
		queryt.exec(tquery.c_str());
		while (queryt.next()) {
			lista_telefonos.push_back(queryt.value(0).toInt());
		}
		
		c->settelefonos(lista_telefonos);
		
		lista_clientes.push_back(*c);
	}
	
	
	return lista_clientes;
}

list <Presupuesto> AccesoADatos::listaPresupuestos() {
	string squery = "select * from Presupuestos;";
	list <Presupuesto> lista_presupuestos;
	QSqlQuery query;
	bool ok = query.exec(squery.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return lista_presupuestos;
	}
	while (query.next()) {
		Presupuesto *p = new Presupuesto();
		p->setid(query.value(0).toInt());
		p->setaceptado(query.value(1).toBool());// ATENCION!!!
		p->setcliente(0);
		p->setfactura(0);
		p->setn_factura(query.value(4).toInt());
		p->setfecha(query.value(5).toString().toStdString());
		p->setaparato(query.value(6).toString().toStdString());
		p->setmarca(query.value(7).toString().toStdString());
		p->setmodelo(query.value(8).toString().toStdString());
		p->setn_fabricacion(query.value(9).toInt());
		if (!query.value(10).isNull()) {
			bool *b = new bool;
			*b = query.value(10).toBool();
			p->setlugar_reparacion(b);
		}
		p->setaveria(query.value(11).toString().toStdString());
		p->settrabajo_realizado(query.value(12).toString().toStdString());
		p->settiempo_empleado(query.value(13).toString().toStdString());
		p->setfecha_terminacion(query.value(14).toString().toStdString());
		p->setobservaciones(query.value(15).toString().toStdString());
		p->setprecio_materiales(query.value(16).toDouble());
		p->setprecio_mano_obra(query.value(17).toDouble());
		p->setprecio_desplazamiento(query.value(18).toDouble());
		p->setprecio_transporte(query.value(19).toDouble());
		p->setiva(query.value(20).toDouble());
		lista_presupuestos.push_back(*p);
	}
	return lista_presupuestos;
}

list <Articulo> AccesoADatos::listaArticulos() {
	string squery = "select * from Articulos;";
			list <Articulo> lista_articulos;
			QSqlQuery query;
			bool ok = query.exec(squery.c_str());
			if (!ok) {
				qDebug() << query.lastError ();
					return lista_articulos;
			}
			while (query.next()) {
				Articulo *a = new Articulo();
				a->setid(query.value(0).toInt());
				a->setcodigo(query.value(1).toInt());
				a->setdescripcion(query.value(2).toString().toStdString());
				a->setcaja(query.value(3).toString().toStdString());
				a->setexistencias(query.value(4).toInt());
				a->setexistencias_minimas(query.value(5).toInt());
				a->setpvp(query.value(6).toDouble());//ATENCION!!
				a->setprecio_coste(query.value(7).toDouble()); //ATENCION!!
				a->setdescuento(query.value(8).toInt());
				a->sethistorico(query.value(9).toBool());

				lista_articulos.push_back(*a);
			}
			return lista_articulos;
		}

//METODOS DE ENLAZADO

//Esta funcion dado un id de factura devuelve el id de cliente aociado
int AccesoADatos::enlazaCliente(int idf) {
	string q("select id_cliente from Facturas where rowid=");
	q.append(itoa(idf));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
	}
	if (query.next())
		return query.value(0).toInt();
	return -1;
}

//Esta funcion dado un id de presupuesto devuelve el id de la factura aociada
int AccesoADatos::enlazaFactura(int idp) {
	string q("select id_factura from Presupuestos where rowid=");
	q.append(itoa(idp));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
	}
	if (query.next())
		return query.value(0).toInt();
	return -1;
}

int AccesoADatos::enlazaClienteP(int idp) {
	string q("select id_cliente from Presupuestos where rowid=");
	q.append(itoa(idp));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
		if (!ok) {
			qDebug() << query.lastError ();
		}
		if (query.next())
			return query.value(0).toInt();
		return -1;
}

int AccesoADatos::getCantidadArticuloFactura(Factura *f, Articulo *a) {
	string q("select cantidad from Facturas_Articulos where id_factura=");
	q.append(itoa(f->getid()));
	q.append(" and id_articulo=");
	q.append(itoa(a->getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
	}
	if (query.next())
		return query.value(0).toInt();
	return -1;
}
list<int> AccesoADatos::getListaIdArticulos(Factura *f) {
	list<int> l;
	string q("select id_articulo from Facturas_Articulos where id_factura=");
	q.append(itoa(f->getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
	}
	while (query.next()) {
		l.push_back(query.value(0).toInt());
	}
	return l;
}
/* Devuelve pares (nº telf, id cliente) */
list<pair<int, int> > AccesoADatos::getListaTelefonos() {	
	list<pair<int, int> > l;
	string q("select * from Telefonos T where (select id from Clientes C where T.id_cliente = C.id and C.historico=0);");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
	}
	while (query.next()) {
		l.push_back(pair<int, int>(query.value(1).toInt(), query.value(2).toInt()));
	}
	return l;
}

//METODOS PARA ACTUALIZAR
bool AccesoADatos::actualizaFactura(Factura factura) {
		db.transaction();
		string query="update Facturas set ";//
		if(factura.getn_factura()==-1)
			query.append("n_factura=NULL, ");
		else {
			string c("n_factura=");
			c.append(itoa(factura.getn_factura()));
			query.append(c + ", ");
		}
		if(factura.getfecha() == "")
			query.append("fecha=NULL, ");
		else
			query.append("fecha=\""+factura.getfecha() + "\", ");

		if(factura.getaparato()== "")
			query.append("aparato=NULL, ");
		else
			query.append("aparato=\""+factura.getaparato() + "\", ");

		if(factura.getmarca()== "")
			query.append("marca=NULL, ");
		else
			query.append("marca=\""+factura.getmarca() + "\", ");

		if(factura.getmodelo()== "")
			query.append("modelo=NULL, ");
		else
			query.append("modelo=\""+factura.getmodelo() + "\", ");

		if(factura.getn_fabricacion()== -1)
				query.append("n_fabricacion=NULL, ");
		else {
			string c("n_fabricacion=");
			c.append(itoa(factura.getn_fabricacion()));
			query.append( c + ", ");
		}
		if(factura.getlugar_reparacion()== 0)
				query.append("lugar_reparacion=NULL, ");
		else {
			bool lr = *factura.getlugar_reparacion();
			if (lr) query.append("lugar_reparacion=1, ");
			else query.append("lugar_reparacion=0, ");
		}


		if(factura.getcliente() == 0)
			query.append("id_cliente=NULL, ");
		else {
			string c("id_cliente=");
			c.append(itoa(factura.getcliente()->getid()));
			query.append(c + ", ");
		}
		if(factura.getaveria() == "") {
			query.append("averia=NULL, ");
		} else {
			query.append("averia=\"");
			query.append(factura.getaveria() + "\", ");

		}
		if(factura.gettrabajo_realizado() == "") {
			query.append("trabajo_realizado=NULL, ");
		} else {
			query.append("trabajo_realizado=\"");
			query.append(factura.gettrabajo_realizado() + "\", ");
		}
		if(factura.gettiempo_empleado() == "") {
				query.append("tiempo_empleado=NULL, ");
		} else {
			query.append("tiempo_empleado=\"");
			query.append(factura.gettiempo_empleado() + "\", ");
		}
		if(factura.getfecha_terminacion() == "") {
			query.append("fecha_terminacion=NULL, ");
		} else {
			query.append("fecha_terminacion=\"");
			query.append(factura.getfecha_terminacion() + "\", ");
		}
		if(factura.getobservaciones() == "") {
			query.append("observaciones=NULL, ");
		} else {
			query.append("observaciones=\"");
			query.append(factura.getobservaciones() + "\", ");
		}
		if(factura.getprecio_materiales() == -1.) {
			query.append("precio_materiales=NULL, ");
		} else {
			query.append("precio_materiales=");
			query.append(ftoa(factura.getprecio_materiales()));
			query.append(", ");
		}
		if(factura.getprecio_mano_obra() == -1.) {
			query.append("precio_mano_obra=NULL, ");
		} else {
			query.append("precio_mano_obra=");
			query.append(ftoa(factura.getprecio_mano_obra()));
			query.append(", ");
		}
		if(factura.getprecio_desplazamiento() == -1.) {
			query.append("precio_desplazamiento=NULL, ");
		} else {
			query.append("precio_desplazamiento=");
			query.append(ftoa(factura.getprecio_desplazamiento()));
			query.append(", ");		}
		if(factura.getprecio_transporte() == -1.) {
			query.append("precio_transporte=NULL ");
		} else {
			query.append("precio_transporte=");
			query.append(ftoa(factura.getprecio_transporte()));
			query.append(" ");
		}
		query.append("where rowid=");
		query.append(itoa(factura.getid()));
		query.append(";");

		QSqlQuery qquery;
		bool ok = qquery.exec(query.c_str());


		query = " delete from Facturas_Articulos where id_factura=";
		query.append(itoa(factura.getid()));
		query.append(";");
		ok = ok && qquery.exec(query.c_str());


		list<LineaArticulo> l = factura.getlista_articulos();
		list<LineaArticulo>::iterator iter;
		for(iter=l.begin(); iter!=l.end();iter++) {
			query = " insert into Facturas_Articulos(id_factura, id_articulo, cantidad) values(";
			query.append(itoa(factura.getid()));
			query.append(", ");
			query.append(itoa(iter->getarticulo().getid()));
			query.append(", ");
			query.append(itoa(iter->getcantidad()));
			query.append(");");
			ok = ok && qquery.exec(query.c_str());
		}
		ok = ok && db.commit();
		return ok;
}


bool AccesoADatos::actualizaPresupuesto(Presupuesto presupuesto) {
		db.transaction();
		QSqlQuery qquery;

		string query="update Presupuestos set ";//
		if(presupuesto.getn_factura()==-1)
			query.append("n_factura=NULL, ");
		else {
			string c("n_factura=");
			c.append(itoa(presupuesto.getn_factura()));
			query.append(c + ", ");
		}
		if(presupuesto.getfecha() == "")
			query.append("fecha=NULL, ");
		else
			query.append("fecha=\""+ presupuesto.getfecha() + "\", ");

		if(presupuesto.getaparato()== "")
			query.append("aparato=NULL, ");
		else
			query.append("aparato=\"" + presupuesto.getaparato() + "\", ");

		if(presupuesto.getmarca()== "")
			query.append("marca=NULL, ");
		else
			query.append("marca=\"" + presupuesto.getmarca() + "\", ");

		if(presupuesto.getmodelo()== "")
			query.append("modelo=NULL, ");
		else
			query.append("modelo=\"" + presupuesto.getmodelo() + "\", ");

		if(presupuesto.getn_fabricacion()== -1)
			query.append("n_fabricacion=NULL, ");
		else {
			string c("n_fabricacion=");
			c.append(itoa(presupuesto.getn_fabricacion()));
			query.append( c + ", ");
		}
		if(presupuesto.getlugar_reparacion()== 0)
			query.append("lugar_reparacion=NULL, ");
		else {
			bool lr = *presupuesto.getlugar_reparacion();
			if (lr) query.append("lugar_reparacion=1, ");
			else query.append("lugar_reparacion=0, ");
		}

		if(presupuesto.getaceptado()== 0)
			query.append("aceptado=NULL, ");
		else {
			bool lr = *presupuesto.getaceptado();
			if (lr) query.append("aceptado=1, ");
			else query.append("aceptado=0, ");
		}
		if(presupuesto.getcliente() == 0)
			query.append("id_cliente=NULL, ");
		else {
			string c("id_cliente=");
			c.append(itoa(presupuesto.getcliente()->getid()));
			query.append(c + ", ");
		}


		if(presupuesto.getfactura() == 0)
			query.append("id_factura=NULL, ");
		else {
			string c("id_factura=");
			c.append(itoa(presupuesto.getfactura()->getid()));
			query.append(", ");
		}
		if(presupuesto.getaveria() == "") {
			query.append("averia=NULL, ");
		} else {
			query.append("averia=\"");
			query.append(presupuesto.getaveria() + "\", ");

		}
		if(presupuesto.gettrabajo_realizado() == "") {
			query.append("trabajo_realizado=NULL, ");
		} else {
			query.append("trabajo_realizado=\"");
			query.append(presupuesto.gettrabajo_realizado() + "\", ");
		}
		if(presupuesto.gettiempo_empleado() == "") {
				query.append("tiempo_empleado=NULL, ");
		} else {
			query.append("tiempo_empleado=\"");
			query.append(presupuesto.gettiempo_empleado() + "\", ");
		}
		if(presupuesto.getfecha_terminacion() == "") {
			query.append("fecha_terminacion=NULL, ");
		} else {
			query.append("fecha_terminacion=\"");
			query.append(presupuesto.getfecha_terminacion() + "\", ");
		}
		if(presupuesto.getobservaciones() == "") {
			query.append("observaciones=NULL, ");
		} else {
			query.append("observaciones=\"");
			query.append(presupuesto.getobservaciones() + "\", ");
		}
		if(presupuesto.getprecio_materiales() == -1.) {
			query.append("precio_materiales=NULL, ");
		} else {
			query.append("precio_materiales=");
			query.append(ftoa(presupuesto.getprecio_materiales()));
			query.append(", ");
		}
		if(presupuesto.getprecio_mano_obra() == -1.) {
			query.append("precio_mano_obra=NULL, ");
		} else {
			query.append("precio_mano_obra=");
			query.append(ftoa(presupuesto.getprecio_mano_obra()));
			query.append(", ");
		}
		if(presupuesto.getprecio_desplazamiento() == -1.) {
			query.append("precio_desplazamiento=NULL, ");
		} else {
			query.append("precio_desplazamiento=");
			query.append(ftoa(presupuesto.getprecio_desplazamiento()));
			query.append(", ");		}
		if(presupuesto.getprecio_transporte() == -1.) {
			query.append("precio_transporte=NULL ");
		} else {
			query.append("precio_transporte=");
			query.append(ftoa(presupuesto.getprecio_transporte()));
			query.append(" ");
		}
		query.append("where rowid=");
		query.append(itoa(presupuesto.getid()));
		query.append(";");
		//QMessageBox::information(0,"Aviso",query.c_str());
		bool ok = qquery.exec(query.c_str());
		if (!ok) {
			qDebug() << qquery.lastError() << endl;
		}


		query = " delete from Presupuestos_Articulos where id_presupuesto=";
		query.append(itoa(presupuesto.getid()));
		query.append(";");
		ok = ok && qquery.exec(query.c_str());
		if (!ok) {
					qDebug() << qquery.lastError() << endl;
		}

		list<LineaArticulo> l = presupuesto.getlista_articulos();
		list<LineaArticulo>::iterator iter;
		for(iter=l.begin(); iter!=l.end();iter++) {
			query = " insert into Presupuestos_Articulos(id_presupuesto, id_articulo, cantidad) values(";
			query.append(itoa(presupuesto.getid()));
			query.append(", ");
			query.append(itoa(iter->getarticulo().getid()));
			query.append(", ");
			query.append(itoa(iter->getcantidad()));
			query.append(");");
			ok = ok && qquery.exec(query.c_str());
			if (!ok) {
				qDebug() << qquery.lastError() << endl;
			}
		}
		ok = ok && db.commit();
		return ok ;
}



bool AccesoADatos::actualizaArticulo(Articulo articulo) {
	db.transaction();
	string query("update Articulos set historico=1 where historico=0 and rowid=");
	query.append(itoa(articulo.getid()));
	query.append(";");

	QSqlQuery qquery;
	bool ok = qquery.exec(query.c_str());

	query = " insert into Articulos(codigo,descripcion,caja,existencias,existencias_minimas,pvp,precio_coste,descuento) values (";
	if(articulo.getcodigo() == -1)
		query.append("NULL, ");
	else {
		query.append(itoa(articulo.getcodigo()));
		query.append(", ");
	}
	if(articulo.getdescripcion() =="")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(articulo.getdescripcion() + "\", ");
	}
	if(articulo.getcaja() == "" )
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(articulo.getcaja() + "\", ");
	}
	if(articulo.getexistencias() == -1)
		query.append("NULL, ");
	else {
		query.append(itoa(articulo.getexistencias()));
		query.append(", ");
	}
	if(articulo.getexistencias_minimas() == -1)
		query.append("NULL, ");
	else {
		query.append(itoa(articulo.getexistencias_minimas()));
		query.append(", ");
	}
	if(articulo.getpvp() ==-1.)
		query.append("NULL, ");
	else {
		query.append(ftoa(articulo.getpvp()));
		query.append(", ");
	}
	if(articulo.getprecio_coste() == -1.)
		query.append("NULL, ");
	else {
		query.append(ftoa(articulo.getprecio_coste()));
		query.append(", ");
	}
	if(articulo.getdescuento() == -1)
		query.append("NULL);");
	else {
		query.append(itoa(articulo.getdescuento()));
		query.append(");");
	}
	ok = ok && qquery.exec(query.c_str());
	ok = ok && db.commit();
	return ok;
}


bool AccesoADatos::actualizaCliente(Cliente cliente) {
	db.transaction();
	string query("update Clientes set historico=1 where historico=0 and rowid=");
	query.append(itoa(cliente.getid()));
	query.append("; ");
	QSqlQuery qquery;
	bool ok = qquery.exec(query.c_str());

	query="insert into Clientes(codigo,nombre,apellidos,direccion,nif,poblacion) values(";
	if(cliente.getcodigo() == 0)
		query.append("NULL, ");
	else {
		query.append(itoa(cliente.getcodigo()));
		query.append(", ");
	}
	if(cliente.getnombre() == "")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getnombre() + "\", ");
	}
	if(cliente.getapellidos() == "")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getapellidos() + "\", ");
	}
	if(cliente.getdireccion()=="")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append(cliente.getdireccion() + "\", " );
	}
	if(cliente.getnif()=="")
		query.append("NULL, ");
	else {
		query.append("\"");
		query.append( cliente.getnif() + "\", ");
	}
	if(cliente.getpoblacion()=="")
		query.append("NULL);");
	else {
		query.append("\"");
		query.append( cliente.getpoblacion() + "\");");
	}
	
	list<int> lista = cliente.gettelefonos();
	list<int>::iterator it;
	for (it = lista.begin(); it != lista.end(); it++){
		string queryTelefonos="insert into Telefonos(id_cliente,numero) values(";
		queryTelefonos.append(itoa(dameIdCliente()));
		queryTelefonos.append(", ");
		queryTelefonos.append(itoa(*it));
		queryTelefonos.append(");");
		cout << "[Debug]" << queryTelefonos << endl;
		QSqlQuery qqueryt;
		ok = ok && qqueryt.exec(queryTelefonos.c_str());
	}

	ok = ok && qquery.exec(query.c_str());
	ok = ok && db.commit();
	return ok;
}





//FALTA COMPROBAR QUE LA BD NO SE QUEDE EN UN ESTADO INCONSISTENTE
//METODOS PARA ELIMINAR DE LA BD
bool AccesoADatos::eliminarFactura(Factura f) {
	string q("delete from Facturas where rowid=");
	q.append(itoa(f.getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return false;
	}
	return true;
}


bool AccesoADatos::eliminarPresupuesto(Presupuesto p) {
	string q("delete from Presupuestos where rowid=");
	q.append(itoa(p.getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return false;
	}
	return true;
}

bool AccesoADatos::eliminarCliente(Cliente c) {
	// Borrar un cliente solo es marcarlo como historico.
	string q("update Clientes set historico=1 where historico=0 and rowid=");
	q.append(itoa(c.getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return false;
	}
	return true;
}

bool AccesoADatos::eliminarArticulo(Articulo a) {
	// Borrar un articulo solo es marcarlo como historico.
	string q("update Articulos set historico=1 where historico=0 and rowid=");
	q.append(itoa(a.getid()));
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return false;
	}
	return true;
}

//METODOS "DAME"
int AccesoADatos::dameIdArticulo() {
	string q("select seq from sqlite_sequence where name=\"Articulos\";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return -1;
	}
	if (query.next())
		return query.value(0).toInt() + 1;
	return 1;
}
int AccesoADatos::dameIdCliente() {
	string q("select seq from sqlite_sequence where name=\"Clientes\";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return -1;
	}
	if (query.next())
		return query.value(0).toInt() + 1;
	return 1;
}
int AccesoADatos::dameIdFactura() {
	string q("select seq from sqlite_sequence where name=\"Facturas\";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return -1;
	}
	if (query.next())
		return query.value(0).toInt() + 1;
	return 1;
}
int AccesoADatos::dameIdPresupuesto() {
	string q("select seq from sqlite_sequence where name=\"Presupuestos\";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return -1;
	}
	if (query.next())
		return query.value(0).toInt() + 1;
	return 1;
}

bool AccesoADatos::cambiarIva(int v) {
	string q("update Iva set valor=");
	q.append(QString::number(v,10).toStdString().c_str());
	q.append(";");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return false;
	}
	return true;
}

int AccesoADatos::obtenerIva() {
	string q("select valor from Iva;");
	QSqlQuery query;
	bool ok = query.exec(q.c_str());
	if (!ok) {
		qDebug() << query.lastError ();
		return -1;
	}
	if (query.next())
		return query.value(0).toInt();
	return -1;
}
