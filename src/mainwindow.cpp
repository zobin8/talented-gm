#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "npc.h"
#include "menumodule.h"
#include "stringvaluepair.h"
#include <QDateTime>
#include <QLinkedList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());

    ui->setupUi(this);
    ui->editHitScrollContents->layout()->setAlignment(Qt::AlignTop);

    data = new TalentData();

    updateEditorNPC();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
    foreach(MenuModule* module, hitBoxModules)
    {
        delete module;
    }
}

QString MainWindow::randName()
{
    return "Custom NPC #" + QString::number(qrand() % 1000000);
}

void MainWindow::updateEditorNPC(QString name)
{
    QLayout* hitLayout = ui->editHitScrollContents->layout();
    while (hitLayout->count() > 0)
    {
        QWidget* w =  hitLayout->itemAt(0)->widget();
        hitLayout->removeWidget(w);
        delete w;
    }

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

        foreach(SVP hit, *(npc->getHitBoxes()))
        {
            addHitBox(hit.string, hit.value);
        }
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

void MainWindow::addHitBox(QString s, double v)
{
    MenuModule* hitModule = new MenuModule();
    hitModule->setValue(SVP(s, v));

    QVBoxLayout* hitLayout = (QVBoxLayout*) ui->editHitScrollContents->layout();
    int index = hitLayout->count() - 2;
    hitLayout->insertWidget(index, hitModule);
}

NPC* MainWindow::makeNPC()
{
    NPC* npc = new NPC();

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

    QLayout* hitLayout = ui->editHitScrollContents->layout();
    for (int i = 0; i < hitLayout->count(); i++)
    {
        QWidget* widget = hitLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            npc->addHitBox(menuMod->getValue());
        }
    }

    return npc;
}

void MainWindow::on_editNPCCombo_activated(const QString &name)
{
    updateEditorNPC(name);
}

void MainWindow::on_editNPCtoTempButton_clicked()
{
    NPC* npc = makeNPC();

    data->addNPCTemplate(npc);

    updateEditorNPC(npc->getName());
}

void MainWindow::on_editAddHitButton_clicked()
{
    addHitBox();
}
