#ifndef EDITORNPCCONTROLLER_H
#define EDITORNPCCONTROLLER_H

#include "controller.h"

class EditorNPCController : public Controller
{
    Q_OBJECT
public:
    explicit EditorNPCController(Controller* parent = 0, QMainWindow* aUi = 0);

    void draw();
};

#endif // EDITORNPCCONTROLLER_H
