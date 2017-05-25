#include "menumodule.h"
#include <QPushButton>
#include <QHBoxLayout>

MenuModule::MenuModule(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    del = new QPushButton("Delete");

    del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->setContentsMargins(0, 0, 0, 0);

    connect(del, SIGNAL(clicked()), this, SLOT(on_deletionEvent()));
}

void MenuModule::addWidgets()
{
    layout->addWidget(del);
}

MenuModule::~MenuModule()
{
    delete layout;
    delete del;
}

void MenuModule::setDeleteText(QString text)
{
    del->setText(text);
}

QPushButton* MenuModule::getDeleteButton()
{
    return del;
}

void MenuModule::on_deletionEvent()
{
    emit killMe(this);
}

void MenuModule::setIdentifier(QString i)
{
    identifier = i;
}

QString MenuModule::getIdentifier()
{
    return identifier;
}
