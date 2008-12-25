#include "../Negocio/CapaNegocio.h"
#include "../Negocio/Articulo.h"
#include "../Negocio/Cliente.h"
#include "../Negocio/Factura.h"
#include "../Negocio/Presupuesto.h"
#include "../Gui/MainWindow.h"

#include <iostream>
#include <string>
#include <list>
#include <QApplication>

using namespace std;

/****ATRIBUTO GLOBAL PARA SOLO TRABAJAR CON UNA INSTANCIA DE LA CAPA DE NEGOCIO****/
CapaNegocio * const capaNegocio = new CapaNegocio;

int main(int argc, char* argv[]){

	QApplication app(argc, argv);
	
	app.setWindowIcon(QIcon("Gui/images/icono.ico"));
	
	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap("Gui/images/splash.png"));
	splash->show();

	Qt::Alignment bottomRight = Qt::AlignRight | Qt::AlignBottom;

	splash->showMessage(QObject::tr("Cargando..."), bottomRight, Qt::black);
	capaNegocio->inicializar();
    MainWindow main(capaNegocio);
    main.showMaximized();
    
    splash->finish(&main);
    delete splash;

    return app.exec();
}
