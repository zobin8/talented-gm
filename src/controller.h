#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject* parent = 0);

    virtual void toView() = 0;
    virtual void fromModel() = 0;
    virtual void fromView() = 0;

public slots:
    void on_update();

signals:
    void update();

};

#endif // CONTROLLER_H
