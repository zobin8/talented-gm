#include "menumodule.h"
#include "stringvaluepair.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

MenuModule::MenuModule(QWidget* parent, int decimals) : QFrame(parent)
{
    layout = new QHBoxLayout(this);
    spin = new QDoubleSpinBox();
    edit = new QLineEdit();
    del = new QPushButton("Delete");

    spin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(spin);
    layout->addWidget(edit);
    layout->addWidget(del);

    layout->setContentsMargins(9, 0, 9, 0);

    spin->setDecimals(decimals);
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
};

void MenuModule::setValue(SVP svp)
{
    spin->setValue(svp.value);
    edit->setText(svp.string);
}
