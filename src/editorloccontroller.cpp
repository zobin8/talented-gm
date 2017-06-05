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

    view.append(uiCombo);
    view.append(uiName);
    view.append(uiMinions1);
    view.append(uiMinions2);
    view.append(uiNPCWidget);
    view.append(uiNPCCombo);
    view.append(uiDescription);

    connect(uiCombo, SIGNAL(activated(QString)), this, SLOT(on_load(QString)));
    connect(uiName, SIGNAL(textChanged(QString)), this, SLOT(on_viewUpdate()));
    connect(uiMinions1, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiMinions2, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiDescription, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
}

void EditorLocController::newNPCModule()
{
    addNPCModule();
    tryFromView();
    tryToModel();
}

void EditorLocController::addNPCModule(QString name)
{
    if (name == "")
    {
        name = uiNPCCombo->currentText();
    }

    NPCTemplate* npc = TalentData::lockTalentFile()->getNPCFromName(name);
    TalentData::unlockTalentFile();
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
    tryFromView();
    tryToModel();
}

void EditorLocController::toView()
{
    uiCombo->clear();
    Controller::appendToCombo("Custom", uiCombo);
    foreach (LocTemplate* aLoc, TalentData::lockTalentFile()->getLocTemplates())
    {
        Controller::appendToCombo(aLoc->getName(), uiCombo);
    }
    TalentData::unlockTalentFile();

    uiCombo->setCurrentText(locTemp->getName());

    QLayout* npcLayout = uiNPCWidget->layout();
    Controller::clearLayout(npcLayout);

    foreach (QString npc, locTemp->NPCs())
    {
        addNPCModule(npc);
    }

    uiName->setText(locTemp->getName());
    uiDescription->setText(locTemp->getDescription());
    uiMinions1->setValue(locTemp->minions1);
    uiMinions2->setValue(locTemp->minions2);
}

void EditorLocController::fromModel()
{
    const LocTemplate* loc = TalentData::lockTalentFile()->getCurrentLoc();
    TalentData::unlockTalentFile();

    delete locTemp;
    locTemp = new LocTemplate(loc);
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

            NPCTemplate* npc = TalentData::lockTalentFile()->getNPCFromName(name);
            TalentData::unlockTalentFile();

            if (npc)
            {
                locTemp->addNPC(name);
            }
        }
    }
}

void EditorLocController::toModel()
{
    TalentData::lockTalentFile()->setCurrentLoc(locTemp);
    TalentData::unlockTalentFile();
}

void EditorLocController::on_load(QString name)
{
    const LocTemplate* loc = TalentData::lockTalentFile()->getLocFromName(name);
    TalentData::unlockTalentFile();

    delete locTemp;
    if (loc)
    {
        locTemp = new LocTemplate(loc);
    }
    else
    {
        locTemp = new LocTemplate();
    }

    tryToModel();
    tryToView();
}

void EditorLocController::toTemp()
{
    tryFromView();

    LocTemplate* temp = new LocTemplate(locTemp);
    TalentData::lockTalentFile()->addLocTemplate(temp);
    TalentData::unlockTalentFile();

    tryToView();
    emit updateView(ConFreq::tempLoc);
    emit updateView(ConFreq::hash);
}

void EditorLocController::toTurn()
{
    tryFromView();

    TalentFile* file = TalentData::lockTalentFile();
    file->currentTurn()->setLocTemplate(locTemp);
    file->resetInitiative();
    TalentData::unlockTalentFile();

    emit viewNPC(NULL);
    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
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

