#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QLayout;
class Module;

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject* parent = 0);

    static void clearLayout(QLayout*);
    static void appendToLayout(Module*, QLayout*);

    virtual void toView() = 0;
    virtual void toModel() = 0;
    virtual void fromModel() = 0;
    virtual void fromView() = 0;

public slots:
    void on_update();

signals:
    void update();
    void unsavedChange();
};

#endif // CONTROLLER_H
