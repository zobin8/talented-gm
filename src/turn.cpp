#include "turn.h"
#include "talentdata.h"

Turn::Turn()
{
    notes = "";
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

QDataStream& operator <<(QDataStream& out, const Turn& turn)
{
    out << QString("Turn1");

    out << turn.getNotes();

    return out;
}

QDataStream& operator >>(QDataStream& in, Turn& turn)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "Turn");

    if (v == 1)
    {
        QString notes;
        in >> notes;
        turn.setNotes(notes);
    }

    return in;
}
