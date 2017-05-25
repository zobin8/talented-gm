#ifndef INITMODULE_H
#define INITMODULE_H

#include "menumodule.h"
#include "initiativeact.h"

class QDoubleSpinBox;
class QLineEdit;
class QCheckBox;

class InitModule : public MenuModule
{
    Q_OBJECT
public:
    explicit InitModule(QWidget *parent = 0);
    ~InitModule();

    void addWidgets();

    InitiativeAct getInitiativeAct();
    void setInitiativeAct(InitiativeAct);

signals:

public slots:

private:
    QDoubleSpinBox* sense;
    QLineEdit* name;
    QLineEdit* action;
    QCheckBox* result;
    QLineEdit* notes;

};

#endif // INITMODULE_H
