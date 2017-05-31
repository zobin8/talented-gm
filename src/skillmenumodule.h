#ifndef SKILLMENUMODULE_H
#define SKILLMENUMODULE_H

#include "menumodule.h"

class Skill;
class QHBoxLayout;
class QDoubleSpinBox;
class QLineEdit;
class QComboBox;

class SkillMenuModule : public MenuModule
{
public:
    SkillMenuModule(QWidget* parent = 0);
    ~SkillMenuModule();

    void addWidgets();

    Skill getSkill();
    void setSkill(Skill);

    QDoubleSpinBox* getSpin();
    QLineEdit* getEdit();
    QComboBox* getCombo();

    void setDecimals(int);

private:
    QDoubleSpinBox* spin;
    QLineEdit* edit;
    QComboBox* combo;
};

#endif // SKILLMENUMODULE_H
