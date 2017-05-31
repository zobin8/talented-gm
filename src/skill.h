#ifndef SKILL_H
#define SKILL_H

#include "svp.h"

class Skill : public SVP
{
public:
    Skill();
    Skill(QString, QString, double);
    Skill(const SVP);
    Skill(const Skill&);

    QString getStatName() const;
    void setStatName(QString);

private:
    QString statName;
};

QDataStream& operator <<(QDataStream&, const Skill&);
QDataStream& operator >>(QDataStream&, Skill&);

#endif // SKILL_H
