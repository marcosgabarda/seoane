#ifndef VISORAYUDA_H
#define VISORAYUDA_H

#include <QtGui>
#include "ui_VisorAyuda.h"

class VisorAyuda : public QWidget
{
    Q_OBJECT

public:
    VisorAyuda(QWidget *parent = 0);
    ~VisorAyuda();

private:
    Ui::VisorAyudaClass ui;
protected:
	void resizeEvent(QResizeEvent *event);
};

#endif // VISORAYUDA_H
