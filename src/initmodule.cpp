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
    active = new QCheckBox("Conscious?");

    result = new QCheckBox();
    result->setTristate(true);
    result->setText("Success?");

    sense->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    name->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    action->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    result->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    notes->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    active->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(active, SIGNAL(clicked(bool)), this, SLOT(on_activeEvent()));

    connect(sense, SIGNAL(valueChanged(double)), this, SLOT(on_update()));
    connect(name, SIGNAL(textChanged(QString)), this, SLOT(on_update()));
    connect(action, SIGNAL(textChanged(QString)), this, SLOT(on_update()));
    connect(result, SIGNAL(clicked(bool)), this, SLOT(on_update()));
    connect(notes, SIGNAL(textChanged(QString)), this, SLOT(on_update()));
    connect(active, SIGNAL(clicked(bool)), this, SLOT(on_update()));
}

InitModule::~InitModule()
{
    delete sense;
    delete name;
    delete action;
    delete result;
    delete notes;
    delete active;
}

void InitModule::addWidgets()
{
    layout->addWidget(sense, 0, 0);
    layout->addWidget(active, 0, 1);
    layout->addWidget(name, 0, 2);
    layout->addWidget(action, 1, 0, 1, 3);
    layout->addWidget(result, 0, 3);
    layout->addWidget(notes, 1, 3);
}

QDoubleSpinBox* InitModule::getSense()
{
    return sense;
}

QLineEdit* InitModule::getName()
{
    return name;
}

QLineEdit* InitModule::getAction()
{
    return action;
}

QCheckBox* InitModule::getResult()
{
    return result;
}

QLineEdit* InitModule::getNotes()
{
    return notes;
}

QCheckBox* InitModule::getActive()
{
    return active;
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
    act.setActive(active->isChecked());

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
    active->setChecked(act.isActive());
    resetActive();

    int i = act.getResult();
    Qt::CheckState c = TalentData::intToState(i);
    result->setCheckState(c);
}

void InitModule::resetActive()
{
    bool a = active->isChecked();
    action->setEnabled(a);
    result->setEnabled(a);
    notes->setEnabled(a);
}

void InitModule::on_activeEvent()
{
    resetActive();
}
