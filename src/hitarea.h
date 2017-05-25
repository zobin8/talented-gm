#ifndef HITAREA_H
#define HITAREA_H

#include <QString>
#include <QVector>

class SVP;

class HitArea
{
public:
    HitArea();
    HitArea(const SVP);

    QString getName() const;
    void setName(QString);

    QVector<int> getValues() const;
    void setValues(QVector<int>);

private:
    QVector<int> values;
    QString name;
};

QDataStream& operator <<(QDataStream&, const HitArea&);
QDataStream& operator >>(QDataStream&, HitArea&);

#endif // HITAREA_H
