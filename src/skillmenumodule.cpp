#include "skillmenumodule.h"
#include "skill.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>

SkillMenuModule::SkillMenuModule(QWidget* parent) : MenuModule(parent)
{
    spin = new QDoubleSpinBox();
    edit = new QLineEdit();
    combo = new QComboBox();

    spin->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    combo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    setDecimals(0);
    spin->setValue(1);

    combo->addItem("None ");
    combo->addItem("Body ");
    combo->addItem("Coord");
    combo->addItem("Sense");
    combo->addItem("Mind ");
    combo->addItem("Charm");
    combo->addItem("Comm ");
}

void SkillMenuModule::addWidgets()
{
    layout->addWidget(combo);
    layout->addWidget(edit);
    layout->addWidget(spin);
    layout->addWidget(getDeleteButton());
}

SkillMenuModule::~SkillMenuModule()
{
    delete combo;
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
    QString n = combo->currentText();

    Skill skill(n, s, v);
    return skill;
}

void SkillMenuModule::setSkill(Skill skill)
{
    spin->setValue(skill.getValue());
    edit->setText(skill.getString());
    combo->setCurrentText(skill.getStatName());
}

QDoubleSpinBox* SkillMenuModule::getSpin()
{
    return spin;
}

QLineEdit* SkillMenuModule::getEdit()
{
    return edit;
}

QComboBox* SkillMenuModule::getCombo()
{
    return combo;
}
