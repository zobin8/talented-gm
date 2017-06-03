#include "editornpccontroller.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include "svpmenumodule.h"
#include "skillmenumodule.h"
#include "svp.h"
#include "skill.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>

EditorNPCController::EditorNPCController(QObject* parent) : Controller(parent)
{
    npcTemp = new NPCTemplate();
}

EditorNPCController::~EditorNPCController()
{
    delete npcTemp;
}

void EditorNPCController::setWidgets(QWidget *editHitScrollContents, QLineEdit *editNPCName, QSpinBox *editBodySpin, QSpinBox *editCoordSpin, QSpinBox *editSenseSpin, QSpinBox *editMindSpin, QSpinBox *editCharmSpin, QSpinBox *editCommSpin, QComboBox *editNPCCombo, QWidget *editSkillScrollContents, QTextEdit* editNPCDesc)
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
    uiDescription = editNPCDesc;

    view.append(uiHitContents);
    view.append(uiSkillContents);
    view.append(uiName);
    view.append(uiBody);
    view.append(uiCoord);
    view.append(uiSense);
    view.append(uiMind);
    view.append(uiCharm);
    view.append(uiComm);
    view.append(uiCombo);
    view.append(uiDescription);

    connect(uiCombo, SIGNAL(activated(QString)), this, SLOT(on_load(QString)));
    connect(uiName, SIGNAL(textChanged(QString)), this, SLOT(on_viewUpdate()));
    connect(uiBody, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiCoord, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiSense, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiMind, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiCharm, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiComm, SIGNAL(valueChanged(int)), this, SLOT(on_viewUpdate()));
    connect(uiDescription, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
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

    npcTemp->getSkills()->clear();
    QLayout* skillLayout = uiSkillContents->layout();
    for (int i = 0; i < skillLayout->count(); i++)
    {
        QWidget* widget = skillLayout->itemAt(i)->widget();
        SkillMenuModule* menuMod = dynamic_cast<SkillMenuModule*>(widget);
        if (menuMod)
        {
            npcTemp->addSkill(menuMod->getSkill());
        }
    }

    npcTemp->setName(uiName->text());
    npcTemp->setDescription(uiDescription->toPlainText());
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
        addSVPModule(hit.getString(), hit.getValue());
    }
    foreach (Skill skill, *npcTemp->getSkills())
    {
        addSkillModule(skill.getStatName(), skill.getString(), skill.getValue());
    }


    uiName->setText(npcTemp->getName());
    uiDescription->setText(npcTemp->getDescription());
    uiBody->setValue(npcTemp->body);
    uiCoord->setValue(npcTemp->coord);
    uiSense->setValue(npcTemp->sense);
    uiMind->setValue(npcTemp->mind);
    uiCharm->setValue(npcTemp->charm);
    uiComm->setValue(npcTemp->comm);


    QStringList npcNames = QStringList();
    uiCombo->clear();
    Controller::appendToCombo("Custom", uiCombo);
    foreach (NPCTemplate* anNPC, TalentData::lockTalentFile()->getNPCTemplates())
    {
        Controller::appendToCombo(anNPC->getName(), uiCombo);
        npcNames.append(anNPC->getName());
    }
    TalentData::unlockTalentFile();

    uiCombo->setCurrentText(npcTemp->getName());
    emit setNPCNames(npcNames);
}

void EditorNPCController::fromModel()
{
    const NPCTemplate* npc = TalentData::lockTalentFile()->getCurrentNPC();
    TalentData::unlockTalentFile();

    delete npcTemp;
    npcTemp = new NPCTemplate(npc);
}

void EditorNPCController::toModel()
{
    TalentData::lockTalentFile()->setCurrentNPC(npcTemp);
    TalentData::unlockTalentFile();
}

void EditorNPCController::toTemp()
{
    tryFromView();

    NPCTemplate* temp = new NPCTemplate(npcTemp);
    TalentData::lockTalentFile()->addNPCTemplate(temp);
    TalentData::unlockTalentFile();

    tryToView();
    emit updateView(ConFreq::tempNPC);
    emit updateView(ConFreq::hash);
}

void EditorNPCController::toTurn()
{
    tryFromView();

    TalentData::lockTalentFile()->currentTurn()->addNPCTemplate(npcTemp);
    TalentData::unlockTalentFile();

    emit updateView(ConFreq::turn);
    emit updateView(ConFreq::hash);
}

void EditorNPCController::newSVPModule()
{
    addSVPModule();
    tryFromView();
    tryToModel();
}

void EditorNPCController::newSkillModule()
{
    addSkillModule();
    tryFromView();
    tryToModel();
}

void EditorNPCController::addSVPModule(QString s, double v)
{
    SVPMenuModule* module = new SVPMenuModule();
    module->addWidgets();
    module->setValue(SVP(s, v));
    module->setDecimals(0);
    module->setSortID(s);

    Controller::appendToLayout(module, uiHitContents->layout());

    connect(module, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteModule(MenuModule*)));
}

void EditorNPCController::addSkillModule(QString n, QString s, double v)
{
    SkillMenuModule* module = new SkillMenuModule();
    module->addWidgets();
    module->setSkill(Skill(n, s, v));
    module->setDecimals(0);
    module->setSortID(s);

    Controller::appendToLayout(module, uiSkillContents->layout());

    connect(module, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteModule(MenuModule*)));
}

void EditorNPCController::on_load(QString name)
{
    const NPCTemplate* npc = TalentData::lockTalentFile()->getNPCFromName(name);
    TalentData::unlockTalentFile();

    delete npcTemp;
    if (npc)
    {
        npcTemp = new NPCTemplate(npc);
    }
    else
    {
        npcTemp = new NPCTemplate();
    }

    tryToModel();
    tryToView();
}

void EditorNPCController::deleteModule(MenuModule* menuMod)
{
    QVBoxLayout* hitLayout = static_cast<QVBoxLayout*>(uiHitContents->layout());
    hitLayout->removeWidget(menuMod);

    QVBoxLayout* skillLayout = static_cast<QVBoxLayout*>(uiSkillContents->layout());
    skillLayout->removeWidget(menuMod);

    delete menuMod;

    tryFromView();
    tryToModel();
}
