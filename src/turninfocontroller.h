#ifndef TURNINFOCONTROLLER_H
#define TURNINFOCONTROLLER_H

#include "controller.h"

class NPC;
class QTextEdit;

class TurnInfoController : public Controller
{
    Q_OBJECT
public:
    explicit TurnInfoController(QObject *parent = 0);
    ~TurnInfoController();

    void setWidgets(QWidget* turnStatContents, QWidget* turnSkillContents, QTextEdit* turnNPCDesc);

    void setNPC(NPC*);

    void toView();
    void toModel();
    void fromModel();
    void fromView();

signals:

public slots:
    void on_viewNPC(NPC*);
    void on_deleteNPC(QString);

private:
    NPC* npc;
    QWidget* uiSkills;
    QWidget* uiStats;
    QTextEdit* uiDesc;
};

#endif // TURNINFOCONTROLLER_H
