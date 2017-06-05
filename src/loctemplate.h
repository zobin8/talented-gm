#ifndef LOCATIONTEMPLATE_H
#define LOCATIONTEMPLATE_H

#include <QString>
#include <QLinkedList>

class LocTemplate
{
public:
    LocTemplate();
    LocTemplate(const LocTemplate*);

    int minions1;
    int minions2;

    QString getName() const;
    void setName(QString);
    QString getDescription() const;
    void setDescription(QString);

    QLinkedList<QString>& NPCs();
    const QLinkedList<QString>& getNPCs() const;

    void addNPC(QString);
    void removeNPC(QString);

private:
    QString name;
    QString description;
    QLinkedList<QString> npcs;

    static QString randName();
};

QDataStream& operator <<(QDataStream&, const LocTemplate&);
QDataStream& operator >>(QDataStream&, LocTemplate&);

#endif // LOCATIONTEMPLATE_H
