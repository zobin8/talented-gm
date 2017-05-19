#include "menumodule.h"
#include "stringvaluepair.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

MenuModule::MenuModule(QWidget* parent) : QFrame(parent)
{
    layout = new QHBoxLayout(this);
    spin = new QDoubleSpinBox();
    edit = new QLineEdit();
    del = new QPushButton();

    layout->addWidget(spin);
    layout->addWidget(edit);
    layout->addWidget(del);
}

MenuModule::~MenuModule()
{
    delete layout;
    delete spin;
    delete edit;
    delete del;
}

SVP MenuModule::getValue()
{
    double v = spin->value();
    QString s = edit->text();
    SVP svp(s, v);
    return svp;
}

void MenuModule::setValue(SVP svp)
{
    spin->setValue(svp.value);
    edit->setText(svp.string);
}
