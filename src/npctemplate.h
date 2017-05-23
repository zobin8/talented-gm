#ifndef NPCTEMPLATE_H
#define NPCTEMPLATE_H

#include <QString>
#include <QLinkedList>

class SVP;

class NPCTemplate
{
public:
    explicit NPCTemplate();
    NPCTemplate(NPCTemplate*);
    ~NPCTemplate();

    int body;
    int coord;
    double sense;
    int mind;
    int charm;
    int comm;

    void setName(QString);
    QString getName() const;

    QLinkedList<SVP>* getSkills() const;
    QLinkedList<SVP>* getHitBoxes() const;
    void addSkill(SVP);
    void addHitBox(SVP);
    void setSkills(QLinkedList<SVP>*);
    void setHitBoxes(QLinkedList<SVP>*);

private:
    QString name;
    QLinkedList<SVP>* skills;
    QLinkedList<SVP>* hitBoxes;

    static QString randName();
};

QDataStream& operator <<(QDataStream&, const NPCTemplate&);
QDataStream& operator >>(QDataStream&, NPCTemplate&);

#endif // NPCTEMPLATE_H
