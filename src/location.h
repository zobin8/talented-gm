#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QMap>
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
    QString getDisplayName() const;
    void setName(QString);

    QString getDescription() const;
    void setDescription(QString);

    QLinkedList<NPC*>& NPCs();
    const QLinkedList<NPC*>& getNPCs() const;

    QMap<QString, int> getTempNames() const;

    void addNPC(NPC*);
    void incrementName(NPC*);
    void removeNPC(NPC*);

    void setTurn(int);
    void incTurn();
    int getTurn() const;

private:
    QString name;
    QString description;
    QLinkedList<NPC*> npcs;
    QMap<QString, int> tempNames;
    int turn;

    static QString randName();
};

QDataStream& operator <<(QDataStream&, const Location&);
QDataStream& operator >>(QDataStream&, Location&);

#endif // LOCATION_H
