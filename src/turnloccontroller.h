#ifndef TURNLOCCONTROLLER_H
#define TURNLOCCONTROLLER_H

#include "controller.h"

class QSpinBox;
class QLabel;
class Location;
class MenuModule;
class QWidget;

class TurnLocController : public Controller
{
    Q_OBJECT
public:
    explicit TurnLocController(QObject *parent = 0);
    ~TurnLocController();

    void setWidgets(QSpinBox* turnMinionSpin1, QSpinBox* turnMinionSpin2, QLabel* turnLocName, QWidget* turnNPCContents);

    void toView();
    void toModel();
    void fromModel();
    void fromView();

signals:
    void deletedNPC(QString);

public slots:
    void on_deletionEvent(MenuModule*);

private:
    QSpinBox* uiMinions1;
    QSpinBox* uiMinions2;
    QLabel* uiLocName;
    QWidget* uiContents;

    Location* loc;
};

#endif // TURNLOCCONTROLLER_H
