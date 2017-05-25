#ifndef HITMODULE_H
#define HITMODULE_H

#include <QWidget>
#include <QVector>

class QHBoxLayout;
class HitArea;
class QLabel;
class QCheckBox;

class HitModule : public QWidget
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
    QHBoxLayout* layout;
    QLabel* label;
    QVector<QCheckBox*> boxes;
};

#endif // HITMODULE_H
