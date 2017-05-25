#include "hitmodule.h"
#include "hitarea.h"
#include "talentdata.h"
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>

HitModule::HitModule(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    label = new QLabel();
    boxes = QVector<QCheckBox*>();

    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->setContentsMargins(9, 0, 9, 0);

    layout->addWidget(label);
}

HitModule::~HitModule()
{
    foreach (QCheckBox* box, boxes)
    {
        delete box;
    }

    delete label;
    delete layout;
}

HitArea HitModule::getHitArea()
{
    HitArea area = HitArea();
    QVector<int> hits = QVector<int>();

    area.setName(label->text());

    foreach (QCheckBox* box, boxes)
    {
        int i = TalentData::stateToInt(box->checkState());
        hits.append(i);
    }

    area.setValues(hits);
    return area;
}

void HitModule::setHitArea(HitArea area)
{
    boxes.clear();
    while (layout->count() > 0)
    {
        QWidget* w = layout->itemAt(0)->widget();
        layout->removeWidget(w);
        delete w;
    }

    label = new QLabel(area.getName());
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    layout->addWidget(label);

    foreach (int i, area.getValues())
    {
        QCheckBox* box = new QCheckBox();
        box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        box->setTristate(true);
        box->setCheckState(TalentData::intToState(i));
        boxes.append(box);
        layout->addWidget(box);
    }

}
