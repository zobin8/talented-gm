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

    QDoubleSpinBox* getSense();
    QLineEdit* getName();
    QLineEdit* getAction();
    QCheckBox* getResult();
    QLineEdit* getNotes();
    QCheckBox* getActive();

    void resetActive();

signals:

public slots:
    void on_activeEvent();

private:
    QDoubleSpinBox* sense;
    QLineEdit* name;
    QLineEdit* action;
    QCheckBox* result;
    QLineEdit* notes;
    QCheckBox* active;
};

#endif // INITMODULE_H
