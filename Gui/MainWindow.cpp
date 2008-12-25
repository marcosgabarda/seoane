#include "MainWindow.h"
#include "../Negocio/Factura.h"
#include "NuevoClienteDialog.h"
#include "NuevoArticuloDialog.h"
#include "NuevaFacturaDialog.h"
#include "NuevoPresupuestoDialog.h"
#include "ListarClientes.h"
#include "BuscarFacturaDialog.h"
#include "CambiarIvaDialog.h"
#include <QtGui>
#include "ListarFacturas.h"
#include "ListarPresupuestos.h"
#include "ListarArticulos.h"
#include <list>
#include <iostream>
#include <QThread>
#include "BuscarClienteDialog.h"
#include "BuscarArticuloDialog.h"
#include "BuscarPresupuestoDialog.h"
#include "ConfigurarImpresora.h"
#include <QTextDocument>
#include "VisorAyuda.h"
#include "imprimirsobrecliente.h"

using namespace std;
/*
template<class A, class B> class Conversion {
	typedef char S_True;
	class S_False {char dummy[2];}
	static A CrearInstancia();
	static S_True Test(B);static S_False Test(…);
public:
	enum {
		existe = ( sizeof(Test(CrearInstancia())) == sizeof(S_True) )
	};
};
*/
void MainThread::setPadre(QWorkspace* parent) {
	 mw = parent;
}
void MainThread::run() {
	 while (true) {
		 usleep(500000);
		 /**
		  * Actualizador de listados abiertos.
		  */
		 QWidgetList windows = mw->windowList();
		 if (windows.isEmpty()) continue;	 
		 	
		 for (int i = 0; i < windows.size(); ++i) {
			 QWidget * child = windows.at(i);
			 ListarArticulos *la = dynamic_cast<ListarArticulos *>( child );
			 if (la != 0) {
				 /*El hijo es de tipo Listar Articulos. */
				 la->actualizar();
			 }
			 ListarFacturas *lf = dynamic_cast<ListarFacturas *>( child );
			 if (lf != 0) {
				 /*El hijo es de tipo Listar Facturas. */
				 lf->actualizar();
			 }
			 ListarPresupuestos *lp = dynamic_cast<ListarPresupuestos *>(child);
			 if (lp != 0) {
				 /*El hijo es de tipo Listar Presupuestos. */
				 lp->actualizar();
			 }
			 ListarClientes *lc = dynamic_cast<ListarClientes *>(child);
			 if (lc != 0) {
				 /*El hijo es de tipo Listar Clientes*/
				 lc->actualizar();
			 }
		 }
	 }
} 


MainWindow::MainWindow(CapaNegocio * const cn, QMainWindow *parent)	: QMainWindow(parent)
{
	workspace = new QWorkspace;
	
	setWindowIcon(QIcon("Gui/images/icono.ico"));
	workspace->setBackground(QBrush(QImage("Gui/images/textura.png")));
	setCentralWidget(workspace);
	
	capaNegocio = cn;

	windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget *)), workspace, SLOT(setActiveWindow(QWidget *)));
	
	connect(workspace, SIGNAL(windowActivated(QWidget *)), this, SLOT(updateMenus()));
	
	createActions();
	createMenus();
	createToolBar();
	createStatusBar();

	actualizador = new MainThread();
	actualizador->setPadre(workspace);
	actualizador->start();
	
	setWindowTitle(tr("Seoane"));
}

MainWindow::~MainWindow()
{
	actualizador->quit();
}
//Acciones del menu facturas
void MainWindow::listarFacturas() {
	ListarFacturas *lf = new ListarFacturas(capaNegocio, workspace);
	workspace->addWindow(lf);
	lf->show();
	statusBar()->showMessage(tr("Total Facturas: %1").arg(capaNegocio->getTotalFacturas()));
}
void MainWindow::nuevaFactura() {
	NuevaFacturaDialog *nfd = new NuevaFacturaDialog(capaNegocio, workspace);
	workspace->addWindow(nfd);
	nfd->show();
	statusBar()->showMessage(tr("Nueva factura."));
}

void MainWindow::buscarFactura() {
	BuscarFacturaDialog *bfd = new BuscarFacturaDialog(capaNegocio, workspace);
	workspace->addWindow(bfd);
	bfd->show();
}

//Acciones del menu presupuestos
void MainWindow::listarPresupuestos() {
	ListarPresupuestos *lp = new ListarPresupuestos(capaNegocio, workspace);
	workspace->addWindow(lp);
	lp->show();
	statusBar()->showMessage(tr("Total Presupuestos: %1").arg(capaNegocio->getTotalPresupuestos()));
}


void MainWindow::buscarPresupuestos() {
	BuscarPresupuestoDialog *bfd = new BuscarPresupuestoDialog(capaNegocio, workspace);
	workspace->addWindow(bfd);
	bfd->show();
}


void MainWindow::nuevoPresupuestos() {
	NuevoPresupuestoDialog *nfd = new NuevoPresupuestoDialog(capaNegocio, workspace);
	workspace->addWindow(nfd);
	nfd->show();
	statusBar()->showMessage(tr("Nuevo presupuesto."));
}


//Acciones del menu articulos
void MainWindow::altaArticulos() {
	NuevoArticuloDialog *aad = new NuevoArticuloDialog(capaNegocio,workspace);
		workspace->addWindow(aad);
		aad->show();
}

void MainWindow::buscarArticulos() {
	BuscarArticuloDialog* bcd = new BuscarArticuloDialog(capaNegocio,workspace);
	workspace->addWindow(bcd);
	bcd->show();
}

void MainWindow::listarArticulos() {
	ListarArticulos *la = new ListarArticulos(capaNegocio, workspace);
	workspace->addWindow(la);
	la->show();
	statusBar()->showMessage(tr("Total Articulos: %1").arg(capaNegocio->getTotalArticulos()));
}

//Acciones del menu clientes
void MainWindow::nuevoCliente(){
	NuevoClienteDialog *ncd = new NuevoClienteDialog(capaNegocio,workspace);
	workspace->addWindow(ncd);
	ncd->show();
}
void MainWindow::buscarCliente(){
	BuscarClienteDialog* bcd = new BuscarClienteDialog(capaNegocio,workspace);
	workspace->addWindow(bcd);
	bcd->show();
}
void MainWindow::listarCliente(){
	ListarClientes *lc = new ListarClientes(capaNegocio, workspace);
	workspace->addWindow(lc);
	lc->show();
	statusBar()->showMessage(tr("Total Clientes: %1").arg(capaNegocio->getTotalClientes()));
}

void MainWindow::imprimirClientes(){
	ImprimirSobreCliente *isc = new ImprimirSobreCliente(workspace, capaNegocio );
	workspace->addWindow(isc);
	isc->show();
	statusBar()->showMessage(tr("Imprimir Sobre Clientes: "));
}

//Acciones del menu ayuda
void MainWindow::acercaDeAyuda() {
	QMessageBox::about(this, tr("Acerca de Seoane Facturación"),
		tr("<h2>Seoane v1.0.4-beta</h2>"
				"<p>Copyright &copy; 2007 Maite Simon & Marcos Gabarda</p>"
				"<h5><i>Programa bajo licencia GPL 3.0</i></h5>"));
}
void MainWindow::ayudaAyuda() {
	VisorAyuda *va = new VisorAyuda(this);
	workspace->addWindow(va);
	va->show();
}
void MainWindow::cambiarIva() {
	CambiarIvaDialog *civa = new CambiarIvaDialog(capaNegocio, this);
	workspace->addWindow(civa);
	civa->show();
}

void MainWindow::configurarImpresora() {
	ConfigurarImpresora *ci = new ConfigurarImpresora(this);
	workspace->addWindow(ci);
	ci->show();
}

void MainWindow::createActions() {

	//menu facturas
	listarFacturasAction = new QAction(tr("&Listar"), this);
	listarFacturasAction->setIcon(QIcon(QString::fromUtf8("Gui/images/LFactura.PNG")));
	connect(listarFacturasAction, SIGNAL(triggered()), this, SLOT(listarFacturas()));

	nuevaFacturaAction = new QAction(tr("&Nueva"), this);
	nuevaFacturaAction->setIcon(QIcon(QString::fromUtf8("Gui/images/NFactura.PNG")));
	connect(nuevaFacturaAction, SIGNAL(triggered()), this, SLOT(nuevaFactura()));

	buscarFacturaAction = new QAction(tr("&Buscar"), this);
	buscarFacturaAction->setIcon(QIcon(QString::fromUtf8("Gui/images/BFactura.PNG")));
	connect(buscarFacturaAction, SIGNAL(triggered()), this, SLOT(buscarFactura()));


	//menu presupuestos
	listarPresupuestosAction = new QAction(tr("&Listar"), this);
	listarPresupuestosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/LPresupuesto.PNG")));
	connect(listarPresupuestosAction, SIGNAL(triggered()), this, SLOT(listarPresupuestos()));

	nuevoPresupuestosAction = new QAction(tr("&Nuevo"), this);
	nuevoPresupuestosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/NPresupuesto.PNG")));
	connect(nuevoPresupuestosAction, SIGNAL(triggered()), this, SLOT(nuevoPresupuestos()));

	buscarPresupuestosAction = new QAction(tr("&Buscar"), this);
	buscarPresupuestosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/BPresupuesto.PNG")));
	connect(buscarPresupuestosAction, SIGNAL(triggered()), this, SLOT(buscarPresupuestos()));

	//menu articulos

	altaArticulosAction = new QAction(tr("&Alta"), this);
	altaArticulosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/NArticulo.PNG")));
	connect(altaArticulosAction, SIGNAL(triggered()), this, SLOT(altaArticulos()));

	buscarArticulosAction = new QAction(tr("&Buscar"), this);
	buscarArticulosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/BArticulo.PNG")));
	connect(buscarArticulosAction, SIGNAL(triggered()), this, SLOT(buscarArticulos()));
	
	listarArticulosAction = new QAction(tr("&Listar"), this);
	listarArticulosAction->setIcon(QIcon(QString::fromUtf8("Gui/images/LArticulo.PNG")));
	connect(listarArticulosAction, SIGNAL(triggered()), this, SLOT(listarArticulos()));

	//menu clientes
	nuevoClienteAction = new QAction(tr("&Nuevo"), this);
	nuevoClienteAction->setIcon(QIcon(QString::fromUtf8("Gui/images/NCliente.png")));
	connect(nuevoClienteAction, SIGNAL(triggered()), this, SLOT(nuevoCliente()));

	buscarClienteAction = new QAction(tr("&Buscar"), this);
	buscarClienteAction->setIcon(QIcon(QString::fromUtf8("Gui/images/BCliente.png")));
	connect(buscarClienteAction, SIGNAL(triggered()), this, SLOT(buscarCliente()));

	listarClienteAction = new QAction(tr("&Listar"), this);
	listarClienteAction->setIcon(QIcon(QString::fromUtf8("Gui/images/LCliente.png")));
	connect(listarClienteAction, SIGNAL(triggered()), this, SLOT(listarCliente()));

	imprimirClienteAction = new QAction(tr("&Imprimir"), this);
	imprimirClienteAction->setIcon(QIcon(QString::fromUtf8("Gui/images/LCliente.png")));
	connect(imprimirClienteAction, SIGNAL(triggered()), this, SLOT(imprimirClientes()));
	
	//menu ayuda
	acercaDeAyudaAction = new QAction(tr("&Acera de"), this);
	connect(acercaDeAyudaAction, SIGNAL(triggered()), this, SLOT(acercaDeAyuda()));

	ayudaAyudaAction = new QAction(tr("&Ayuda"), this);
	connect(ayudaAyudaAction, SIGNAL(triggered()), this, SLOT(ayudaAyuda()));
	
	//Menu ventanas
	closeAction = new QAction(tr("&Cerrar"), this);
	closeAction->setShortcut(tr("Ctrl+F4"));
	closeAction->setStatusTip(tr("Cierra la ventana activa."));
	connect(closeAction, SIGNAL(triggered()), workspace, SLOT(closeActiveWindow()));
		
	closeAllAction = new QAction(tr("Cerrar &Todo"), this);
	closeAllAction->setStatusTip(tr("Cierra todas las ventanas."));
	connect(closeAllAction, SIGNAL(triggered()), workspace, SLOT(closeAllWindows()));

	tileAction = new QAction(tr("&Tile"), this);
	tileAction->setStatusTip(tr("Organiza las ventanas por valdosas."));
	connect(tileAction, SIGNAL(triggered()), workspace, SLOT(tile()));

	cascadeAction = new QAction(tr("&Cascada"), this);
	cascadeAction->setStatusTip(tr("Organiza las ventanas en cascada."));
	connect(cascadeAction, SIGNAL(triggered()), workspace, SLOT(cascade()));

	nextAction = new QAction(tr("&Siguiente"), this);
	nextAction->setStatusTip(tr("Se mueve a la siguiente ventana."));
	connect(nextAction, SIGNAL(triggered()), workspace, SLOT(activateNextWindow()));

	previousAction = new QAction(tr("&Anterior"), this);
	previousAction->setStatusTip(tr("Se mueve a la ventana anterior."));
	connect(previousAction, SIGNAL(triggered()), workspace, SLOT(activatePreviousWindow()));
	
	cambiarIvaAction = new QAction(tr("Cambiar IVA"), this);
	connect(cambiarIvaAction, SIGNAL(triggered()), this, SLOT(cambiarIva()));
	
	//configurarImpresoraAction = new QAction(tr("Configurar Impresora"), this);
	//connect(configurarImpresoraAction, SIGNAL(triggered()), this, SLOT(configurarImpresora()));

}

void MainWindow::createMenus() {
	facturasMenu = menuBar()->addMenu(tr("&Facturas"));
	presupuestosMenu = menuBar()->addMenu(tr("&Presupuestos"));
	articulosMenu=menuBar()->addMenu(tr("&Articulos"));
	clientesMenu=menuBar()->addMenu(tr("&Clientes"));
	windowMenu=menuBar()->addMenu(tr("&Ventanas"));
	configMenu=menuBar()->addMenu(tr("Con&figuracion"));
	ayudaMenu=menuBar()->addMenu(tr("&Ayuda"));
	
	//crea el menu facturas
	facturasMenu->addAction(listarFacturasAction);
	facturasMenu->addAction(nuevaFacturaAction);
	facturasMenu->addAction(buscarFacturaAction);

	//crea menu presupuestos
	presupuestosMenu->addAction(listarPresupuestosAction);
	presupuestosMenu->addAction(nuevoPresupuestosAction);
	presupuestosMenu->addAction(buscarPresupuestosAction);

	//crea el menu articulo
	articulosMenu->addAction(altaArticulosAction);
	articulosMenu->addAction(buscarArticulosAction);
	articulosMenu->addAction(listarArticulosAction);
	
	//Crea el menu clientes
	clientesMenu->addAction(nuevoClienteAction);
	clientesMenu->addAction(buscarClienteAction);
	clientesMenu->addAction(listarClienteAction);
	clientesMenu->addAction(imprimirClienteAction);
	
	//crea el menu ayuda
	ayudaMenu->addAction(acercaDeAyudaAction);
	ayudaMenu->addAction(ayudaAyudaAction);
	
	//crea el menu vantanas
	windowMenu->addAction(closeAction);
	windowMenu->addAction(closeAllAction);
	windowMenu->addSeparator();
	windowMenu->addAction(tileAction);
	windowMenu->addAction(cascadeAction);
	windowMenu->addSeparator();
	windowMenu->addAction(nextAction);
	windowMenu->addAction(previousAction);
	
	configMenu->addAction(cambiarIvaAction);
	//configMenu->addAction(configurarImpresoraAction);

}

void MainWindow::createToolBar() {
	
	facturaToolBar = addToolBar(tr("Facturas"));
	facturaToolBar->addAction(nuevaFacturaAction);
	facturaToolBar->addAction(buscarFacturaAction);
	facturaToolBar->addAction(listarFacturasAction);
	
	presupuestoToolBar = addToolBar(tr("Presupuestos"));
	presupuestoToolBar->addAction(nuevoPresupuestosAction);
	presupuestoToolBar->addAction(buscarPresupuestosAction);
	presupuestoToolBar->addAction(listarPresupuestosAction);
	
	clienteToolBar = addToolBar(tr("Clientes"));
	clienteToolBar->addAction(nuevoClienteAction);
	clienteToolBar->addAction(buscarClienteAction);
	clienteToolBar->addAction(listarClienteAction);
	
	articuloToolBar = addToolBar(tr("Articulos"));
	articuloToolBar->addAction(altaArticulosAction);
	articuloToolBar->addAction(buscarArticulosAction);
	articuloToolBar->addAction(listarArticulosAction);
	
}

void MainWindow::updateMenus() {
	
	windowMenu->clear();
	windowMenu->addAction(closeAction);
	windowMenu->addAction(closeAllAction);
	windowMenu->addSeparator();
	windowMenu->addAction(tileAction);
	windowMenu->addAction(cascadeAction);
	windowMenu->addSeparator();
	windowMenu->addAction(nextAction);
	windowMenu->addAction(previousAction);

	QWidgetList windows = workspace->windowList();
	
	if (!windows.isEmpty()) windowMenu->addSeparator(); 
	
	for (int i = 0; i < windows.size(); ++i) {
		QWidget *child = windows.at(i);
		QString text;
		if (i < 9) {
			text = tr("&%1 %2").arg(i + 1).arg(child->windowTitle());
		} else {
			text = tr("%1 %2").arg(i + 1).arg(child->windowTitle());
		}
		QAction *action  = windowMenu->addAction(text);
		action->setCheckable(true);
		action->setChecked(child == workspace->activeWindow());
		connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
		windowMapper->setMapping(action, windows.at(i));
	}
}
void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Listo"));
}
