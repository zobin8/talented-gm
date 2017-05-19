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
    del = new QPushButton("Delete");

    spin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->addWidget(spin);
    layout->addWidget(edit);
    layout->addWidget(del);

    layout->setContentsMargins(9, 0, 9, 0);

    connect(del, SIGNAL(clicked()), this, SLOT(on_deletionEvent()));
}

MenuModule::~MenuModule()
{
    delete layout;
    delete spin;
    delete edit;
    delete del;
}

void MenuModule::setDecimals(int d)
{
    spin->setDecimals(d);
}

QPushButton* MenuModule::getDeleteButton()
{
    return del;
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

void MenuModule::on_deletionEvent()
{
    emit killMe(this);
}
