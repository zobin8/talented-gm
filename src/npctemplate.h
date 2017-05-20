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
    QString getName();

    QLinkedList<SVP>* getSkills();
    QLinkedList<SVP>* getHitBoxes();
    void addSkill(SVP);
    void addHitBox(SVP);

private:
    QString name;
    QLinkedList<SVP>* skills;
    QLinkedList<SVP>* hitBoxes;

    //TODO: Make static
    QString randName();
};

#endif // NPCTEMPLATE_H
