#ifndef STRINGVALUEPAIR_H
#define STRINGVALUEPAIR_H

#include <QString>

class SVP
{
public:
    SVP();
    SVP(const SVP&);
    SVP(QString, double);

    QString getString() const;
    void setString(QString);

    double getValue() const;
    void setValue(double);

protected:
    QString string;
    double value;
};

QDataStream& operator <<(QDataStream&, const SVP&);
QDataStream& operator >>(QDataStream&, SVP&);

#endif // STRINGVALUEPAIR_H
