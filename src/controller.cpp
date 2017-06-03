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
    mutex = new QMutex();
    view = QVector<QWidget*>();
}

Controller::~Controller()
{
    delete mutex;
}

void Controller::on_viewUpdate()
{
    tryFromView();
    tryToModel();
}

void Controller::tryToView()
{
    lockView();

    foreach (QWidget* w, view)
    {
        w->blockSignals(true);
    }

    toView();

    foreach (QWidget* w, view)
    {
        w->blockSignals(false);
    }

    unlockView();
}

void Controller::tryToModel()
{
    toModel();
    emit updateView(ConFreq::hash);
}

void Controller::tryFromView()
{
    lockView();
    fromView();
    unlockView();
}

void Controller::tryFromModel()
{
    fromModel();
}

void Controller::lockView()
{
    mutex->lock();
}

void Controller::unlockView()
{
    mutex->unlock();
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
