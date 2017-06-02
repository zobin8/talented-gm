#include "maincontroller.h"

MainController::MainController(QObject *parent) : Controller(parent)
{
    editorNPCController = new EditorNPCController();
    editorLocController = new EditorLocController();
    tempLocController = new TempLocController();
    tempNPCController = new TempNPCController();
    tempPlayerController = new TempPlayerController();
    fileController = new FileController();
    generalController = new GeneralController();
    tempNotesController = new TempNotesController();
    turnController = new TurnController();
    turnNotesController = new TurnNotesController();
    turnLocController = new TurnLocController();
    turnInitController = new TurnInitController();
    turnInfoController = new TurnInfoController();
    hashController = new HashController();

    controllers = QLinkedList<Controller*>();
    controllers.append(editorNPCController);
    controllers.append(editorLocController);
    controllers.append(tempLocController);
    controllers.append(tempNPCController);
    controllers.append(tempPlayerController);
    controllers.append(fileController);
    controllers.append(generalController);
    controllers.append(tempNotesController);
    controllers.append(turnController);
    controllers.append(turnLocController);
    controllers.append(turnNotesController);
    controllers.append(turnInitController);
    controllers.append(turnInfoController);
    controllers.append(hashController);

    connectControllers();
}

MainController::~MainController()
{
    delete editorNPCController;
    delete editorLocController;
    delete tempLocController;
    delete tempNPCController;
    delete tempPlayerController;
    delete fileController;
    delete generalController;
    delete tempNotesController;
    delete turnController;
    delete turnNotesController;
    delete turnLocController;
    delete turnInitController;
    delete turnInfoController;
    delete hashController;
}

void MainController::connectControllers()
{
    connect(editorNPCController, SIGNAL(setNPCNames(QStringList)), editorLocController, SLOT(on_NPCNamesChanged(QStringList)));

    connect(turnLocController, SIGNAL(deletedNPC(QString)), turnInitController, SLOT(deleteInit(QString)));
    connect(tempPlayerController, SIGNAL(deletedPlayer(QString)), turnInitController, SLOT(deleteInit(QString)));
    connect(turnLocController, SIGNAL(deletedNPC(QString)), turnInfoController, SLOT(on_deleteNPC(QString)));

    connect(turnLocController, SIGNAL(viewNPC(NPC*)), turnInfoController, SLOT(on_viewNPC(NPC*)));
    connect(editorLocController, SIGNAL(viewNPC(NPC*)), turnInfoController, SLOT(on_viewNPC(NPC*)));

    connect(hashController, SIGNAL(unsavedChange(bool)), fileController, SLOT(on_unsavedChange(bool)));
    connect(fileController, SIGNAL(savedChange()), hashController, SLOT(on_savedChange()));

    foreach (Controller* con, controllers)
    {
        connect(con, SIGNAL(updateModel(ConFreq)), this, SLOT(on_updateModel(ConFreq)));
        connect(con, SIGNAL(updateView(ConFreq)), this, SLOT(on_updateView(ConFreq)));
    }
}

void MainController::toView()
{
    foreach (Controller* con, controllers)
    {
        con->toView();
    }
}

void MainController::toModel()
{
    foreach (Controller* con, controllers)
    {
        con->toModel();
    }
}

void MainController::fromModel()
{
    foreach (Controller* con, controllers)
    {
        con->fromModel();
    }
}

void MainController::fromView()
{
    foreach (Controller* con, controllers)
    {
        con->fromView();
    }
}

QLinkedList<Controller*> MainController::conFromFreq(ConFreq cf)
{
    QLinkedList<Controller*> update = QLinkedList<Controller*>();

    switch(cf)
    {
    case ConFreq::editLoc:
        update.append(editorLocController);
        break;
    case ConFreq::editNPC:
        update.append(editorNPCController);
        break;
    case ConFreq::tempLoc:
        update.append(tempLocController);
        break;
    case ConFreq::tempNPC:
        update.append(tempNPCController);
        break;
    case ConFreq::turnLoc:
        update.append(turnLocController);
        break;
    case ConFreq::turnInit:
        update.append(turnInitController);
        break;
    case ConFreq::turn:
        update.append(turnController);
        update.append(turnLocController);
        update.append(turnInitController);
        update.append(turnInfoController);
        update.append(turnNotesController);
        break;
    case ConFreq::hash: break;
    case ConFreq::allButFile:
        update = QLinkedList<Controller*>(controllers);
        update.removeOne(fileController);
        break;
    case ConFreq::all:
        update = QLinkedList<Controller*>(controllers);
        break;
    }
    update.append(hashController);

    return update;
}

void MainController::on_updateView(ConFreq cf)
{
    QLinkedList<Controller*> update = conFromFreq(cf);

    foreach (Controller* con, update)
    {
        con->fromModel();
        con->toView();
    }
}

void MainController::on_updateModel(ConFreq cf)
{
    QLinkedList<Controller*> update = conFromFreq(cf);

    foreach (Controller* con, update)
    {
        con->fromView();
        con->toModel();
    }
}
