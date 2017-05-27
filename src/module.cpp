#include "module.h"
#include <QHBoxLayout>
#include <QString>

Module::Module(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    sortID = "";
    sort = false;
}

Module::~Module()
{
    delete layout;
}

void Module::setSortID(QString anID)
{
    sortID = anID.toLower();
    sort = true;
}

QString Module::getSortID()
{
    return sortID;
}

bool Module::needsSort()
{
    return sort;
}
