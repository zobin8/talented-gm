#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QVector>

class NPCTemplate;
class HitArea;
class Skill;

class NPC
{
public:
    NPC();
    NPC(const NPC*);
    NPC(const NPCTemplate*);
    ~NPC();

    int body;
    int coord;
    double sense;
    int mind;
    int charm;
    int comm;

    void setName(QString);
    QString getName() const;

    void setDescription(QString);
    QString getDescription() const;

    void setHitAreas(QVector<HitArea>*);
    QVector<HitArea>* getHitAreas() const;

    void setSkills(QVector<Skill>*);
    QVector<Skill>* getSkills() const;
    int getSkillDice(Skill) const;

    int getStatFromName(QString) const;

private:
    QString name;
    QString description;
    QVector<HitArea>* hitAreas;
    QVector<Skill>* skills;

    void sortHitAreas();
};

QDataStream& operator <<(QDataStream&, const NPC&);
QDataStream& operator >>(QDataStream&, NPC&);

#endif // NPC_H
