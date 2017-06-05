#include "loctemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "talentfile.h"

LocTemplate::LocTemplate()
{
    npcs = QLinkedList<QString>();
    name = LocTemplate::randName();
    description = "";

    minions1 = 0;
    minions2 = 0;
}

LocTemplate::LocTemplate(const LocTemplate* old)
{
    name = old->getName();
    description = old->getDescription();
    minions1 = old->minions1;
    minions2 = old->minions2;
    npcs = QLinkedList<QString>(old->getNPCs());
}

const QLinkedList<QString>& LocTemplate::getNPCs() const
{
    return npcs;
}

QLinkedList<QString>& LocTemplate::NPCs()
{
    return npcs;
}

QString LocTemplate::getName() const
{
    return name;
}

void LocTemplate::setName(QString aName)
{
    name = aName;
}

QString LocTemplate::getDescription() const
{
    return description;
}

void LocTemplate::setDescription(QString aDesc)
{
    description = aDesc;
}

void LocTemplate::addNPC(QString npc)
{
    npcs.append(npc);
}

void LocTemplate::removeNPC(QString npc)
{
    npcs.removeOne(npc);
}

QString LocTemplate::randName()
{
    return "Custom Location #" + QString::number(qrand() % 1000000);
}

QDataStream& operator <<(QDataStream& out, const LocTemplate& locTemp)
{
    out << QString("LocTemplate3");

    out << locTemp.getName();
    out << locTemp.minions1;
    out << locTemp.minions2;

    out << locTemp.getNPCs();

    out << locTemp.getDescription();

    return out;
}

QDataStream& operator >>(QDataStream& in, LocTemplate& locTemp)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "LocTemplate");

    if (v >= 1)
    {
        QString name;
        in >> name;
        locTemp.setName(name);

        in >> locTemp.minions1;
        in >> locTemp.minions2;

        if (v < 3)
        {
            int count;
            in >> count;
            for (int i = 0; i < count; i++)
            {
                QString n;
                in >> n;
                locTemp.addNPC(n);
            }
        }
        else
        {
            in >> locTemp.NPCs();
        }
    }
    if (v >= 2)
    {
        QString description;
        in >> description;
        locTemp.setDescription(description);
    }

    return in;
}
