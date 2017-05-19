#include "editornpccontroller.h"
#include "npctemplate.h"
#include "ui_mainwindow.h"
#include "talentdata.h"
#include "menumodule.h"
#include "stringvaluepair.h"

EditorNPCController::EditorNPCController(QObject* parent) : Controller(parent)
{
    npcTemp = new NPCTemplate();
}

EditorNPCController::~EditorNPCController()
{
    delete npcTemp;
}

void EditorNPCController::makeNPC()
{
    npcTemp->getHitBoxes()->clear();
    QLayout* hitLayout = ui->editHitScrollContents->layout();
    for (int i = 0; i < hitLayout->count(); i++)
    {
        QWidget* widget = hitLayout->itemAt(i)->widget();
        MenuModule* menuMod = dynamic_cast<MenuModule*>(widget);
        if (menuMod)
        {
            npcTemp->addHitBox(menuMod->getValue());
        }
    }

    npcTemp->setName(ui->editNPCName->text());
    npcTemp->body = ui->editBodySpin->value();
    npcTemp->coord = ui->editCoordSpin->value();
    npcTemp->sense = ui->editSenseSpin->value();
    npcTemp->mind = ui->editMindSpin->value();
    npcTemp->charm = ui->editCharmSpin->value();
    npcTemp->comm = ui->editCommSpin->value();
}

void EditorNPCController::draw()
{
    QLayout* hitLayout = ui->editHitScrollContents->layout();
    while (hitLayout->count() > 0)
    {
        QWidget* w =  hitLayout->itemAt(0)->widget();
        hitLayout->removeWidget(w);
        delete w;
    }

    foreach(SVP hit, *(npcTemp->getHitBoxes()))
    {
        addHitBox(hit.string, hit.value);
    }

    ui->editNPCName->setText(npcTemp->getName());
    ui->editBodySpin->setValue(npcTemp->body);
    ui->editCoordSpin->setValue(npcTemp->coord);
    ui->editSenseSpin->setValue(npcTemp->sense);
    ui->editMindSpin->setValue(npcTemp->mind);
    ui->editCharmSpin->setValue(npcTemp->charm);
    ui->editCommSpin->setValue(npcTemp->comm);

    ui->editNPCCombo->clear();
    ui->editNPCCombo->addItem("Custom");
    foreach (NPCTemplate* anNPC, TalentData::getInstance().getNPCTemplates())
    {
        ui->editNPCCombo->addItem(anNPC->getName());
    }
    ui->editNPCCombo->setCurrentText(npcTemp->getName());
}

void EditorNPCController::load()
{
    QString name = ui->editNPCCombo->currentText();
    NPCTemplate* npc = TalentData::getInstance().getNPCFromName(name);

    delete npcTemp;
    if (npc)
    {
        npcTemp = new NPCTemplate(npc);
    }
    else
    {
        npcTemp = new NPCTemplate();
    }

    draw();
}

void EditorNPCController::toTemplate()
{
    makeNPC();

    NPCTemplate* temp = new NPCTemplate(npcTemp);
    TalentData::getInstance().addNPCTemplate(temp);
    draw();
}

void EditorNPCController::addHitBox(QString s, double v)
{
    MenuModule* hitModule = new MenuModule();
    hitModule->setValue(SVP(s, v));

    QVBoxLayout* hitLayout = (QVBoxLayout*) ui->editHitScrollContents->layout();
    int index = hitLayout->count() - 1;
    hitLayout->insertWidget(index, hitModule);

    connect(hitModule, SIGNAL(killMe(MenuModule*)), this, SLOT(deleteHitBox(MenuModule*)));
}

void EditorNPCController::deleteHitBox(MenuModule* menuMod)
{
    QVBoxLayout* hitLayout = (QVBoxLayout*) ui->editHitScrollContents->layout();
    hitLayout->removeWidget(menuMod);
    delete menuMod;
}
