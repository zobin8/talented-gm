#ifndef NPCMENUMODULE_H
#define NPCMENUMODULE_H

#include "menumodule.h"

class NPC;
class QLabel;
class QWidget;

class NPCMenuModule : public MenuModule
{
    Q_OBJECT
public:
    NPCMenuModule();
    ~NPCMenuModule();

    void addWidgets();

    NPC* getNPC();
    void setNPC(NPC*);

public slots:
    void on_viewEvent();

signals:
    void viewNPC(NPC*);

private:
    NPC* npc;
    QLabel* nameLabel;
    QPushButton* viewButton;
};

#endif // NPCMENUMODULE_H
