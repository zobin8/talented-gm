#include "menumodule.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
//#include <QObjectList>

MenuModule::MenuModule(QWidget* parent) : QFrame(parent)
{
    layout = new QHBoxLayout(this);
}

MenuModule::~MenuModule()
{
    while (layout->count() > 0)
    {
        QLayoutItem* child = layout->itemAt(0);
        layout->removeItem(child);
        delete child;
    }
    delete layout;
}

QLineEdit* MenuModule::addLineEdit(QString aString)
{
    QLineEdit* out = new QLineEdit(aString);
    layout->addWidget(out);
    return out;
}

QLabel* MenuModule::addLabel(QString aString)
{
    QLabel* out = new QLabel(aString);
    layout->addWidget(out);
    return out;
}

QPushButton* MenuModule::addButton(QString aString)
{
    QPushButton* out = new QPushButton(aString);
    layout->addWidget(out);
    return out;
}

QSpinBox* MenuModule::addSpinBox(int anInt)
{
    QSpinBox* out = new QSpinBox();
    out->setValue(anInt);
    layout->addWidget(out);
    return out;
}

QDoubleSpinBox* MenuModule::addDoubleSpinBox(double aDouble)
{
    QDoubleSpinBox* out = new QDoubleSpinBox();
    out->setValue(aDouble);
    layout->addWidget(out);
    return out;
}
