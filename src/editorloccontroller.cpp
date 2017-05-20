#include "editorloccontroller.h"
#include "locationtemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "menumodule.h"
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>

EditorLocController::EditorLocController(QObject *parent) : Controller(parent)
{
    locTemp = new LocationTemplate();
}

EditorLocController::~EditorLocController()
{
    delete locTemp;
}

void EditorLocController::setWidgets(QComboBox *editLocationCombo, QLineEdit *editLocationName, QSpinBox *editMinionSpin1, QSpinBox *editMinionSpin2, QWidget* editLocContents, QComboBox* editLocNPCCombo)
{
    uiCombo = editLocationCombo;
    uiName = editLocationName;
    uiMinions1 = editMinionSpin1;
    uiMinions2 = editMinionSpin2;
    uiNPCWidget = editLocContents;
    uiNPCCombo = editLocNPCCombo;
}

void EditorLocController::addNPCModule(QString name)
{
    if (name == "")
    {
        name = uiNPCCombo->currentText();
    }

    NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);
    if (npc)
    {
        MenuModule* menMod = new MenuModule();
        menMod->setDeleteText("Delete NPC: " + name);

        QVBoxLayout* npcLayout = (QVBoxLayout*) uiNPCWidget->layout();
        int index = npcLayout->count();
        npcLayout->insertWidget(index, menMod);

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
    uiCombo->addItem("Custom");
    foreach (LocationTemplate* aLoc, TalentData::getInstance().getLocTemplates())
    {
        uiCombo->addItem(aLoc->getName());
    }
    uiCombo->setCurrentText(locTemp->getName());

    QLayout* npcLayout = uiNPCWidget->layout();
    while (npcLayout->count() > 0)
    {
        QWidget* w =  npcLayout->itemAt(0)->widget();
        npcLayout->removeWidget(w);
        delete w;
    }

    foreach (NPCTemplate* npc, locTemp->getNPCs())
    {
        addNPCModule(npc->getName());
    }

    uiName->setText(locTemp->getName());
    uiMinions1->setValue(locTemp->minions1);
    uiMinions2->setValue(locTemp->minions2);
}

void EditorLocController::fromModel()
{
    QString name = uiCombo->currentText();
    LocationTemplate* loc = TalentData::getInstance().getLocFromName(name);

    delete locTemp;
    if (loc)
    {
        locTemp = new LocationTemplate(loc);
    }
    else
    {
        locTemp = new LocationTemplate();
    }

    //TODO: See EditorNPCController::fromModel()
    toView();
}

void EditorLocController::fromView()
{
    locTemp->setName(uiName->text());
    locTemp->minions1 = uiMinions1->value();
    locTemp->minions2 = uiMinions2->value();

    locTemp->getNPCs().clear();
    QLayout* npcLayout = uiNPCWidget->layout();
    for (int i = 0; i < npcLayout->count(); i++)
    {
        QWidget* widget = npcLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            QString name = menuMod->getDeleteButton()->text();
            name.remove("Delete NPC: ");

            NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);

            if (npc)
            {
                locTemp->addNPC(npc);
            }
        }
    }
}

void EditorLocController::toTemplate()
{
    fromView();

    LocationTemplate* temp = new LocationTemplate(locTemp);
    TalentData::getInstance().addLocTemplate(temp);

    toView();
}

void EditorLocController::on_NPCNamesChanged(QStringList names)
{
    QString current = uiNPCCombo->currentText();

    uiNPCCombo->clear();
    uiNPCCombo->addItems(names);

    uiNPCCombo->setCurrentText(current);
}
