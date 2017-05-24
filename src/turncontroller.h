#ifndef TURNCONTROLLER_H
#define TURNCONTROLLER_H

#include "controller.h"

class TurnNotesController;
class QLabel;

class TurnController : public Controller
{
    Q_OBJECT
public:
    explicit TurnController(QObject *parent = 0);
    ~TurnController();

    void setWidgets(QLabel* turnCount);

    void toView();
    void toModel();
    void fromModel();
    void fromView();

    TurnNotesController* turnNotesController;

signals:

public slots:

private:
    QList<Controller*> turnControllers;

    QLabel* uiTurnCount;
};

#endif // TURNCONTROLLER_H
