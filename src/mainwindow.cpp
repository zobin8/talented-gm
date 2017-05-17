#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include "talentdata.h"
#include "npc.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    ui->setupUi(this);
    data = new TalentData();

    updateEditorNPC();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
}

QString MainWindow::randName()
{
    return "Custom NPC #" + QString::number(qrand() % 1000000);
}

void MainWindow::updateEditorNPC(QString name)
{
    NPC* npc = currentEditorNPC(name);

    if (npc)
    {
        ui->editNPCName->setText(npc->getName());
        ui->editBodySpin->setValue(npc->body);
        ui->editCoordSpin->setValue(npc->coord);
        ui->editSenseSpin->setValue(npc->sense);
        ui->editMindSpin->setValue(npc->mind);
        ui->editCharmSpin->setValue(npc->charm);
        ui->editCommSpin->setValue(npc->comm);
    }
    else
    {
        name = randName();
        ui->editNPCName->setText(name);
        ui->editBodySpin->setValue(0);
        ui->editCoordSpin->setValue(0);
        ui->editSenseSpin->setValue(0);
        ui->editMindSpin->setValue(0);
        ui->editCharmSpin->setValue(0);
        ui->editCommSpin->setValue(0);
    }

    ui->editNPCCombo->clear();
    ui->editNPCCombo->addItem("Custom");
    foreach (NPC* anNPC, data->getNPCTemplates())
    {
        ui->editNPCCombo->addItem(anNPC->getName());
    }
    ui->editNPCCombo->setCurrentText(name);
}

NPC* MainWindow::currentEditorNPC(QString name)
{
    if (name == "Custom") name = ui->editNPCCombo->currentText();
    NPC* npc = data->getNPCFromName(name);
    return npc;
}

void MainWindow::on_editNPCCombo_activated(const QString &name)
{
    updateEditorNPC(name);
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    NPC* npc = currentEditorNPC();
    if (npc)
    {
        npc = new NPC(npc);
    }
    else
    {
        npc = new NPC();
    }

    QString name = ui->editNPCName->text();
    if (name == "Custom")
    {
        npc->setName(randName());
    }
    else
    {
        npc->setName(name);
    }
    npc->body = ui->editBodySpin->value();
    npc->coord = ui->editCoordSpin->value();
    npc->sense = ui->editSenseSpin->value();
    npc->mind = ui->editMindSpin->value();
    npc->charm = ui->editCharmSpin->value();
    npc->comm = ui->editCommSpin->value();

    data->addNPCTemplate(npc);

    updateEditorNPC(npc->getName());
}
