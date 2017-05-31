#include "editorloccontroller.h"
#include "loctemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include "menumodule.h"
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

EditorLocController::EditorLocController(QObject *parent) : Controller(parent)
{
    locTemp = new LocTemplate();
}

EditorLocController::~EditorLocController()
{
    delete locTemp;
}

void EditorLocController::setWidgets(QComboBox *editLocationCombo, QLineEdit *editLocationName, QSpinBox *editMinionSpin1, QSpinBox *editMinionSpin2, QWidget* editLocContents, QComboBox* editLocNPCCombo, QTextEdit* editLocDesc)
{
    uiCombo = editLocationCombo;
    uiName = editLocationName;
    uiMinions1 = editMinionSpin1;
    uiMinions2 = editMinionSpin2;
    uiNPCWidget = editLocContents;
    uiNPCCombo = editLocNPCCombo;
    uiDescription = editLocDesc;
}

void EditorLocController::addNPCModule(QString name)
{
    if (name == "")
    {
        name = uiNPCCombo->currentText();
    }

    NPCTemplate* npc = TalentData::getTalentFile()->getNPCFromName(name);
    if (npc)
    {
        MenuModule* menMod = new MenuModule();
        menMod->addWidgets();
        menMod->setDeleteText("Delete NPC: " + name);
        menMod->setIdentifier(name);
        menMod->setSortID(name);

        Controller::appendToLayout(menMod, uiNPCWidget->layout());

        connect(menMod, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteNPC(MenuModule*)));
    }
}

void EditorLocController::deleteNPC(MenuModule* menMod)
{
    QVBoxLayout* npcLayout = (QVBoxLayout*) uiNPCWidget->layout();
    npcLayout->removeWidget(menMod);
    delete menMod;
}

void EditorLocController::toView()
{
    uiCombo->clear();
    Controller::appendToCombo("Custom", uiCombo);
    foreach (LocTemplate* aLoc, TalentData::getTalentFile()->getLocTemplates())
    {
        Controller::appendToCombo(aLoc->getName(), uiCombo);
    }
    uiCombo->setCurrentText(locTemp->getName());

    QLayout* npcLayout = uiNPCWidget->layout();
    Controller::clearLayout(npcLayout);

    foreach (NPCTemplate* npc, locTemp->NPCs())
    {
        addNPCModule(npc->getName());
    }

    uiName->setText(locTemp->getName());
    uiDescription->setText(locTemp->getDescription());
    uiMinions1->setValue(locTemp->minions1);
    uiMinions2->setValue(locTemp->minions2);
}

void EditorLocController::fromModel()
{
    QString name = uiCombo->currentText();
    LocTemplate* loc = TalentData::getTalentFile()->getLocFromName(name);

    delete locTemp;
    if (loc)
    {
        locTemp = new LocTemplate(loc);
    }
    else
    {
        locTemp = new LocTemplate();
    }
}

void EditorLocController::fromView()
{
    locTemp->setName(uiName->text());
    locTemp->setDescription(uiDescription->toPlainText());
    locTemp->minions1 = uiMinions1->value();
    locTemp->minions2 = uiMinions2->value();

    locTemp->NPCs().clear();
    QLayout* npcLayout = uiNPCWidget->layout();
    for (int i = 0; i < npcLayout->count(); i++)
    {
        QWidget* widget = npcLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            QString name = menuMod->getIdentifier();

            NPCTemplate* npc = TalentData::getTalentFile()->getNPCFromName(name);

            if (npc)
            {
                locTemp->addNPC(npc);
            }
        }
    }
}

void EditorLocController::toModel()
{
    fromView();

    LocTemplate* temp = new LocTemplate(locTemp);
    TalentData::getTalentFile()->addLocTemplate(temp);

    toView();
    emit update();
    emit unsavedChange();
}

void EditorLocController::toTurn()
{
    fromView();

    TalentData::getTalentFile()->currentTurn()->setLocTemplate(locTemp);
    TalentData::getInstance().getTalentFile()->resetInitiative();

    emit viewNPC(NULL);
    emit update();
    emit unsavedChange();
}

void EditorLocController::on_NPCNamesChanged(QStringList names)
{
    QString current = uiNPCCombo->currentText();

    uiNPCCombo->clear();
    foreach (QString name, names)
    {
        Controller::appendToCombo(name, uiNPCCombo);
    }

    uiNPCCombo->setCurrentText(current);
}

