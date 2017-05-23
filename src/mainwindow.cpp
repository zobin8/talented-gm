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

#include <QDateTime>
#include <QLinkedList>
#include <QCloseEvent>
#include <QFileDialog>

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

    editorNPCController = new EditorNPCController();
    editorLocController = new EditorLocController();
    tempLocController = new TempLocController();
    tempNPCController = new TempNPCController();
    tempPlayerController = new TempPlayerController();
    fileController = new FileController();
    generalController = new GeneralController();

    controllers = QLinkedList<Controller*>();
    controllers.append(editorNPCController);
    controllers.append(editorLocController);
    controllers.append(tempLocController);
    controllers.append(tempNPCController);
    controllers.append(tempPlayerController);
    controllers.append(fileController);
    controllers.append(generalController);

    connectControllers();
    setControllerWidgets();

    foreach (Controller* con, controllers)
    {
        con->fromModel();
        con->toView();
    }

    fileController->newFile();
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

    connect(fileController, SIGNAL(update()), generalController, SLOT(on_update()));
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
                                    ui->editSkillScrollContents);
    editorLocController->setWidgets(ui->editLocationCombo,
                                    ui->editLocationName,
                                    ui->editMinionSpin1,
                                    ui->editMinionSpin2,
                                    ui->editLocContents,
                                    ui->editLocNPCCombo);

    tempLocController->setWidgets(ui->tempLocContents);
    tempNPCController->setWidgets(ui->tempNPCContents);
    tempPlayerController->setWidgets(ui->tempPlayerContents);

    generalController->setWidgets(ui->generalEdit);
}

QString MainWindow::pickFile(bool allowNew)
{
    QFileDialog fileDialog(this, "Choose a file");
    fileDialog.setNameFilter("TalentedGM Files (*.tgm)");
    fileDialog.setDefaultSuffix(".tgm");
    if (allowNew)
    {
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    }
    else
    {
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    }
    fileDialog.exec();

    QString path = fileDialog.selectedFiles().first();
    QFileInfo check(path);
    if (check.exists() && check.isFile())
    {
        return path;
    }
    else
    {
        if (!check.exists() && allowNew)
        {
            return path;
        }
        else
        {
            return QString("");
        }
    }
}

void MainWindow::on_editNPCCombo_activated(const QString& name)
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
    editorNPCController->toTemplate();
    running = false;

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddHitButton_clicked()
{
    if (running) return;
    running = true;

    editorNPCController->addModule(ui->editHitScrollContents);

    running = false;
}

void MainWindow::on_editAddSkillButton_clicked()
{
    if (running) return;
    running = true;

    editorNPCController->addModule(ui->editSkillScrollContents);

    running = false;
}

void MainWindow::on_editLocationCombo_activated(const QString& name)
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

    editorLocController->toTemplate();

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

void MainWindow::on_tempAddLocationButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->editorTab);
}

void MainWindow::on_tempAddNPCButton_clicked()
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

void MainWindow::on_tempEdit_textChanged()
{
    if (running) return;
    running = true;

    TalentData::getTalentFile()->setNoteTemplate(ui->tempEdit->toPlainText());

    running = false;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
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

    event->accept();

    running = false;
}

void MainWindow::on_actionNew_triggered()
{
    fileController->newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = pickFile(false);
    if (path != "")
    {
        fileController->openFile(path);
        fileController->loadFile();
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (fileController->hasFile())
    {
        fileController->saveFile();
    }
    else
    {
        on_actionSave_as_triggered();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString path = pickFile(true);
    if (path != "")
    {
        fileController->openFile(path);
        fileController->saveFile();
    }
}

void MainWindow::on_actionExport_to_log_triggered()
{
    //TODO: this function
}
