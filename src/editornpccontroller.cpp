#include "editornpccontroller.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "svpmenumodule.h"
#include "svp.h"
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

void EditorNPCController::setWidgets(QWidget *editHitScrollContents, QLineEdit *editNPCName, QSpinBox *editBodySpin, QSpinBox *editCoordSpin, QDoubleSpinBox *editSenseSpin, QSpinBox *editMindSpin, QSpinBox *editCharmSpin, QSpinBox *editCommSpin, QComboBox *editNPCCombo, QWidget *editSkillScrollContents)
{
    uiHitContents = editHitScrollContents;
    uiSkillContents = editSkillScrollContents;
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
        SVPMenuModule* menuMod = dynamic_cast<SVPMenuModule*>(widget);
        if (menuMod)
        {
            npcTemp->addHitBox(menuMod->getValue());
        }
    }

    //TODO: Make this cleaner. Maybe a function?
    npcTemp->getSkills()->clear();
    QLayout* skillLayout = uiSkillContents->layout();
    for (int i = 0; i < skillLayout->count(); i++)
    {
        QWidget* widget = skillLayout->itemAt(i)->widget();
        SVPMenuModule* menuMod = dynamic_cast<SVPMenuModule*>(widget);
        if (menuMod)
        {
            npcTemp->addSkill(menuMod->getValue());
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
    Controller::clearLayout(hitLayout);

    QLayout* skillLayout = uiSkillContents->layout();
    Controller::clearLayout(skillLayout);

    foreach(SVP hit, *(npcTemp->getHitBoxes()))
    {
        addModule(uiHitContents, hit.string, hit.value);
    }
    foreach (SVP skill, *npcTemp->getSkills())
    {
        addModule(uiSkillContents, skill.string, skill.value);
    }

    uiName->setText(npcTemp->getName());
    uiBody->setValue(npcTemp->body);
    uiCoord->setValue(npcTemp->coord);
    uiSense->setValue(npcTemp->sense);
    uiMind->setValue(npcTemp->mind);
    uiCharm->setValue(npcTemp->charm);
    uiComm->setValue(npcTemp->comm);

    QStringList npcNames = QStringList();
    uiCombo->clear();
    uiCombo->addItem("Custom");
    foreach (NPCTemplate* anNPC, TalentData::getInstance().getNPCTemplates())
    {
        uiCombo->addItem(anNPC->getName());
        npcNames.append(anNPC->getName());
    }
    uiCombo->setCurrentText(npcTemp->getName());
    emit setNPCNames(npcNames);
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
}

void EditorNPCController::toTemplate()
{
    fromView();

    NPCTemplate* temp = new NPCTemplate(npcTemp);
    TalentData::getInstance().addNPCTemplate(temp);

    toView();
    emit update();
}

void EditorNPCController::addModule(QWidget* contents, QString s, double v)
{
    SVPMenuModule* module = new SVPMenuModule();
    module->setValue(SVP(s, v));
    module->setDecimals(0);

    Controller::appendToLayout(module, contents->layout());

    connect(module, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteModule(MenuModule*)));
}

void EditorNPCController::deleteModule(MenuModule* menuMod)
{
    QVBoxLayout* hitLayout = static_cast<QVBoxLayout*>(uiHitContents->layout());
    hitLayout->removeWidget(menuMod);

    QVBoxLayout* skillLayout = static_cast<QVBoxLayout*>(uiSkillContents->layout());
    skillLayout->removeWidget(menuMod);

    delete menuMod;
}
