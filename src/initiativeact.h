#ifndef INITIATIVEACT_H
#define INITIATIVEACT_H

#include "svp.h"
#include <QString>

class InitiativeAct
{
public:
    InitiativeAct();

    SVP getPlayer() const;
    void setPlayer(SVP);

    QString getAction() const;
    void setAction(QString);

    int getResult() const;
    void setResult(int);

    QString getNotes() const;
    void setNotes(QString);

private:
    SVP player;
    QString action;
    int result;
    QString notes;
};

QDataStream& operator <<(QDataStream&, const InitiativeAct&);
QDataStream& operator >>(QDataStream&, InitiativeAct&);

#endif // INITIATIVEACT_H
