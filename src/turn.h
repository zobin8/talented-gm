#ifndef TURN_H
#define TURN_H

#include <QString>

class Turn
{
public:
    Turn();
    Turn(Turn*);

    QString getNotes() const;
    void setNotes(QString);

private:
    QString notes;
};

QDataStream& operator <<(QDataStream&, const Turn&);
QDataStream& operator >>(QDataStream&, Turn&);

#endif // TURN_H
