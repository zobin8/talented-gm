#include "turninfocontroller.h"
#include "npc.h"
#include "svp.h"
#include "skill.h"
#include <QLayout>
#include <QLabel>
#include <QTextEdit>

TurnInfoController::TurnInfoController(QObject *parent) : Controller(parent)
{
    npc = NULL;
}

TurnInfoController::~TurnInfoController()
{
    delete npc;
}

void TurnInfoController::setWidgets(QWidget *turnStatContents, QWidget *turnSkillContents, QTextEdit* turnNPCDesc)
{
    uiSkills = turnSkillContents;
    uiStats = turnStatContents;
    uiDesc = turnNPCDesc;

    view.append(uiSkills);
    view.append(uiStats);
    view.append(uiDesc);
}

void TurnInfoController::toView()
{
    QLayout* skills = uiSkills->layout();
    QLayout* stats = uiStats->layout();

    Controller::clearLayout(skills);
    Controller::clearLayout(stats);

    uiDesc->setText("");

    if (npc)
    {
        int baseWill = npc->comm + npc->charm;

        QString bodyString = "Body: " + QString::number(npc->body);
        stats->addWidget(new QLabel(bodyString));

        QString coordString = "Coordination: " + QString::number(npc->coord);
        stats->addWidget(new QLabel(coordString));

        QString senseString = "Sense: " + QString::number(npc->sense);
        stats->addWidget(new QLabel(senseString));

        QString mindString = "Mind: " + QString::number(npc->mind);
        stats->addWidget(new QLabel(mindString));

        QString charmString = "Charm: " + QString::number(npc->charm);
        stats->addWidget(new QLabel(charmString));

        QString commString = "Command: " + QString::number(npc->comm);
        stats->addWidget(new QLabel(commString));

        QString willString = "Base will: " + QString::number(baseWill);
        stats->addWidget(new QLabel(willString));

        foreach (Skill skill, *npc->getSkills())
        {
            int dice = npc->getSkillDice(skill);
            QString skillString = skill.getString();
            QString valueString = QString::number(skill.getValue());
            QString diceString = QString::number(dice);

            QString string = skillString + ": " + valueString + " (" + diceString + "D)";
            Controller::appendToLayout(string, skills);
        }

        uiDesc->setText(npc->getDescription());
    }
}

void TurnInfoController::toModel()
{
    //No action. View only.
}

void TurnInfoController::fromModel()
{
    //No action. View only.
}

void TurnInfoController::fromView()
{
    //No action. View only.
}

void TurnInfoController::setNPC(NPC* anNPC)
{
    delete npc;
    if (anNPC)
    {
        npc = new NPC(anNPC);
    }
    else
    {
        npc = NULL;
    }

    tryToView();
}

void TurnInfoController::on_viewNPC(NPC* anNPC)
{
    if (anNPC)
    {
        if (npc)
        {
            if (npc->getName() == anNPC->getName())
            {
                setNPC(NULL);
            }
            else
            {
                setNPC(anNPC);
            }
        }
        else
        {
            setNPC(anNPC);
        }
    }
    else
    {
        setNPC(NULL);
    }
}

void TurnInfoController::on_deleteNPC(QString name)
{
    if (npc)
    {
        if (name == npc->getName())
        {
            setNPC(NULL);
        }
    }
}
