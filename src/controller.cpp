#include "controller.h"
#include "module.h"
#include "talentdata.h"
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

void Controller::appendToLayout(Module* insertedModule, QLayout* l)
{
    QVBoxLayout* vLayout = static_cast<QVBoxLayout*>(l);

    if (insertedModule->needsSort())
    {
        if (insertedModule->getSortID() == "")
        {
            vLayout->addWidget(insertedModule);
            return;
        }
        else
        {
            for (int i = 0; i < vLayout->count(); i++)
            {
                QWidget* w = vLayout->itemAt(i)->widget();
                Module* module = dynamic_cast<Module*>(w);
                if (module)
                {
                    if (module->needsSort())
                    {
                        int compare = TalentData::smartStringCompare(insertedModule->getSortID(), module->getSortID());
                        if (compare < 0)
                        {
                            vLayout->insertWidget(i, insertedModule);
                            return;
                        }
                    }
                }
            }
            vLayout->addWidget(insertedModule);
        }
    }
    else
    {
        vLayout->addWidget(insertedModule);
    }
}
