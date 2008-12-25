#ifndef IMPRIMIRSOBRECLIENTE_H
#define IMPRIMIRSOBRECLIENTE_H

#include <QtGui/QWidget>
#include "ui_imprimirsobrecliente.h"
#include "../Negocio/CapaNegocio.h"
#include <list>
#include "../Negocio/Cliente.h"



class ImprimirSobreCliente : public QWidget
{
    Q_OBJECT

public:
    ImprimirSobreCliente(QWidget *parent = 0,CapaNegocio *cn = 0);
    ~ImprimirSobreCliente();

public slots:
	void aceptar();

private:
    Ui::ImprimirSobreClienteClass ui;
    CapaNegocio *capaNegocio;
    
   
};

#endif // IMPRIMIRSOBRECLIENTE_H
