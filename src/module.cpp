#include "module.h"
#include <QHBoxLayout>
#include <QString>

Module::Module(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    sortID = "";
}

Module::~Module()
{
    delete layout;
}

void Module::setSortID(QString anID)
{
    sortID = anID.toLower();
}
