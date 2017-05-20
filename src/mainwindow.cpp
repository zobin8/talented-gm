#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "npctemplate.h"
#include "menumodule.h"
#include "stringvaluepair.h"
#include "editornpccontroller.h"
#include "editorloccontroller.h"
#include <QDateTime>
#include <QLinkedList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    ui->setupUi(this);
    ui->editHitScrollContents->layout()->setAlignment(Qt::AlignTop);
    ui->editLocContents->layout()->setAlignment(Qt::AlignTop);

    editorNPCController = new EditorNPCController();
    editorLocController = new EditorLocController();

    setControllerWidgets();

    editorNPCController->toView();
    editorLocController->toView();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editorNPCController;
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
                                    ui->editNPCCombo);

    editorLocController->setWidgets(ui->editLocationCombo,
                                    ui->editLocationName,
                                    ui->editMinionSpin1,
                                    ui->editMinionSpin2);
}

void MainWindow::on_editNPCCombo_activated(const QString& name)
{
    editorNPCController->fromModel();
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    editorNPCController->toTemplate();
}

void MainWindow::on_editAddHitButton_clicked()
{
    editorNPCController->addHitBox();
}

void MainWindow::on_editLocationCombo_activated(const QString& name)
{
    editorLocController->fromModel();
}

void MainWindow::on_editAddLocTempButton_clicked()
{
    editorLocController->toTemplate();
}

void MainWindow::on_editAddNPCButton_clicked()
{
    //TODO
}
