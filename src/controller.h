#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

namespace Ui
{
    class MainWindow;
}

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject* parent = 0);

    virtual void setUi(Ui::MainWindow*);
    virtual void toView() = 0;
    virtual void fromModel() = 0;
    virtual void fromView() = 0;

public slots:

signals:

protected:
    Ui::MainWindow* ui;
};

#endif // CONTROLLER_H
