#include "talentdata.h"
#include "npc.h"
#include <QLinkedList>

TalentData::TalentData()
{
    npcTemplates = QLinkedList<NPC*>();
}

TalentData::~TalentData()
{
    foreach (NPC* npc, npcTemplates)
    {
        delete npc;
    }
}

NPC* TalentData::getNPCFromName(const QString name)
{
    foreach (NPC* npc, npcTemplates)
    {
        if (npc->getName() == name)
        {
            return npc;
        }
    }
    return NULL;
}

void TalentData::addNPCTemplate(NPC* npc)
{
    QString name = npc->getName();
    NPC* oldNPC = getNPCFromName(name);

    if (oldNPC != npc)
    {
        if (oldNPC)
        {
            npcTemplates.removeOne(oldNPC);
            delete oldNPC;
        }

        npcTemplates.append(npc);
    }
}

QLinkedList<NPC*> TalentData::getNPCTemplates()
{
    return npcTemplates;
}
