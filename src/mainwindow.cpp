#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "npctemplate.h"
#include "menumodule.h"
#include "stringvaluepair.h"
#include "editornpccontroller.h"
#include <QDateTime>
#include <QLinkedList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    ui->setupUi(this);
    ui->editHitScrollContents->layout()->setAlignment(Qt::AlignTop);

    editorNPCController = new EditorNPCController();
    editorNPCController->setUi(ui);
    editorNPCController->toView();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editorNPCController;
}

/*NPCTemplate* MainWindow::currentEditorNPC(QString name)
{
    if (name == "Custom") name = ui->editNPCCombo->currentText();
    NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);
    return npc;
}*/


void MainWindow::on_editNPCCombo_activated(const QString &name)
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
