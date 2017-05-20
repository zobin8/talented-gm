#include "editornpccontroller.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "menumodule.h"
#include "stringvaluepair.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>

EditorNPCController::EditorNPCController(QObject* parent) : Controller(parent)
{
    npcTemp = new NPCTemplate();
}

EditorNPCController::~EditorNPCController()
{
    delete npcTemp;
}

void EditorNPCController::setWidgets(QWidget *editHitScrollContents, QLineEdit *editNPCName, QSpinBox *editBodySpin, QSpinBox *editCoordSpin, QDoubleSpinBox *editSenseSpin, QSpinBox *editMindSpin, QSpinBox *editCharmSpin, QSpinBox *editCommSpin, QComboBox *editNPCCombo)
{
    uiHitContents = editHitScrollContents;
    uiName = editNPCName;
    uiBody = editBodySpin;
    uiCoord = editCoordSpin;
    uiSense = editSenseSpin;
    uiMind = editMindSpin;
    uiCharm = editCharmSpin;
    uiComm = editCommSpin;
    uiCombo = editNPCCombo;
}

void EditorNPCController::fromView()
{
    npcTemp->getHitBoxes()->clear();
    QLayout* hitLayout = uiHitContents->layout();
    for (int i = 0; i < hitLayout->count(); i++)
    {
        QWidget* widget = hitLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            npcTemp->addHitBox(menuMod->getValue());
        }
    }

    npcTemp->setName(uiName->text());
    npcTemp->body = uiBody->value();
    npcTemp->coord = uiCoord->value();
    npcTemp->sense = uiSense->value();
    npcTemp->mind = uiMind->value();
    npcTemp->charm = uiCharm->value();
    npcTemp->comm = uiComm->value();
}

void EditorNPCController::toView()
{
    QLayout* hitLayout = uiHitContents->layout();
    while (hitLayout->count() > 0)
    {
        QWidget* w =  hitLayout->itemAt(0)->widget();
        hitLayout->removeWidget(w);
        delete w;
    }

    foreach(SVP hit, *(npcTemp->getHitBoxes()))
    {
        addHitBox(hit.string, hit.value);
    }

    uiName->setText(npcTemp->getName());
    uiBody->setValue(npcTemp->body);
    uiCoord->setValue(npcTemp->coord);
    uiSense->setValue(npcTemp->sense);
    uiMind->setValue(npcTemp->mind);
    uiCharm->setValue(npcTemp->charm);
    uiComm->setValue(npcTemp->comm);

    uiCombo->clear();
    uiCombo->addItem("Custom");
    foreach (NPCTemplate* anNPC, TalentData::getInstance().getNPCTemplates())
    {
        uiCombo->addItem(anNPC->getName());
    }
    uiCombo->setCurrentText(npcTemp->getName());
}

void EditorNPCController::fromModel()
{
    QString name = uiCombo->currentText();
    NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);

    delete npcTemp;
    if (npc)
    {
        npcTemp = new NPCTemplate(npc);
    }
    else
    {
        npcTemp = new NPCTemplate();
    }

    //TODO: There is a better way to do this. I can't think of it right now.
    toView();
}

void EditorNPCController::toTemplate()
{
    fromView();

    NPCTemplate* temp = new NPCTemplate(npcTemp);
    TalentData::getInstance().addNPCTemplate(temp);
    toView();
}

void EditorNPCController::addHitBox(QString s, double v)
{
    MenuModule* hitModule = new MenuModule();
    hitModule->setValue(SVP(s, v));

    QVBoxLayout* hitLayout = (QVBoxLayout*) uiHitContents->layout();
    int index = hitLayout->count() - 1;
    hitLayout->insertWidget(index, hitModule);

    connect(hitModule, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteHitBox(MenuModule*)));
}

void EditorNPCController::deleteHitBox(MenuModule* menuMod)
{
    QVBoxLayout* hitLayout = (QVBoxLayout*) uiHitContents->layout();
    hitLayout->removeWidget(menuMod);
    delete menuMod;
}
