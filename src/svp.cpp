#include "svp.h"
#include "talentdata.h"

SVP::SVP()
{
    string = "";
    value = 0;
}

SVP::SVP(const SVP& old)
{
    string = old.getString();
    value = old.getValue();
}

SVP::SVP(QString s, double v)
{
    string = s;
    value = v;
}

QString SVP::getString() const
{
    return string;
}

void SVP::setString(QString aString)
{
    string = aString;
}

double SVP::getValue() const
{
    return value;
}

void SVP::setValue(double aValue)
{
    value = aValue;
}

QDataStream& operator <<(QDataStream& out, const SVP& svp)
{
    out << QString("SVP1");

    out << svp.getString();
    out << svp.getValue();

    return out;
}

QDataStream& operator >>(QDataStream& in, SVP& svp)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "SVP");

    if (v >= 1)
    {
        QString s;
        in >> s;
        svp.setString(s);

        double v;
        in >> v;
        svp.setValue(v);
    }

    return in;
}
