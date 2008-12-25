#include "ConfigurarImpresora.h"
#include <fstream>
#include <iostream>
#include <string>
#include <QtGui>
#include <cstdlib>

using namespace std;

ConfigurarImpresora::ConfigurarImpresora(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(GuardarCambios()));

	listaOpciones << "LPT1";
	listaOpciones << "LPT2";
	listaOpciones << "LPT3";
	listaOpciones << "COM1";
	listaOpciones << "COM2";
	listaOpciones << "COM3";
	listaOpciones << "COM4";
	listaOpciones << "USB001";
	listaOpciones << "XPSPort";
	
	ui.comboBox->addItems(listaOpciones);
	
	fstream fileConfig;
	fileConfig.open("Gui/printer.cfg", fstream::in);
	if (fileConfig.fail()) {
		QMessageBox::critical(this, "Error", "Error al abrir el archivo de configuración de impresoras.");
		return ;
	}
	string name, value;
	while (!fileConfig.eof()) {
		fileConfig >> name >> value;
		if (name == "Manual") {
			if (value == "true") {
				ui.checkBox->setCheckState(Qt::Checked);				
			} else if (value == "false") {
				ui.checkBox->setCheckState(Qt::Unchecked);
			} else {
				ui.checkBox->setCheckState(Qt::Unchecked);
			}
		} else if (name == "Puerto") {
			int index = listaOpciones.indexOf(QString(value.c_str()));
			ui.comboBox->setCurrentIndex(index);
		} else if (name == "Largo") {
			ui.spinBox->setValue(atoi(value.c_str()));
		} else if (name == "Ancho") {
			ui.spinBox_2->setValue(atoi(value.c_str()));
		}
	}
	fileConfig.close();
}

ConfigurarImpresora::~ConfigurarImpresora()
{
	
}
/* Guarda los cambios de configuracion. */
void ConfigurarImpresora::GuardarCambios () {
	fstream fileConfig;
	fileConfig.open("Gui/printer.cfg", fstream::out);
	if (ui.checkBox->isChecked()) {
		fileConfig << "Manual\ttrue" << endl;
	} else {
		fileConfig << "Manual\tfalse" << endl;
	}
	fileConfig << "Puerto\t" << ui.comboBox->currentText().toStdString() << endl; 
	fileConfig << "Largo\t" << ui.spinBox->value() << endl;
	fileConfig << "Ancho\t" << ui.spinBox_2->value() << endl;
	fileConfig.close();
	this->close();
}
