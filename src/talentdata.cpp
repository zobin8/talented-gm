#include "talentdata.h"
#include "npctemplate.h"
#include "locationtemplate.h"
#include "stringvaluepair.h"
#include <QLinkedList>

TalentData::TalentData()
{
    npcTemplates = QLinkedList<NPCTemplate*>();
    locTemplates = QLinkedList<LocationTemplate*>();
    players = new QLinkedList<SVP>();
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

    delete players;
}

QLinkedList<SVP>* TalentData::getPlayers()
{
    return players;
}

void TalentData::setPlayers(QLinkedList<SVP>* newPlayers)
{
    delete players;
    players = new QLinkedList<SVP>(*newPlayers);
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

QString TalentData::getNoteTemplate()
{
    return noteTemplate;
}

void TalentData::setNoteTemplate(QString aString)
{
    noteTemplate = aString;
}
