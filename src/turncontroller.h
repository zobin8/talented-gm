#ifndef TURNCONTROLLER_H
#define TURNCONTROLLER_H

#include "controller.h"

class QLabel;

class TurnController : public Controller
{
    Q_OBJECT
public:
    explicit TurnController(QObject *parent = 0);
    ~TurnController();

    void setWidgets(QLabel* turnCount);

    void addTurn();
    void deleteTurn();
    void nextTurn();
    void prevTurn();

signals:

public slots:

private:
    QLabel* uiTurnCount;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TURNCONTROLLER_H
