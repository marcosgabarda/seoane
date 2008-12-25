#ifndef CONFIGURARIMPRESORA_H
#define CONFIGURARIMPRESORA_H

#include <QtGui/QWidget>
#include "ui_ConfigurarImpresora.h"

class ConfigurarImpresora : public QWidget
{
    Q_OBJECT

public:
    ConfigurarImpresora(QWidget *parent = 0);
    ~ConfigurarImpresora();
    
private slots:
	void GuardarCambios();

private:
    Ui::ConfigurarImpresoraClass ui;
    QStringList listaOpciones;
};

#endif // CONFIGURARIMPRESORA_H
