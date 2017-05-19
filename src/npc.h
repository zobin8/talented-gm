#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QLinkedList>

class SVP;

class NPC
{
public:
    explicit NPC();
    //explicit NPC(NPC*);
    ~NPC();

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
};

#endif // NPC_H
