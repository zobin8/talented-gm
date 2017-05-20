#ifndef EDITORLOCCONTROLLER_H
#define EDITORLOCCONTROLLER_H

#include "controller.h"

class LocationTemplate;
class NPCTemplate;

class EditorLocController : public Controller
{
    Q_OBJECT
public:
    explicit EditorLocController(QObject *parent = 0);
    ~EditorLocController();

    void toView();
    void fromModel();
    void addNPC(NPCTemplate*);
    void fromView();
    void toTemplate();

signals:

public slots:
    void deleteNPC(NPCTemplate*);

private:
    LocationTemplate* locTemp;
};

#endif // EDITORLOCCONTROLLER_H
