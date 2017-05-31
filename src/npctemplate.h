#ifndef NPCTEMPLATE_H
#define NPCTEMPLATE_H

#include <QString>
#include <QLinkedList>

class SVP;
class Skill;

class NPCTemplate
{
public:
    explicit NPCTemplate();
    NPCTemplate(const NPCTemplate*);
    ~NPCTemplate();

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

    QLinkedList<Skill>* getSkills() const;
    QLinkedList<SVP>* getHitBoxes() const;
    void addSkill(Skill);
    void addHitBox(SVP);
    void setSkills(QLinkedList<Skill>*);
    void setHitBoxes(QLinkedList<SVP>*);

private:
    QString name;
    QString description;
    QLinkedList<Skill>* skills;
    QLinkedList<SVP>* hitBoxes;

    static QString randName();
};

QDataStream& operator <<(QDataStream&, const NPCTemplate&);
QDataStream& operator >>(QDataStream&, NPCTemplate&);

#endif // NPCTEMPLATE_H
