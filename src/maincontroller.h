#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "controller.h"
#include "editornpccontroller.h"
#include "editorloccontroller.h"
#include "tempnpccontroller.h"
#include "temploccontroller.h"
#include "tempplayercontroller.h"
#include "filecontroller.h"
#include "generalcontroller.h"
#include "tempnotescontroller.h"
#include "turncontroller.h"
#include "turnnotescontroller.h"
#include "turnloccontroller.h"
#include "turninitcontroller.h"
#include "turninfocontroller.h"
#include "hashcontroller.h"
#include <QLinkedList>

class MainController : public Controller
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = 0);
    ~MainController();

    void connectControllers();

    void toView();
    void toModel();
    void fromModel();
    void fromView();

    EditorNPCController* editorNPCController;
    EditorLocController* editorLocController;
    TempLocController* tempLocController;
    TempNPCController* tempNPCController;
    TempPlayerController* tempPlayerController;
    FileController* fileController;
    GeneralController* generalController;
    TempNotesController* tempNotesController;
    TurnController* turnController;
    TurnNotesController* turnNotesController;
    TurnLocController* turnLocController;
    TurnInitController* turnInitController;
    TurnInfoController* turnInfoController;
    HashController* hashController;

signals:

public slots:
    void on_updateView(ConFreq);
    void on_updateModel(ConFreq);

private:
    QLinkedList<Controller*> controllers;
    QLinkedList<Controller*> conFromFreq(ConFreq);
};

#endif // MAINCONTROLLER_H
