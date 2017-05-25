#include "controller.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QWidget>

Controller::Controller(QObject* parent) : QObject(parent)
{

}

void Controller::on_update()
{
    fromModel();
    toView();
}

void Controller::clearLayout(QLayout* lay)
{
    while (lay->count() > 0)
    {
        QWidget* w =  lay->itemAt(0)->widget();
        lay->removeWidget(w);
        delete w;
    }
}

void Controller::appendToLayout(QWidget* w, QLayout* l)
{
    QVBoxLayout* vLayout = static_cast<QVBoxLayout*>(l);
    vLayout->addWidget(w);
}
