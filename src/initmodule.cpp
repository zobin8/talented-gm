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

    sense->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    action->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    result->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
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
    layout->addWidget(sense);
    layout->addWidget(name);
    layout->addWidget(action);
    layout->addWidget(result);
    layout->addWidget(notes);
}

InitiativeAct InitModule::getInitiativeAct()
{
    InitiativeAct act = InitiativeAct();

    SVP player = SVP();
    player.string = name->text();
    player.value = sense->value();
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
    name->setText(act.getPlayer().string);
    sense->setValue(act.getPlayer().value);
    action->setText(act.getAction());
    notes->setText(act.getNotes());

    int i = act.getResult();
    Qt::CheckState c = TalentData::intToState(i);
    result->setCheckState(c);
}
