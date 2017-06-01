#include "initiativeact.h"
#include "talentdata.h"

InitiativeAct::InitiativeAct()
{
    player = SVP();
    action = "";
    result = 0;
    notes = "";
    active = true;
}

SVP InitiativeAct::getPlayer() const
{
    return player;
}

void InitiativeAct::setPlayer(SVP svp)
{
    player = svp;
}

QString InitiativeAct::getAction() const
{
    return action;
}

void InitiativeAct::setAction(QString act)
{
    action = act;
}

int InitiativeAct::getResult() const
{
    return result;
}

void InitiativeAct::setResult(int i)
{
    result = i;
}

QString InitiativeAct::getNotes() const
{
    return notes;
}

void InitiativeAct::setNotes(QString aString)
{
    notes = aString;
}

bool InitiativeAct::isActive() const
{
    return active;
}

void InitiativeAct::setActive(bool b)
{
    active = b;
}

QDataStream& operator <<(QDataStream& out, const InitiativeAct& act)
{
    out << QString("InitiativeAct2");

    out << act.getPlayer();
    out << act.getAction();
    out << act.getResult();
    out << act.getNotes();
    out << act.isActive();

    return out;
}

QDataStream& operator >>(QDataStream& in, InitiativeAct& act)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "InitiativeAct");

    if (v >= 1)
    {
        SVP player = SVP();
        in >> player;
        act.setPlayer(player);

        QString action;
        in >> action;
        act.setAction(action);

        int result;
        in >> result;
        act.setResult(result);

        QString notes;
        in >> notes;
        act.setNotes(notes);
    }
    if (v >= 2)
    {
        bool a;
        in >> a;
        act.setActive(a);
    }

    return in;
}
