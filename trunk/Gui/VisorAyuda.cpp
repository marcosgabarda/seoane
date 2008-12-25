#include "VisorAyuda.h"

VisorAyuda::VisorAyuda(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
	ui.textBrowser->setSource(QUrl("Ayuda/ayuda.html"));
}

VisorAyuda::~VisorAyuda()
{

}

void VisorAyuda::resizeEvent(QResizeEvent *event) {
	ui.gridLayout->setGeometry(QRect(0, 0, event->size().width(), event->size().height()));
}
