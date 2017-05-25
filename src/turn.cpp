#include "turn.h"
#include "talentdata.h"
#include "loctemplate.h"
#include "npctemplate.h"
#include "npc.h"
#include "location.h"

Turn::Turn()
{
    notes = "";
    loc = new Location();
}

Turn::Turn(Turn* old)
{
    notes = old->getNotes();
}

QString Turn::getNotes() const
{
    return notes;
}

void Turn::setNotes(QString aString)
{
    notes = aString;
}

void Turn::setLocTemplate(const LocTemplate* locTemp)
{
    delete loc;
    loc = new Location(locTemp);
}

void Turn::addNPCTemplate(const NPCTemplate* npcTemp)
{
    NPC* npc = new NPC(npcTemp);
    loc->addNPC(npc);
}

const Location* Turn::getLoc() const
{
    return loc;
}

void Turn::setLoc(Location* aLoc)
{
    delete loc;
    loc = new Location(aLoc);
}

QDataStream& operator <<(QDataStream& out, const Turn& turn)
{
    out << QString("Turn2");

    out << turn.getNotes();
    out << *turn.getLoc();

    return out;
}

QDataStream& operator >>(QDataStream& in, Turn& turn)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "Turn");

    if (v >= 1)
    {
        QString notes;
        in >> notes;
        turn.setNotes(notes);
    }
    if (v >= 2)
    {
        Location* loc = new Location();
        in >> *loc;
        turn.setLoc(loc);
    }

    return in;
}
