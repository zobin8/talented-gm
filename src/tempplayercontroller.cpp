#include "tempplayercontroller.h"
#include "svp.h"
#include "svpmenumodule.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QLinkedList>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QLineEdit>

TempPlayerController::TempPlayerController(QObject *parent) : Controller(parent)
{
    players = new QLinkedList<SVP>();
}

TempPlayerController::~TempPlayerController()
{
    delete players;
}

void TempPlayerController::toView()
{
    Controller::clearLayout(uiPlayerContents->layout());

    foreach (SVP svp, *players)
    {
        addPlayerView(svp.string, svp.value);
    }
}

void TempPlayerController::fromModel()
{
    delete players;
    players = new QLinkedList<SVP>(*TalentData::getTalentFile()->getPlayers());
}

void TempPlayerController::toModel()
{
    TalentData::getTalentFile()->setPlayers(players);
}

void TempPlayerController::toTurn()
{
    TalentData::getTalentFile()->resetInitiative();
    emit update();
}

void TempPlayerController::fromView()
{
    players->clear();
    QLayout* pLayout = uiPlayerContents->layout();
    for (int i = 0; i < pLayout->count(); i++)
    {
        QWidget* widget = pLayout->itemAt(i)->widget();
        SVPMenuModule* menMod = dynamic_cast<SVPMenuModule*>(widget);
        if (menMod)
        {
            players->append(menMod->getValue());
        }
    }
}

void TempPlayerController::setWidgets(QWidget* tempPlayerContents)
{
    uiPlayerContents = tempPlayerContents;
}

void TempPlayerController::on_deletionEvent(MenuModule* del)
{
    emit deletedPlayer(del->getIdentifier());

    uiPlayerContents->layout()->removeWidget(del);
    delete del;

    fromView();
    toModel();
    emit unsavedChange();
}

void TempPlayerController::addPlayer()
{
    addPlayerView();
    on_uiUpdate();
}

void TempPlayerController::on_uiUpdate()
{
    fromView();
    toModel();
    emit unsavedChange();
}

void TempPlayerController::addPlayerView(QString s, double v)
{
    SVPMenuModule* menMod = new SVPMenuModule();
    menMod->addWidgets();
    menMod->setValue(SVP(s, v));
    menMod->setDecimals(1);

    Controller::appendToLayout(menMod, uiPlayerContents->layout());

    connect(menMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
    connect(menMod->getSpin(), SIGNAL(valueChanged(double)), this, SLOT(on_uiUpdate()));
    connect(menMod->getEdit(), SIGNAL(textChanged(QString)), this, SLOT(on_uiUpdate()));
}
