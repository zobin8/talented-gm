#include "temploccontroller.h"
#include "loctemplate.h"
#include "menumodule.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QLayout>
#include <QVBoxLayout>

TempLocController::TempLocController(QObject *parent) : Controller(parent)
{
    locTemplates = QLinkedList<LocTemplate*>();
}

void TempLocController::setWidgets(QWidget* tempLocContents)
{
    uiLocContents = tempLocContents;
    view.append(uiLocContents);
}

void TempLocController::toView()
{
    QLayout* lay = uiLocContents->layout();
    Controller::clearLayout(lay);

    foreach (LocTemplate* loc, locTemplates)
    {
        MenuModule* locMod = new MenuModule();
        locMod->addWidgets();
        locMod->requireConfirmation();
        locMod->setDeleteText("Delete Location: " + loc->getName());
        locMod->setIdentifier(loc->getName());
        locMod->setSortID(loc->getName());

        Controller::appendToLayout(locMod, uiLocContents->layout());

        connect(locMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
    }
}

void TempLocController::fromModel()
{
    QLinkedList<LocTemplate*> model = TalentData::lockTalentFile()->getLocTemplates();
    locTemplates = QLinkedList<LocTemplate*>(model);
    TalentData::unlockTalentFile();
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
            LocTemplate* loc = TalentData::lockTalentFile()->getLocFromName(name);

            if (loc)
            {
                locTemplates.append(loc);
            }

            TalentData::unlockTalentFile();
        }
    }
}

void TempLocController::toModel()
{
    TalentData::lockTalentFile()->setLocTemplates(locTemplates);
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::editLoc);
}

void TempLocController::on_deletionEvent(MenuModule* menMod)
{
    uiLocContents->layout()->removeWidget(menMod);
    menMod->deleteLater();

    tryFromView();
    tryToModel();
}
