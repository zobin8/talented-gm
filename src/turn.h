#ifndef TURN_H
#define TURN_H

#include <QString>
#include <QVector>

class LocTemplate;
class NPCTemplate;
class Location;
class InitiativeAct;

class Turn
{
public:
    Turn();
    Turn(Turn*);

    QString getNotes() const;
    void setNotes(QString);

    void setLocTemplate(const LocTemplate*);
    void addNPCTemplate(const NPCTemplate*);

    const Location* getLoc() const;
    void setLoc(Location*);

    const QVector<InitiativeAct>* getInitiative() const;
    void setInitiative(QVector<InitiativeAct>*);

private:
    QString notes;
    Location* loc;
    QVector<InitiativeAct>* initiative;
};

QDataStream& operator <<(QDataStream&, const Turn&);
QDataStream& operator >>(QDataStream&, Turn&);

#endif // TURN_H
