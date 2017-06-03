#ifndef TURNLOCCONTROLLER_H
#define TURNLOCCONTROLLER_H

#include "controller.h"

class QSpinBox;
class QLabel;
class QTextEdit;
class Location;
class MenuModule;
class QWidget;
class NPC;

class TurnLocController : public Controller
{
    Q_OBJECT
public:
    explicit TurnLocController(QObject *parent = 0);
    ~TurnLocController();

    void setWidgets(QSpinBox* turnMinionSpin1, QSpinBox* turnMinionSpin2, QLabel* turnLocName, QWidget* turnNPCContents, QTextEdit* turnLocDesc);

signals:
    void deletedNPC(QString);
    void viewNPC(NPC*);

public slots:
    void on_viewNPC(NPC*);
    void on_deletionEvent(MenuModule*);

private:
    QSpinBox* uiMinions1;
    QSpinBox* uiMinions2;
    QLabel* uiLocName;
    QWidget* uiContents;
    QTextEdit* uiDesc;
    Location* loc;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TURNLOCCONTROLLER_H
