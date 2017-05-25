#include "talentfile.h"
#include "npctemplate.h"
#include "loctemplate.h"
#include "talentdata.h"
#include "location.h"
#include "initiativeact.h"
#include "svp.h"
#include "turn.h"
#include "npc.h"
#include <QLinkedList>

TalentFile::TalentFile()
{
    npcTemplates = QLinkedList<NPCTemplate*>();
    locTemplates = QLinkedList<LocTemplate*>();
    players = new QLinkedList<SVP>();
    generalNotes = "";
    noteTemplate = "";

    turnIndex = 0;
    turns = QList<Turn*>();
    addTurn();
}

TalentFile::~TalentFile()
{
    foreach (NPCTemplate* npc, npcTemplates)
    {
        delete npc;
    }
    foreach (LocTemplate* loc, locTemplates)
    {
        delete loc;
    }
    foreach (Turn* turn, turns)
    {
        delete turn;
    }

    delete players;
}

QLinkedList<SVP>* TalentFile::getPlayers() const
{
    return players;
}

void TalentFile::setPlayers(QLinkedList<SVP>* newPlayers)
{
    delete players;
    players = new QLinkedList<SVP>(*newPlayers);
}

NPCTemplate* TalentFile::getNPCFromName(const QString name)
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

LocTemplate* TalentFile::getLocFromName(const QString name)
{
    foreach (LocTemplate* loc, locTemplates)
    {
        if (loc->getName() == name)
        {
            return loc;
        }
    }
    return NULL;
}

void TalentFile::addNPCTemplate(NPCTemplate* npc)
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

void TalentFile::addLocTemplate(LocTemplate* loc)
{
    QString name = loc->getName();
    LocTemplate* oldLoc = getLocFromName(name);

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

QLinkedList<NPCTemplate*> TalentFile::getNPCTemplates() const
{
    return npcTemplates;
}

QLinkedList<LocTemplate*> TalentFile::getLocTemplates() const
{
    return locTemplates;
}

void TalentFile::setLocTemplates(QLinkedList<LocTemplate*> locs)
{
    locTemplates = QLinkedList<LocTemplate*>(locs);
}

void TalentFile::setNPCTemplates(QLinkedList<NPCTemplate*> npcs)
{
    npcTemplates = QLinkedList<NPCTemplate*>(npcs);
}

QString TalentFile::getNoteTemplate() const
{
    return noteTemplate;
}

void TalentFile::setNoteTemplate(QString aString)
{
    noteTemplate = aString;
}

QString TalentFile::getNotes() const
{
    return generalNotes;
}

void TalentFile::setNotes(QString aString)
{
    generalNotes = aString;
}

Turn* TalentFile::currentTurn()
{
    if (turns.count() == 0) return NULL;

    //RIP 3 hours of my time. They have served me well trying to figure out why this line would not work:
    //return turns.takeAt(turnIndex);
    return turns.at(turnIndex);
}

const QList<Turn*> TalentFile::getTurns() const
{
    return turns;
}

void TalentFile::setTurns(QList<Turn*> newTurns)
{
    //Memory leak?
    turns = QList<Turn*>(newTurns);
    updateTurnIndex();
}

int TalentFile::currentTurnIndex() const
{
    return turnIndex;
}

void TalentFile::updateTurnIndex()
{
    if (turnIndex < 0)
    {
        turnIndex = 0;
    }
    else if (turnIndex >= turns.count())
    {
        turnIndex = turns.count() - 1;
    }
}

void TalentFile::previousTurn()
{
    turnIndex--;
    updateTurnIndex();
}

void TalentFile::nextTurn()
{
    turnIndex++;
    updateTurnIndex();
}

void TalentFile::resetInitiative()
{
    QVector<InitiativeAct>* initiative = new QVector<InitiativeAct>();
    foreach (SVP player, *players)
    {
        InitiativeAct act = InitiativeAct();
        act.setPlayer(player);
        initiative->append(act);
    }
    currentTurn()->setInitiative(initiative);

    foreach (NPC* npc, currentTurn()->getLoc()->getNPCs())
    {
        currentTurn()->addNPCInitiative(npc);
    }
}

void TalentFile::addTurn()
{
    Turn* turn = new Turn();

    turn->setNotes(noteTemplate);

    if (currentTurn())
    {
        Location* loc = new Location(currentTurn()->getLoc());
        turn->setLoc(loc);

        QVector<InitiativeAct>* initiative = new QVector<InitiativeAct>();
        foreach (InitiativeAct act, *currentTurn()->getInitiative())
        {
            InitiativeAct newAct = InitiativeAct();
            newAct.setPlayer(act.getPlayer());
            initiative->append(newAct);
        }
        turn->setInitiative(initiative);
    }

    turns.append(turn);

    turnIndex = turns.count() - 1;
    updateTurnIndex();
}

void TalentFile::deleteTurn()
{
    if (turns.count() > 1)
    {
        Turn* turn = currentTurn();
        turns.removeOne(turn);
        delete turn;
        updateTurnIndex();
    }
}

QDataStream& operator <<(QDataStream& out, const TalentFile& file)
{
    out << QString("TalentFile6");

    out << file.getNotes();
    out << file.getNoteTemplate();
    out << *file.getPlayers();

    out << file.getNPCTemplates().count();
    foreach (NPCTemplate* npc, file.getNPCTemplates())
    {
        out << *npc;
    }

    out << file.getLocTemplates().count();
    foreach (LocTemplate* loc, file.getLocTemplates())
    {
        out << *loc;
    }

    out << file.getTurns().count();
    foreach (Turn* t, file.getTurns())
    {
        out << *t;
    }

    return out;
}

QDataStream& operator >>(QDataStream& in, TalentFile& file)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "TalentFile");

    if (v >= 1)
    {
        QString n;
        in >> n;
        file.setNotes(n);
    }
    if (v >= 2)
    {
        QString nTemp;
        in >> nTemp;
        file.setNoteTemplate(nTemp);
    }
    if (v >= 3)
    {
        QLinkedList<SVP>* p = new QLinkedList<SVP>();
        in >> *p;
        file.setPlayers(p);
    }
    if (v >= 4)
    {
        QLinkedList<NPCTemplate*> npcs = QLinkedList<NPCTemplate*>();
        int count;
        in >> count;
        for (int i = 0; i < count; i++)
        {
            NPCTemplate* npc = new NPCTemplate();
            in >> *npc;
            npcs.append(npc);
        }
        file.setNPCTemplates(npcs);
    }
    if (v >= 5)
    {
        QLinkedList<LocTemplate*> locs = QLinkedList<LocTemplate*>();
        int count;
        in >> count;
        for (int i = 0; i < count; i++)
        {
            LocTemplate* loc = new LocTemplate();
            in >> *loc;
            locs.append(loc);
        }
        file.setLocTemplates(locs);
    }
    if (v >= 6)
    {
        QList<Turn*> turns = QList<Turn*>();
        int count;
        in >> count;
        for (int i = 0; i < count; i++)
        {
            Turn* t = new Turn();
            in >> *t;
            turns.append(t);
        }
        file.setTurns(turns);
    }

    return in;
}
