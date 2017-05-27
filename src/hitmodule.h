#ifndef HITMODULE_H
#define HITMODULE_H

#include "module.h"
#include <QVector>

class HitArea;
class QLabel;
class QCheckBox;

class HitModule : public Module
{
    Q_OBJECT
public:
    explicit HitModule(QWidget *parent = 0);
    ~HitModule();

    HitArea getHitArea();
    void setHitArea(HitArea);

signals:

public slots:

private:
    QLabel* label;
    QVector<QCheckBox*> boxes;
};

#endif // HITMODULE_H
