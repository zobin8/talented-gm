#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "npctemplate.h"
#include "svpmenumodule.h"
#include "svp.h"
#include "maincontroller.h"
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

    mc = new MainController();
    setControllerWidgets();

    QString path = ":/default/default.tgm";
    QString argPath = "";

    if (QCoreApplication::arguments().count() > 1)
    {
        argPath = QCoreApplication::arguments().at(1);
    }

    if (fileOkay(argPath, false))
    {
        mc->fileController->openFile(argPath);
        mc->fileController->loadFile();
    }
    else
    {
        mc->fileController->openFile(path);
        mc->fileController->loadFile();
        mc->fileController->closeFile();
    }

    ui->tabWidget->setCurrentWidget(ui->generalTab);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mc;
}

void MainWindow::setControllerWidgets()
{
    mc->editorNPCController->setWidgets(ui->editHitScrollContents,
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
    mc->editorLocController->setWidgets(ui->editLocationCombo,
                                        ui->editLocationName,
                                        ui->editMinionSpin1,
                                        ui->editMinionSpin2,
                                        ui->editLocContents,
                                        ui->editLocNPCCombo,
                                        ui->editLocDesc);

    mc->tempLocController->setWidgets(ui->tempLocContents);
    mc->tempNPCController->setWidgets(ui->tempNPCContents);
    mc->tempPlayerController->setWidgets(ui->tempPlayerContents);
    mc->tempNotesController->setWidgets(ui->tempEdit);

    mc->generalController->setWidgets(ui->generalEdit);
    mc->fileController->setWidgets(ui->statusBar);

    mc->turnController->setWidgets(ui->turnCounterLabel);
    mc->turnNotesController->setWidgets(ui->turnEdit);
    mc->turnLocController->setWidgets(ui->turnMinionSpin1,
                                                      ui->turnMinionSpin2,
                                                      ui->turnLocationLabel,
                                                      ui->turnNPCContents,
                                                      ui->turnLocDescription);
    mc->turnInitController->setWidgets(ui->turnInitContents);
    mc->turnInfoController->setWidgets(ui->turnStatContents,
                                                       ui->turnSkillContents,
                                                       ui->turnNPCDescription);
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

    mc->on_updateView(ConFreq::editNPC);

    running = false;
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    if (running) return;
    running = true;
    mc->editorNPCController->toTemp();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddHitButton_clicked()
{
    if (running) return;
    running = true;

    mc->editorNPCController->addSVPModule();

    running = false;
}

void MainWindow::on_editAddSkillButton_clicked()
{
    if (running) return;
    running = true;

    mc->editorNPCController->addSkillModule();

    running = false;
}

void MainWindow::on_editLocationCombo_activated(const QString&)
{
    if (running) return;
    running = true;

    mc->on_updateView(ConFreq::editLoc);
    running = false;
}

void MainWindow::on_editAddLocTempButton_clicked()
{
    if (running) return;
    running = true;

    mc->editorLocController->toTemp();

    running = false;

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddNPCButton_clicked()
{
    if (running) return;
    running = true;

    mc->editorLocController->addNPCModule();

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

    mc->tempPlayerController->addPlayer();

    running = false;
}

void MainWindow::on_actionQuit_triggered()
{
    FileAbortResponse res = mc->fileController->abortClose();
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

    FileAbortResponse res = mc->fileController->abortClose();
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

    FileAbortResponse res = mc->fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        mc->fileController->newFile();
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

    FileAbortResponse res = mc->fileController->abortClose();
    if (res == FileAbortResponse::Okay)
    {
        //TODO: Clean up, put in functions. Need to hotfix right now.
        QString path = pickTGMFile(false);
        if (path != "")
        {
            mc->fileController->openFile(path);
            mc->fileController->loadFile();
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

    if (mc->fileController->hasFile())
    {
        mc->on_updateModel(ConFreq::all);

        mc->fileController->saveFile();
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
        mc->on_updateModel(ConFreq::all);

        mc->fileController->openFile(path);
        mc->fileController->saveFile();
    }

    running = false;
}

void MainWindow::on_actionExport_to_log_triggered()
{
    if (running) return;
    running = true;

    mc->on_updateModel(ConFreq::all);

    QString path = pickLogFile();
    if (path != "")
    {
        mc->on_updateModel(ConFreq::all);

        mc->fileController->exportToLog(path);
    }

    running = false;
}

void MainWindow::on_actionAdd_triggered()
{
    if (running) return;
    running = true;

    mc->turnController->addTurn();

    running = false;
}

void MainWindow::on_actionDelete_triggered()
{
    if (running) return;
    running = true;

    mc->turnController->deleteTurn();

    running = false;
}

void MainWindow::on_actionPrevious_turn_triggered()
{
    if (running) return;
    running = true;

    mc->turnController->prevTurn();

    running = false;
}

void MainWindow::on_actionNext_triggered()
{
    if (running) return;
    running = true;

    mc->turnController->nextTurn();

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
    mc->editorLocController->toTurn();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_editNPCToTurn_clicked()
{
    if (running) return;
    running = true;
    mc->editorNPCController->toTurn();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->turnTab);
}

void MainWindow::on_tempToTurnButton_clicked()
{
    if (running) return;
    running = true;
    mc->tempPlayerController->toTurn();
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
