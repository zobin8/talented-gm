#include "editornpccontroller.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "svpmenumodule.h"
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
        addHitBox(hit.string, hit.value);
    }
    foreach (SVP skill, *npcTemp->getSkills())
    {
        addSkill(skill.string, skill.value);
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

    //TODO: There is a better way to do this. I can't think of it right now.
    toView();
}

void EditorNPCController::toTemplate()
{
    fromView();

    NPCTemplate* temp = new NPCTemplate(npcTemp);
    TalentData::getInstance().addNPCTemplate(temp);

    toView();
    emit update();
}

void EditorNPCController::addHitBox(QString s, double v)
{
    SVPMenuModule* hitModule = new SVPMenuModule();
    hitModule->setValue(SVP(s, v));

    QVBoxLayout* hitLayout = (QVBoxLayout*) uiHitContents->layout();
    int index = hitLayout->count();
    hitLayout->insertWidget(index, hitModule);

    connect(hitModule, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteHitBox(MenuModule*)));
}

void EditorNPCController::deleteHitBox(MenuModule* menuMod)
{
    QVBoxLayout* hitLayout = (QVBoxLayout*) uiHitContents->layout();
    hitLayout->removeWidget(menuMod);
    delete menuMod;
}

//TODO: Does this function really need to be different from addHitBox()?
void EditorNPCController::addSkill(QString s, double v)
{
    SVPMenuModule* skillModule = new SVPMenuModule();
    skillModule->setValue(SVP(s, v));

    QVBoxLayout* skillLayout = (QVBoxLayout*) uiSkillContents->layout();
    int index = skillLayout->count();
    skillLayout->insertWidget(index, skillModule);

    connect(skillModule, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteSkill(MenuModule*)));
}

//TODO: Does this function really need to be different from deleteHitBox()?
void EditorNPCController::deleteSkill(MenuModule* menuMod)
{
    QVBoxLayout* skillLayout = (QVBoxLayout*) uiSkillContents->layout();
    skillLayout->removeWidget(menuMod);
    delete menuMod;
}
