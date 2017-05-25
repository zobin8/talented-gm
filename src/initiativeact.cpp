#include "initiativeact.h"
#include "talentdata.h"

InitiativeAct::InitiativeAct()
{
    player = SVP();
    action = "";
    result = 0;
    notes = "";
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

QDataStream& operator <<(QDataStream& out, const InitiativeAct& act)
{
    out << QString("InitiativeAct1");

    out << act.getPlayer();
    out << act.getAction();
    out << act.getResult();
    out << act.getNotes();

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

    return in;
}
