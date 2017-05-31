#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "npctemplate.h"
#include "svpmenumodule.h"
#include "svp.h"

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

#include <QDateTime>
#include <QLinkedList>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    running = false;

    ui->setupUi(this);
    ui->editHitScrollContents->layout()->setAlignment(Qt::AlignTop);
    ui->editLocContents->layout()->setAlignment(Qt::AlignTop);
    ui->editSkillScrollContents->layout()->setAlignment(Qt::AlignTop);
    ui->tempLocContents->layout()->setAlignment(Qt::AlignTop);
    ui->tempNPCContents->layout()->setAlignment(Qt::AlignTop);
    ui->tempPlayerContents->layout()->setAlignment(Qt::AlignTop);
    ui->turnNPCContents->layout()->setAlignment(Qt::AlignTop);
    ui->turnInitContents->layout()->setAlignment(Qt::AlignTop);
    ui->turnSkillContents->layout()->setAlignment(Qt::AlignTop);
    ui->turnStatContents->layout()->setAlignment(Qt::AlignTop);

    editorNPCController = new EditorNPCController();
    editorLocController = new EditorLocController();
    tempLocController = new TempLocController();
    tempNPCController = new TempNPCController();
    tempPlayerController = new TempPlayerController();
    fileController = new FileController();
    generalController = new GeneralController();
    tempNotesController = new TempNotesController();
    turnController = new TurnController();

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
    controllers.append(turnController->turnLocController);
    controllers.append(turnController->turnNotesController);
    controllers.append(turnController->turnInitController);
    controllers.append(turnController->turnInfoController);

    setControllerWidgets();
    connectControllers();

    QString path = ":/default/default.tgm";
    QString argPath = "";

    if (QCoreApplication::arguments().count() > 1)
    {
        argPath = QCoreApplication::arguments().at(1);
    }

    if (fileOkay(argPath, false))
    {
        fileController->openFile(argPath);
        fileController->loadFile();
    }
    else
    {
        fileController->openFile(path);
        fileController->loadFile();
        fileController->closeFile();
    }

    ui->tabWidget->setCurrentWidget(ui->generalTab);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editorNPCController;
}

void MainWindow::connectControllers()
{
    connect(editorNPCController, SIGNAL(setNPCNames(QStringList)), editorLocController, SLOT(on_NPCNamesChanged(QStringList)));

    connect(editorLocController, SIGNAL(update()), tempLocController, SLOT(on_update()));
    connect(tempLocController, SIGNAL(update()), editorLocController, SLOT(on_update()));

    connect(editorNPCController, SIGNAL(update()), tempNPCController, SLOT(on_update()));
    connect(tempNPCController, SIGNAL(update()), editorNPCController, SLOT(on_update()));

    connect(editorLocController, SIGNAL(update()), turnController->turnLocController, SLOT(on_update()));
    connect(editorNPCController, SIGNAL(update()), turnController->turnLocController, SLOT(on_update()));
    connect(editorNPCController, SIGNAL(update()), turnController->turnInitController, SLOT(on_update()));
    connect(editorLocController, SIGNAL(update()), turnController->turnInitController, SLOT(on_update()));

    connect(turnController->turnLocController, SIGNAL(deletedNPC(QString)), turnController->turnInitController, SLOT(deleteInit(QString)));
    connect(tempPlayerController, SIGNAL(deletedPlayer(QString)), turnController->turnInitController, SLOT(deleteInit(QString)));
    connect(tempPlayerController, SIGNAL(update()), turnController->turnInitController, SLOT(on_update()));

    connect(turnController->turnLocController, SIGNAL(viewNPC(NPC*)), turnController->turnInfoController, SLOT(on_viewNPC(NPC*)));
    connect(turnController->turnLocController, SIGNAL(deletedNPC(QString)), turnController->turnInfoController, SLOT(on_deleteNPC(QString)));
    connect(editorLocController, SIGNAL(viewNPC(NPC*)), turnController->turnInfoController, SLOT(on_viewNPC(NPC*)));

    foreach (Controller* con, controllers)
    {
        if (con != fileController)
        {
            connect(fileController, SIGNAL(update()), con, SLOT(on_update()));
            connect(con, SIGNAL(unsavedChange()), fileController, SLOT(on_unsavedChange()));
        }
    }
}

void MainWindow::setControllerWidgets()
{
    editorNPCController->setWidgets(ui->editHitScrollContents,
                                    ui->editNPCName,
                                    ui->editBodySpin,
                                    ui->editCoordSpin,
                                    ui->editSenseSpin,
                                    ui->editMindSpin,
                                    ui->editCharmSpin,
                                    ui->editCommSpin,
                                    ui->editNPCCombo,
                                    ui->editSkillScrollContents,
                                    ui->editNPCDesc);
    editorLocController->setWidgets(ui->editLocationCombo,
                                    ui->editLocationName,
                                    ui->editMinionSpin1,
                                    ui->editMinionSpin2,
                                    ui->editLocContents,
                                    ui->editLocNPCCombo,
                                    ui->editLocDesc);

    tempLocController->setWidgets(ui->tempLocContents);
    tempNPCController->setWidgets(ui->tempNPCContents);
    tempPlayerController->setWidgets(ui->tempPlayerContents);
    tempNotesController->setWidgets(ui->tempEdit);

    generalController->setWidgets(ui->generalEdit);
    fileController->setWidgets(ui->statusBar);

    turnController->setWidgets(ui->turnCounterLabel);
    turnController->turnNotesController->setWidgets(ui->turnEdit);
    turnController->turnLocController->setWidgets(ui->turnMinionSpin1,
                                                  ui->turnMinionSpin2,
                                                  ui->turnLocationLabel,
                                                  ui->turnNPCContents,
                                                  ui->turnLocDescription);
    turnController->turnInitController->setWidgets(ui->turnInitContents);
    turnController->turnInfoController->setWidgets(ui->turnStatContents,
                                                   ui->turnSkillContents,
                                                   ui->turnNPCDescription);
}

void MainWindow::fromView()
{
    foreach (Controller* con, controllers)
    {
        con->fromView();
    }
}

void MainWindow::toView()
{
    foreach (Controller* con, controllers)
    {
        con->toView();
    }
}

void MainWindow::fromModel()
{
    foreach (Controller* con, controllers)
    {
        con->fromModel();
    }
}

void MainWindow::toModel()
{
    foreach (Controller* con, controllers)
    {
        con->toModel();
    }
}

QString MainWindow::pickTGMFile(bool allowNew)
{
    QString filter = "TalentedGM Files (*.tgm)";
    QString suffix = ".tgm";
    return pickFile(allowNew, filter, suffix);
}

QString MainWindow::pickLogFile()
{
    QString filter = "TalentedGM Files (*.tgm)";
    QString suffix = ".tgm";
    bool allowNew = true;
    return pickFile(allowNew, filter, suffix);
}

bool MainWindow::fileOkay(QString path, bool allowNew)
{
    QFileInfo check(path);

    if (path == "")
    {
        return false;
    }
    else if (check.exists() && check.isFile())
    {
        return true;
    }
    else if (allowNew && !check.exists())
    {
        if (check.fileName().endsWith(".tgm"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

QString MainWindow::pickFile(bool allowNew, QString filter, QString suffix)
{
    QFileDialog fileDialog(this, "Choose a file");
    fileDialog.setNameFilter(filter);
    fileDialog.setDefaultSuffix(suffix);
    if (allowNew)
    {
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    }
    else
    {
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    }
    fileDialog.exec();

    QString path;
    if (fileDialog.selectedFiles().count() > 0)
    {
        path = fileDialog.selectedFiles().first();
    }
    else
    {
        return QString("");
    }

    if (fileOkay(path, allowNew))
    {
        return path;
    }
    else
    {
        return QString("");
    }
}

void MainWindow::on_editNPCCombo_activated(const QString&)
{
    if (running) return;
    running = true;

    editorNPCController->fromModel();
    editorNPCController->toView();

    running = false;
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    if (running) return;
    running = true;
    editorNPCController->toModel();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddHitButton_clicked()
{
    if (running) return;
    running = true;

    editorNPCController->addSVPModule();

    running = false;
}

void MainWindow::on_editAddSkillButton_clicked()
{
    if (running) return;
    running = true;

    editorNPCController->addSkillModule();

    running = false;
}

void MainWindow::on_editLocationCombo_activated(const QString&)
{
    if (running) return;
    running = true;

    editorLocController->fromModel();
    editorLocController->toView();

    running = false;
}

void MainWindow::on_editAddLocTempButton_clicked()
{
    if (running) return;
    running = true;

    editorLocController->toModel();

    running = false;

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddNPCButton_clicked()
{
    if (running) return;
    running = true;

    editorLocController->addNPCModule();

    running = false;
}

void MainWindow::on_tempAddTempButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->editorTab);
}

void MainWindow::on_tempNewPlayerButton_clicked()
{
    if (running) return;
    running = true;

    tempPlayerController->addPlayer();

    running = false;
}

void MainWindow::on_actionQuit_triggered()
{
    FileAbortResponse res = fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        QApplication::quit();
    }
    else if (res ==FileAbortResponse::Save)
    {
        on_actionSave_triggered();
        on_actionQuit_triggered();
    }
}

void MainWindow::on_actionGeneral_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->generalTab);

}

void MainWindow::on_actionTurns_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_actionTemplates_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_actionEditor_triggered()
{
    ui->tabWidget->setCurrentWidget(ui->editorTab);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (running) return;
    running = true;

    FileAbortResponse res = fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        event->accept();
    }
    else if (res == FileAbortResponse::Save)
    {
        running = false;
        on_actionSave_triggered();
        running = false;
        closeEvent(event);
    }
    else
    {
        event->ignore();
    }

    running = false;
}

void MainWindow::on_actionNew_triggered()
{
    if (running) return;
    running = true;

    FileAbortResponse res = fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        fileController->newFile();
    }
    else if (res == FileAbortResponse::Save)
    {
        running = false;
        on_actionSave_triggered();
        running = false;
        on_actionNew_triggered();
    }

    running = false;
}

void MainWindow::on_actionOpen_triggered()
{
    if (running) return;
    running = true;

    FileAbortResponse res = fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        //TODO: Clean up, put in functions. Need to hotfix right now.
        QString path = pickTGMFile(false);
        if (path != "")
        {
            fileController->openFile(path);
            fileController->loadFile();
        }
    }
    else if (res == FileAbortResponse::Save)
    {
        running = false;
        on_actionSave_triggered();
        running = false;
        on_actionOpen_triggered();
    }

    running = false;
}

void MainWindow::on_actionSave_triggered()
{
    if (running) return;
    running = true;

    if (fileController->hasFile())
    {
        fromView();
        toModel();

        fileController->saveFile();
    }
    else
    {
        running = false;
        on_actionSave_as_triggered();
    }

    running = false;
}

void MainWindow::on_actionSave_as_triggered()
{
    if (running) return;
    running = true;

    QString path = pickTGMFile(true);
    if (path != "")
    {
        fromView();
        toModel();

        fileController->openFile(path);
        fileController->saveFile();
    }

    running = false;
}

void MainWindow::on_actionExport_to_log_triggered()
{
    if (running) return;
    running = true;

    turnController->fromView();
    turnController->toModel();

    QString path = pickLogFile();
    if (path != "")
    {
        fromView();
        toModel();

        fileController->exportToLog(path);
    }

    running = false;
}

void MainWindow::on_actionAdd_triggered()
{
    if (running) return;
    running = true;

    turnController->addTurn();

    running = false;
}

void MainWindow::on_actionDelete_triggered()
{
    if (running) return;
    running = true;

    turnController->deleteTurn();

    running = false;
}

void MainWindow::on_actionPrevious_turn_triggered()
{
    if (running) return;
    running = true;

    turnController->prevTurn();

    running = false;
}

void MainWindow::on_actionNext_triggered()
{
    if (running) return;
    running = true;

    turnController->nextTurn();

    running = false;
}

void MainWindow::on_turnDeleteButton_clicked()
{
    on_actionDelete_triggered();
}
void MainWindow::on_turnPrevButton_clicked()
{
    on_actionPrevious_turn_triggered();
}
void MainWindow::on_turnNextButton_clicked()
{
    on_actionNext_triggered();
}
void MainWindow::on_turnAddButton_clicked()
{
    on_actionAdd_triggered();
}

void MainWindow::on_turnLoadButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->editorTab);
}

void MainWindow::on_editAddLocTurnButton_clicked()
{
    if (running) return;
    running = true;
    editorLocController->toTurn();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_editNPCToTurn_clicked()
{
    if (running) return;
    running = true;
    editorNPCController->toTurn();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_tempToTurnButton_clicked()
{
    if (running) return;
    running = true;
    tempPlayerController->toTurn();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_actionNext_Tab_triggered()
{
    int i = ui->tabWidget->currentIndex();
    i++;
    if (i >= ui->tabWidget->count())
    {
        i = 0;
    }
    ui->tabWidget->setCurrentIndex(i);
}

void MainWindow::on_actionPrevious_Tab_triggered()
{
    int i = ui->tabWidget->currentIndex();
    i--;
    if (i <= -1)
    {
        i = ui->tabWidget->count() - 1;
    }
    ui->tabWidget->setCurrentIndex(i);
}
