#ifndef EDITORNPCCONTROLLER_H
#define EDITORNPCCONTROLLER_H

#include "controller.h"
#include <QString>

class NPCTemplate;
class MenuModule;

class EditorNPCController : public Controller
{
public:
    explicit EditorNPCController(Ui::MainWindow*);
    ~EditorNPCController();

    void draw();
    void load();
    void addHitBox(QString s = "", double v = 0);
    void makeNPC();
    void toTemplate();

private:
    NPCTemplate* npcTemp;
    //QLinkedList<MenuModule*> hitBoxModules;
};

#endif // EDITORNPCCONTROLLER_H
