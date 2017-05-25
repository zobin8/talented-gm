#ifndef TURNINITCONTROLLER_H
#define TURNINITCONTROLLER_H

#include "controller.h"
#include <QVector>

class MenuModule;
class QWidget;
class InitiativeAct;

class TurnInitController : public Controller
{
    Q_OBJECT
public:
    explicit TurnInitController(QObject *parent = 0);
    ~TurnInitController();

    void toView();
    void fromModel();
    void toModel();
    void fromView();
    void setWidgets(QWidget* turnInitContents);
    void addPlayer();

signals:

public slots:
    void deleteInit(QString);

private:
    QWidget* uiContents;
    QVector<InitiativeAct>* initiative;
};

#endif // TURNINITCONTROLLER_H
