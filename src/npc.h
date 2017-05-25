#ifndef NPC_H
#define NPC_H

#include <QString>
#include <QVector>

class NPCTemplate;
class HitArea;

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

    void setHitAreas(QVector<HitArea>*);
    QVector<HitArea>* getHitAreas() const;

private:
    QString name;
    QVector<HitArea>* hitAreas;
};

QDataStream& operator <<(QDataStream&, const NPC&);
QDataStream& operator >>(QDataStream&, NPC&);

#endif // NPC_H
