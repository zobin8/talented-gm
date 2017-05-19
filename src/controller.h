#ifndef CONTROLLER_H
#define CONTROLLER_H


namespace Ui
{
    class MainWindow;
}

class Controller
{
public:
    Controller(Ui::MainWindow*);
    virtual void draw() = 0;
    virtual void load() = 0;

protected:
    Ui::MainWindow* ui;
};

#endif // CONTROLLER_H
