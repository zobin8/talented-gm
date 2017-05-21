#include "talentdata.h"
#include "npctemplate.h"
#include "locationtemplate.h"
#include <QLinkedList>

TalentData::TalentData()
{
    npcTemplates = QLinkedList<NPCTemplate*>();
    locTemplates = QLinkedList<LocationTemplate*>();
}

TalentData::~TalentData()
{
    foreach (NPCTemplate* npc, npcTemplates)
    {
        delete npc;
    }
    foreach (LocationTemplate* loc, locTemplates)
    {
        delete loc;
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

LocationTemplate* TalentData::getLocFromName(const QString name)
{
    foreach (LocationTemplate* loc, locTemplates)
    {
        if (loc->getName() == name)
        {
            return loc;
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

void TalentData::addLocTemplate(LocationTemplate* loc)
{
    QString name = loc->getName();
    LocationTemplate* oldLoc = getLocFromName(name);

    if (oldLoc != loc)
    {
        if (oldLoc)
        {
            locTemplates.removeOne(oldLoc);
            delete oldLoc;
        }

        locTemplates.append(loc);
    }
}

QLinkedList<NPCTemplate*> TalentData::getNPCTemplates()
{
    return npcTemplates;
}

QLinkedList<LocationTemplate*> TalentData::getLocTemplates()
{
    return locTemplates;
}

void TalentData::setLocTemplates(QLinkedList<LocationTemplate*> locs)
{
    locTemplates = QLinkedList<LocationTemplate*>(locs);
}

void TalentData::setNPCTemplates(QLinkedList<NPCTemplate*> npcs)
{
    npcTemplates = QLinkedList<NPCTemplate*>(npcs);
}
