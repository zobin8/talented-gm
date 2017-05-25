#ifndef TURN_H
#define TURN_H

#include <QString>

class LocTemplate;
class NPCTemplate;
class Location;

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


private:
    QString notes;
    Location* loc;
};

QDataStream& operator <<(QDataStream&, const Turn&);
QDataStream& operator >>(QDataStream&, Turn&);

#endif // TURN_H
