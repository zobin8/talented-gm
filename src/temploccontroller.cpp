#include "temploccontroller.h"
#include "locationtemplate.h"
#include "menumodule.h"
#include "talentdata.h"
#include <QLayout>
#include <QVBoxLayout>

TempLocController::TempLocController(QObject *parent) : Controller(parent)
{
    locTemplates = QLinkedList<LocationTemplate*>();
}

void TempLocController::setWidgets(QWidget* tempLocContents)
{
    uiLocContents = tempLocContents;
}

void TempLocController::toView()
{
    QLayout* lay = uiLocContents->layout();
    Controller::clearLayout(lay);

    foreach (LocationTemplate* loc, locTemplates)
    {
        MenuModule* locMod = new MenuModule();
        locMod->setDeleteText("Delete location: " + loc->getName());
        locMod->setIdentifier(loc->getName());

        QVBoxLayout* locLayout = static_cast<QVBoxLayout*>(uiLocContents->layout());
        int i = locLayout->count();
        locLayout->insertWidget(i, locMod);

        connect(locMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
    }
}

void TempLocController::fromModel()
{
    QLinkedList<LocationTemplate*> model = TalentData::getInstance().getLocTemplates();
    locTemplates = QLinkedList<LocationTemplate*>(model);
}

void TempLocController::fromView()
{
    locTemplates.clear();
    QLayout* locLayout = uiLocContents->layout();
    for (int i = 0; i < locLayout->count(); i++)
    {
        QWidget* widget = locLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            QString name = menuMod->getIdentifier();
            LocationTemplate* loc = TalentData::getInstance().getLocFromName(name);

            if (loc)
            {
                locTemplates.append(loc);
            }
        }
    }
}

void TempLocController::toModel()
{
    TalentData::getInstance().setLocTemplates(locTemplates);

    emit update();
}

void TempLocController::on_deletionEvent(MenuModule* menMod)
{
    uiLocContents->layout()->removeWidget(menMod);
    delete menMod;

    fromView();
    toModel();
}
