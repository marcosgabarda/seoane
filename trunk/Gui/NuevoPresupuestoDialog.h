#ifndef NUEVOPRESUPUESTODIALOG_H
#define NUEVOPRESUPUESTODIALOG_H

#include <QtGui/QDialog>
#include "ui_NuevoPresupuestoDialog.h"
#include "../Negocio/CapaNegocio.h"
#include "../Negocio/Presupuesto.h"
#include "../Gui/ListarPresupuestos.h"

class ActualizadorPreThread;

class NuevoPresupuestoDialog : public QDialog
{
    Q_OBJECT

public:
	NuevoPresupuestoDialog(CapaNegocio * const cn, QWidget *parent = 0, Presupuesto *f = 0);
    ~NuevoPresupuestoDialog();
    
    void addRow();
    void addRowTelefono();
    void actualizaPrecios();
    //void actualizar();
    
private:
    Ui::NuevoPresupuestoDialogClass ui;
    CapaNegocio *capaNegocio;
    QWidget *workspace;
    
    list<Cliente> lClientes;
    list<Articulo> lArticulos;
    list<pair<pair<string, double>, int> > lArticuloFila;
    
    void buscarCliente();
    void buscarArticulo();
    void cambiarCliente();
    bool comprobarDatos();
    
    
    Presupuesto *nuevoPresupuesto;
    Cliente *cliente;
    ListarPresupuestos *padre;
    
    ActualizadorPreThread *actualizador;
    
    Articulo articuloActual;
    
private slots:

	void anyadirLineaArticulo();
	void borrarArticulo();
	void guardar();
	void editar();
	void limpiar();
	void nuevoTelefono();
	void borrarTelefono();
	void crearFactura();
	void cambiarEstadoDomicilio();
	void cambiarEstadoTaller();
	
	void imprimir();
	bool guardarSinSalir();
	bool editarSinSalir();
	
protected:
	void keyPressEvent(QKeyEvent* event);
    
};

class ActualizadorPreThread : public QThread {
private:
	 NuevoPresupuestoDialog *nfd;
public:
    void run();
    void setPadre(NuevoPresupuestoDialog *parent);
};

#endif // NUEVOPRESUPUESTODIALOG_H
