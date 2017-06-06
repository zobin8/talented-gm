#include "controller.h"
#include "module.h"
#include "talentdata.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QMutex>

Controller::Controller(QObject* parent) : QObject(parent)
{
    conMutex = new QMutex();
    view = QVector<QWidget*>();
}

Controller::~Controller()
{
    delete conMutex;
}

void Controller::on_viewUpdate()
{
    tryFromView();
    tryToModel();
}

void Controller::tryToView()
{
    lockCon();

    foreach (QWidget* w, view)
    {
        w->blockSignals(true);
    }

    toView();

    foreach (QWidget* w, view)
    {
        w->blockSignals(false);
    }

    unlockCon();
}

void Controller::tryToModel()
{
    lockCon();
    toModel();
    unlockCon();

    emit updateView(ConFreq::hash);
}

void Controller::tryFromView()
{
    lockCon();
    fromView();
    unlockCon();
}

void Controller::tryFromModel()
{
    lockCon();
    fromModel();
    unlockCon();
}

void Controller::lockCon()
{
    conMutex->lock();
}

void Controller::unlockCon()
{
    conMutex->unlock();
}

void Controller::on_modelUpdate()
{
    tryFromModel();
    tryToView();
}

void Controller::clearLayout(QLayout* lay)
{
    while (lay->count() > 0)
    {
        QWidget* w =  lay->itemAt(0)->widget();
        lay->removeWidget(w);
        delete w;
    }
}

void Controller::appendToLayout(Module* insertedModule, QLayout* l)
{
    QVBoxLayout* vLayout = static_cast<QVBoxLayout*>(l);

    if (insertedModule->needsSort())
    {
        if (insertedModule->getSortID() == "")
        {
            vLayout->addWidget(insertedModule);
            return;
        }
        else
        {
            for (int i = 0; i < vLayout->count(); i++)
            {
                QWidget* w = vLayout->itemAt(i)->widget();
                Module* module = dynamic_cast<Module*>(w);
                if (module)
                {
                    if (module->needsSort())
                    {
                        int compare = TalentData::smartStringCompare(insertedModule->getSortID(), module->getSortID());
                        if (compare < 0)
                        {
                            vLayout->insertWidget(i, insertedModule);
                            return;
                        }
                    }
                }
            }
            vLayout->addWidget(insertedModule);
        }
    }
    else
    {
        vLayout->addWidget(insertedModule);
    }
}

void Controller::appendToLayout(QLabel* toSort, QLayout* l)
{
    QVBoxLayout* vLayout = static_cast<QVBoxLayout*>(l);

    for (int i = 0; i < vLayout->count(); i++)
    {
        QWidget* w = vLayout->itemAt(i)->widget();
        QLabel* label = dynamic_cast<QLabel*>(w);
        if (label)
        {
            int comp = TalentData::smartStringCompare(toSort->text(), label->text());
            if (comp < 0)
            {
                vLayout->insertWidget(i, toSort);
                return;
            }
        }
    }
    vLayout->addWidget(toSort);
}

void Controller::appendToLayout(QString string, QLayout* l)
{
    QLabel* toSort = new QLabel(string);
    appendToLayout(toSort, l);
}

void Controller::appendToCombo(QString toSort, QComboBox* combo)
{
    for (int i = 0; i < combo->count(); i++)
    {
        QString current = combo->itemText(i);
        int comp = TalentData::smartStringCompare(toSort, current);
        if (comp < 0)
        {
            combo->insertItem(i, toSort);
            return;
        }
    }
    combo->addItem(toSort);
}
