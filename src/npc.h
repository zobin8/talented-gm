#ifndef NPC_H
#define NPC_H

#include <QString>

class NPCTemplate;

class NPC
{
public:
    NPC();
    NPC(NPC*);
    NPC(NPCTemplate*);
    ~NPC();

    int body;
    int coord;
    double sense;
    int mind;
    int charm;
    int comm;

    void setName(QString);
    QString getName() const;

private:
    QString name;
};

QDataStream& operator <<(QDataStream&, const NPC&);
QDataStream& operator >>(QDataStream&, NPC&);

#endif // NPC_H
