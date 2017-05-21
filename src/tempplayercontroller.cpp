#include "tempplayercontroller.h"
#include "stringvaluepair.h"
#include "svpmenumodule.h"
#include "talentdata.h"
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
    players = new QLinkedList<SVP>(*TalentData::getInstance().getPlayers());
}

void TempPlayerController::toModel()
{
    TalentData::getInstance().setPlayers(players);
}

void TempPlayerController::fromView()
{

}

void TempPlayerController::setWidgets(QWidget* tempPlayerContents)
{
    uiPlayerContents = tempPlayerContents;
}

void TempPlayerController::on_deletionEvent(MenuModule* del)
{
    uiPlayerContents->layout()->removeWidget(del);
    delete del;

    fromView();
    toModel();
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
}

void TempPlayerController::addPlayerView(QString s, double v)
{
    SVPMenuModule* menMod = new SVPMenuModule();
    menMod->setValue(SVP(s, v));

    //TODO: Make this a static function in Controller
    QVBoxLayout* playerLayout = (QVBoxLayout*) uiPlayerContents->layout();
    int index = playerLayout->count();
    playerLayout->insertWidget(index, menMod);

    connect(menMod, SIGNAL(killMe(MenuModule*)), this, SLOT(on_deletionEvent(MenuModule*)));
    connect(menMod->getSpin(), SIGNAL(valueChanged(double)), this, SLOT(on_uiUpdate()));
    connect(menMod->getEdit(), SIGNAL(textChanged(QString)), this, SLOT(on_uiUpdate()));
}
