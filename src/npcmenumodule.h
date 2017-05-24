#ifndef NPCMENUMODULE_H
#define NPCMENUMODULE_H

#include "menumodule.h"

class NPC;
class QLabel;

class NPCMenuModule : public MenuModule
{
public:
    NPCMenuModule();
    ~NPCMenuModule();

    void addWidgets();

    NPC* getNPC();
    void setNPC(NPC*);

private:
    NPC* npc;
    QLabel* nameLabel;
};

#endif // NPCMENUMODULE_H
