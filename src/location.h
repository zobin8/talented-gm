#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QLinkedList>

class NPC;
class LocTemplate;

class Location
{
public:
    Location();
    Location(const Location*);
    Location(const LocTemplate*);
    ~Location();

    int minions1;
    int minions2;

    QString getName() const;
    void setName(QString);

    QLinkedList<NPC*>& NPCs();
    const QLinkedList<NPC*>& getNPCs() const;

    void addNPC(NPC*);
    void removeNPC(NPC*);

private:
    QString name;
    QLinkedList<NPC*> npcs;

    static QString randName();
};

QDataStream& operator <<(QDataStream&, const Location&);
QDataStream& operator >>(QDataStream&, Location&);

#endif // LOCATION_H
