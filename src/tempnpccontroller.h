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

    void setWidgets(QWidget* tempNPCContents);

signals:

public slots:
    void on_deletionEvent(MenuModule*);

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QWidget* uiNPCContents;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TEMPNPCCONTROLLER_H
