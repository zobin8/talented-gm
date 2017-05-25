#ifndef TURNCONTROLLER_H
#define TURNCONTROLLER_H

#include "controller.h"

class TurnNotesController;
class TurnLocController;
class TurnInitController;
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

    void addTurn();
    void deleteTurn();
    void nextTurn();
    void prevTurn();

    TurnNotesController* turnNotesController;
    TurnLocController* turnLocController;
    TurnInitController* turnInitController;

signals:

public slots:

private:
    QList<Controller*> turnControllers;

    QLabel* uiTurnCount;
};

#endif // TURNCONTROLLER_H
