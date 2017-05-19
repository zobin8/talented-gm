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
    virtual void draw() = 0;
    virtual void load() = 0;

public slots:

signals:

protected:
    Ui::MainWindow* ui;
};

#endif // CONTROLLER_H
