#ifndef NUEVAFACTURADIALOG_H
#define NUEVAFACTURADIALOG_H

#include <QtGui/QDialog>
#include "ui_NuevaFacturaDialog.h"
#include "../Negocio/CapaNegocio.h"
#include "../Negocio/Factura.h"
#include "../Gui/ListarFacturas.h"

class ActualizadorThread;

class NuevaFacturaDialog : public QDialog
{
    Q_OBJECT

public:
    NuevaFacturaDialog(CapaNegocio * const cn, QWidget *parent = 0, Factura *f = 0, bool dePresupuesto = false);
    ~NuevaFacturaDialog();
    
    void addRow();
    void addRowTelefono();
    void actualizaPrecios();
    void buscarCliente();
    void buscarArticulo();
    
private:
    Ui::NuevaFacturaDialogClass ui;
    CapaNegocio *capaNegocio;
    
    list<Cliente> lClientes;
    list<Articulo> lArticulos;
    list<pair<pair<string, double>, int> > lArticuloFila;
    
    bool comprobarDatos();
    void cambiarCliente();
    
    Factura *nuevaFactura;
    Cliente *cliente;
    ListarFacturas *padre;
    
    Articulo articuloActual;
    
    ActualizadorThread *actualizador;

    bool dePresupuesto;
    
private slots:

	void anyadirLineaArticulo();
	void borrarArticulo();
	void guardar();
	void editar();
	void limpiar();
	void nuevoTelefono();
	void borrarTelefono();
	void cambiarEstadoDomicilio();
	void cambiarEstadoTaller();
	void imprimir();
	bool guardarSinSalir();
	bool editarSinSalir();

protected:
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
};

class ActualizadorThread : public QThread {
private:
	 NuevaFacturaDialog *nfd;
public:
    void run();
    void setPadre(NuevaFacturaDialog *parent);
}; 

#endif // NUEVAFACTURADIALOG_H
