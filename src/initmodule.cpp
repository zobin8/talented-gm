#include "initmodule.h"
#include "svp.h"
#include "talentdata.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>

InitModule::InitModule(QWidget *parent) : MenuModule(parent)
{
    sense = new QDoubleSpinBox();
    sense->setDecimals(1);

    name = new QLineEdit("New Player");
    action = new QLineEdit("");
    notes = new QLineEdit("");

    result = new QCheckBox();
    result->setTristate(true);
    result->setText("Success?");

    sense->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    action->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    result->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    notes->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
}

InitModule::~InitModule()
{
    delete sense;
    delete name;
    delete action;
    delete result;
    delete notes;
}

void InitModule::addWidgets()
{
    layout->addWidget(sense, 0, 0);
    layout->addWidget(name, 0, 1);
    layout->addWidget(action, 1, 1);
    layout->addWidget(result, 0, 2);
    layout->addWidget(notes, 1, 2);
}

InitiativeAct InitModule::getInitiativeAct()
{
    InitiativeAct act = InitiativeAct();

    SVP player = SVP();
    player.setString(name->text());
    player.setValue(sense->value());
    act.setPlayer(player);

    act.setAction(action->text());
    act.setNotes(notes->text());

    Qt::CheckState c = result->checkState();
    int i = TalentData::stateToInt(c);
    act.setResult(i);

    return act;
}

void InitModule::setInitiativeAct(InitiativeAct act)
{
    name->setText(act.getPlayer().getString());
    sense->setValue(act.getPlayer().getValue());
    action->setText(act.getAction());
    notes->setText(act.getNotes());

    int i = act.getResult();
    Qt::CheckState c = TalentData::intToState(i);
    result->setCheckState(c);
}
