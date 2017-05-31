#include "skill.h"
#include "talentdata.h"

Skill::Skill() : SVP()
{
    statName = "None";
}

Skill::Skill(const SVP svp) : SVP(svp)
{
    statName = "None";
}

Skill::Skill(const Skill& skill) : SVP()
{
    statName = skill.getStatName();

    value = skill.getValue();
    string = skill.getString();
}

QString Skill::getStatName() const
{
    return statName;
}

void Skill::setStatName(QString aName)
{
    statName = aName;
}

QDataStream& operator <<(QDataStream& out, const Skill& skill)
{
    out << QString("Skill1");

    out << skill.getString();
    out << skill.getValue();
    out << skill.getStatName();

    return out;
}

QDataStream& operator >>(QDataStream& in, Skill& skill)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "Skill");

    if (v >= 1)
    {
        QString s;
        in >> s;
        skill.setString(s);

        double v;
        in >> v;
        skill.setValue(v);

        QString n;
        in >> n;
        skill.setStatName(n);
    }

    return in;
}
