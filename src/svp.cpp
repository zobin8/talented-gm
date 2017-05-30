#include "svp.h"
#include "talentdata.h"

SVP::SVP()
{
    string = "";
    value = 0;
}

SVP::SVP(QString s, double v)
{
    string = s;
    value = v;
}

QDataStream& operator <<(QDataStream& out, const SVP& svp)
{
    out << QString("SVP1");

    out << svp.string;
    out << svp.value;

    return out;
}

QDataStream& operator >>(QDataStream& in, SVP& svp)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "SVP");

    if (v >= 1)
    {
        in >> svp.string;
        in >> svp.value;
    }

    return in;
}
