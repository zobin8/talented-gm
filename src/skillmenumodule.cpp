#include "skillmenumodule.h"
#include "skill.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

SkillMenuModule::SkillMenuModule(QWidget* parent) : MenuModule(parent)
{
    spin = new QDoubleSpinBox();
    edit = new QLineEdit();

    spin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    setDecimals(0);
    spin->setValue(1);
}

void SkillMenuModule::addWidgets()
{
    layout->addWidget(spin);
    layout->addWidget(edit);
    layout->addWidget(getDeleteButton());
}

SkillMenuModule::~SkillMenuModule()
{
    delete spin;
    delete edit;
}

void SkillMenuModule::setDecimals(int d)
{
    spin->setDecimals(d);
}

Skill SkillMenuModule::getSkill()
{
    double v = spin->value();
    QString s = edit->text();
    Skill skill("None", s, v);
    return skill;
}

void SkillMenuModule::setSkill(Skill skill)
{
    spin->setValue(skill.getValue());
    edit->setText(skill.getString());
}

QDoubleSpinBox* SkillMenuModule::getSpin()
{
    return spin;
}

QLineEdit* SkillMenuModule::getEdit()
{
    return edit;
}
