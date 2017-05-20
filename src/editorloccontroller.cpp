#include "editorloccontroller.h"
#include "locationtemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include "ui_mainwindow.h"

EditorLocController::EditorLocController(QObject *parent) : Controller(parent)
{
    locTemp = new LocationTemplate();
}

EditorLocController::~EditorLocController()
{
    delete locTemp;
}

void EditorLocController::deleteNPC(NPCTemplate* npcTemp)
{

}

void EditorLocController::toView()
{
    ui->editLocationCombo->clear();
    ui->editLocationCombo->addItem("Custom");
    foreach (LocationTemplate* aLoc, TalentData::getInstance().getLocTemplates())
    {
        ui->editLocationCombo->addItem(aLoc->getName());
    }
    ui->editLocationCombo->setCurrentText(locTemp->getName());
}

void EditorLocController::fromModel()
{
    QString name = ui->editLocationCombo->currentText();
    LocationTemplate* loc = TalentData::getInstance().getLocFromName(name);

    delete locTemp;
    if (loc)
    {
        locTemp = new LocationTemplate(loc);
    }
    else
    {
        locTemp = new LocationTemplate();
    }

    //TODO: See EditorNPCController::fromModel()
    toView();
}

void EditorLocController::fromView()
{
    locTemp->setName(ui->editLocationName->text());
}
