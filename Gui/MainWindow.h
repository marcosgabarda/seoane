#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "../Negocio/Factura.h"
#include "../Negocio/CapaNegocio.h"
#include <QtGui>
#include <list>

class MainThread;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(CapaNegocio * const cn, QMainWindow *parent = 0);
	virtual ~MainWindow();

private slots:

	//menu ventana
	void updateMenus(); //Actualiza las ventanas abiertas

	//menu facturas
	void listarFacturas();
	void nuevaFactura();
	void buscarFactura();

	//menu presupuestos
	void listarPresupuestos();
	void nuevoPresupuestos();
	void buscarPresupuestos();

	//menu articulos
	void altaArticulos();
	void buscarArticulos();
	void listarArticulos();

	//menu clientes
	void nuevoCliente();
	void buscarCliente();
	void listarCliente();

	void imprimirClientes();
	
	//menu ayuda
	void acercaDeAyuda();
	void ayudaAyuda();

	void cambiarIva();
	void configurarImpresora();

private:

	MainThread *actualizador;
	
	QWorkspace *workspace;
    QSignalMapper *windowMapper;
    
	//menus
	QMenu *facturasMenu;
	QMenu *presupuestosMenu;
	QMenu *articulosMenu;
	QMenu *ayudaMenu;
	QMenu *clientesMenu;
	QMenu *windowMenu;
	QMenu *configMenu;
	
	QToolBar *clienteToolBar;
	QToolBar *articuloToolBar;
	QToolBar *facturaToolBar;
	QToolBar *presupuestoToolBar;

	//acciones del menu facturas
	QAction *listarFacturasAction;
	QAction *nuevaFacturaAction;
	QAction *buscarFacturaAction;

	//acciones del menu presupuestos
	QAction *listarPresupuestosAction;
	QAction *buscarPresupuestosAction;
	QAction *nuevoPresupuestosAction;

	//acciones del menu articulos
	QAction *altaArticulosAction;
	QAction *buscarArticulosAction;
	QAction *listarArticulosAction;

	//acciones del menu clientes
	QAction *nuevoClienteAction;
	QAction *buscarClienteAction;
	QAction *listarClienteAction;
	QAction *imprimirClienteAction;
	
	//acciones del menu ayuda
	QAction *acercaDeAyudaAction;
	QAction *ayudaAyudaAction;
	
	//acciones del menu ventana
	QAction *closeAction;
	QAction *closeAllAction;
	QAction *tileAction;
	QAction *cascadeAction;
	QAction *nextAction;
	QAction *previousAction;
	
	QAction *cambiarIvaAction;
	QAction *configurarImpresoraAction;
	
	CapaNegocio *capaNegocio;

	void createMenus();
	void createActions();
	void createToolBar();
	void createStatusBar();

};

class MainThread : public QThread {
private:
	 QWorkspace *mw;
public:
    void run();
    void setPadre(QWorkspace *parent);
}; 


#endif /*MAINWINDOW_H_*/
