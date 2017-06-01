#include "hitarea.h"
#include "talentdata.h"
#include "svp.h"

HitArea::HitArea()
{
    name = "";
    values = QVector<int>();
}

HitArea::HitArea(const SVP svp)
{
    name = svp.getString();
    values = QVector<int>(svp.getValue(), Qt::Unchecked);
}

QString HitArea::getName() const
{
    return name;
}

void HitArea::setName(QString aString)
{
    name = aString;
}

QVector<int> HitArea::getValues() const
{
    return values;
}

void HitArea::setValues(QVector<int> aVec)
{
    values = aVec;
}

bool HitArea::lessThan(HitArea& a, HitArea& b)
{
    int c = TalentData::smartStringCompare(a.getName(), b.getName());
    return (c < 0);
}

QDataStream& operator <<(QDataStream& out, const HitArea& area)
{
    out << QString("HitArea1");

    out << area.getName();
    out << area.getValues();

    return out;
}

QDataStream& operator >>(QDataStream& in, HitArea& area)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "HitArea");

    if (v >= 1)
    {
        QString name;
        in >> name;
        area.setName(name);

        QVector<int> values = QVector<int>();
        in >> values;
        area.setValues(values);
    }

    return in;
}
