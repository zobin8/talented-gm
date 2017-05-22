#ifndef LOCATIONTEMPLATE_H
#define LOCATIONTEMPLATE_H

#include <QString>
#include <QLinkedList>

class NPCTemplate;

class LocTemplate
{
public:
    LocTemplate();
    LocTemplate(LocTemplate*);

    int minions1;
    int minions2;

    QString getName();
    void setName(QString);

    QLinkedList<NPCTemplate*>& getNPCs();

    void addNPC(NPCTemplate*);
    void removeNPC(NPCTemplate*);

private:
    QString name;
    QLinkedList<NPCTemplate*> npcs;

    static QString randName();
};

#endif // LOCATIONTEMPLATE_H
