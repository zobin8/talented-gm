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
#include <QDateTime>
#include <QLinkedList>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

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

    controllers = QLinkedList<Controller*>();
    controllers.append(editorNPCController);
    controllers.append(editorLocController);
    controllers.append(tempLocController);
    controllers.append(tempNPCController);
    controllers.append(tempPlayerController);

    connectControllers();
    setControllerWidgets();

    foreach (Controller* con, controllers)
    {
        con->fromModel();
        con->toView();
    }
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
}

void MainWindow::on_editNPCCombo_activated(const QString& name)
{
    editorNPCController->fromModel();
    editorNPCController->toView();
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    editorNPCController->toTemplate();

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddHitButton_clicked()
{
    editorNPCController->addModule(ui->editHitScrollContents);
}

void MainWindow::on_editAddSkillButton_clicked()
{
    editorNPCController->addModule(ui->editSkillScrollContents);
}

void MainWindow::on_editLocationCombo_activated(const QString& name)
{
    editorLocController->fromModel();
    editorLocController->toView();
}

void MainWindow::on_editAddLocTempButton_clicked()
{
    editorLocController->toTemplate();

    ui->tabWidget->setCurrentWidget(ui->templatesTab);
}

void MainWindow::on_editAddNPCButton_clicked()
{
    editorLocController->addNPCModule();
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
    tempPlayerController->addPlayer();
}

void MainWindow::on_tempEdit_textChanged()
{
    TalentData::getInstance().setNoteTemplate(ui->tempEdit->toPlainText());
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
    event->accept();
}
