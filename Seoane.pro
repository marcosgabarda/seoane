TEMPLATE = app
TARGET = seoane
QT += core \
    gui \
    sql
HEADERS += Negocio/Articulo.h \
    Negocio/CapaNegocio.h \
    Negocio/Cliente.h \
    Negocio/Factura.h \
    Negocio/LineaArticulo.h \
    Negocio/Presupuesto.h \
    Gui/BuscarArticuloDialog.h \
    Gui/BuscarClienteDialog.h \
    Gui/BuscarFacturaDialog.h \
    Gui/BuscarPresupuestoDialog.h \
    Gui/CambiarIvaDialog.h \
    Gui/ConfigurarImpresora.h \
    Gui/ListarArticulos.h \
    Gui/ListarClientes.h \
    Gui/ListarFacturas.h \
    Gui/ListarPresupuestos.h \
    Gui/MainWindow.h \
    Gui/NuevaFacturaDialog.h \
    Gui/NuevoArticuloDialog.h \
    Gui/NuevoClienteDialog.h \
    Gui/NuevoPresupuestoDialog.h \
    Gui/PrintWindow.h \
    Gui/VisorAyuda.h \
    Gui/imprimirsobrecliente.h \
    Datos/AccesoADatos.h \
    Datos/CriterioBusqueda.h \
    Datos/utils.h
SOURCES += Negocio/Articulo.cpp \
    Negocio/CapaNegocio.cpp \
    Negocio/Cliente.cpp \
    Negocio/Factura.cpp \
    Negocio/LineaArticulo.cpp \
    Negocio/Presupuesto.cpp \
    Gui/BuscarArticuloDialog.cpp \
    Gui/BuscarClienteDialog.cpp \
    Gui/BuscarFacturaDialog.cpp \
    Gui/BuscarPresupuestoDialog.cpp \
    Gui/CambiarIvaDialog.cpp \
    Gui/ConfigurarImpresora.cpp \
    Gui/ListarArticulos.cpp \
    Gui/ListarClientes.cpp \
    Gui/ListarFacturas.cpp \
    Gui/ListarPresupuestos.cpp \
    Gui/MainWindow.cpp \
    Gui/NuevaFacturaDialog.cpp \
    Gui/NuevoArticuloDialog.cpp \
    Gui/NuevoClienteDialog.cpp \
    Gui/NuevoPresupuestoDialog.cpp \
    Gui/PrintWindow.cpp \
    Gui/VisorAyuda.cpp \
    Gui/imprimirsobrecliente.cpp \
    Gui/main.cpp \
    Datos/AccesoADatos.cpp \
    Datos/CriterioBusqueda.cpp \
    Datos/utils.cpp
FORMS += Gui/BuscarArticuloDialog.ui \
    Gui/BuscarClienteDialog.ui \
    Gui/BuscarFacturaDialog.ui \
    Gui/BuscarPresupuestoDialog.ui \
    Gui/CambiarIvaDialog.ui \
    Gui/ConfigurarImpresora.ui \
    Gui/ListarArticulos.ui \
    Gui/ListarClientes.ui \
    Gui/ListarFacturas.ui \
    Gui/ListarPresupuestos.ui \
    Gui/NuevaFacturaDialog.ui \
    Gui/NuevoArticuloDialog.ui \
    Gui/NuevoClienteDialog.ui \
    Gui/NuevoOperarioDialog.ui \
    Gui/NuevoPresupuestoDialog.ui \
    Gui/VisorAyuda.ui \
    Gui/imprimirsobrecliente.ui
RESOURCES += 
