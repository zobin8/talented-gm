#ifndef TEMPNPCCONTROLLER_H
#define TEMPNPCCONTROLLER_H

#include "controller.h"
#include <QLinkedList>

class MenuModule;
class NPCTemplate;

class TempNPCController : public Controller
{
    Q_OBJECT
public:
    explicit TempNPCController(QObject *parent = 0);

    void toView();
    void fromModel();
    void toModel();
    void fromView();
    void setWidgets(QWidget* tempNPCContents);

signals:

public slots:
    void on_deletionEvent(MenuModule*);

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QWidget* uiNPCContents;
};

#endif // TEMPNPCCONTROLLER_H
