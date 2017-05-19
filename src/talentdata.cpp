#include "talentdata.h"
#include "npctemplate.h"
#include <QLinkedList>

TalentData::TalentData()
{
    npcTemplates = QLinkedList<NPCTemplate*>();
}

TalentData::~TalentData()
{
    foreach (NPCTemplate* npc, npcTemplates)
    {
        delete npc;
    }
}

NPCTemplate* TalentData::getNPCFromName(const QString name)
{
    foreach (NPCTemplate* npc, npcTemplates)
    {
        if (npc->getName() == name)
        {
            return npc;
        }
    }
    return NULL;
}

void TalentData::addNPCTemplate(NPCTemplate* npc)
{
    QString name = npc->getName();
    NPCTemplate* oldNPC = getNPCFromName(name);

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

QLinkedList<NPCTemplate*> TalentData::getNPCTemplates()
{
    return npcTemplates;
}
