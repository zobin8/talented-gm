#include "turninfocontroller.h"
#include "npc.h"
#include <QLayout>
#include <QLabel>

TurnInfoController::TurnInfoController(QObject *parent) : Controller(parent)
{
    npc = NULL;
}

TurnInfoController::~TurnInfoController()
{
    delete npc;
}

void TurnInfoController::setWidgets(QWidget *turnStatContents, QWidget *turnSkillContents)
{
    uiSkills = turnSkillContents;
    uiStats = turnStatContents;
}

void TurnInfoController::toView()
{
    QLayout* skills = uiSkills->layout();
    QLayout* stats = uiStats->layout();

    Controller::clearLayout(skills);
    Controller::clearLayout(stats);

    if (npc)
    {
        //stats->addWidget(new QLabel("Body: " + QString::number(npc->body)));
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

void TurnInfoController::on_viewNPC(NPC* anNPC)
{
    delete npc;
    npc = new NPC(anNPC);

    toView();
}
