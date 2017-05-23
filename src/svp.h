#ifndef STRINGVALUEPAIR_H
#define STRINGVALUEPAIR_H

#include <QString>

class SVP
{
public:
    SVP();
    SVP(QString, double);
    QString string;
    double value;

private:
};

QDataStream& operator <<(QDataStream&, const SVP&);
QDataStream& operator >>(QDataStream&, SVP&);

#endif // STRINGVALUEPAIR_H
