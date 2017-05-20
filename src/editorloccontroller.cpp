#include "editorloccontroller.h"
#include "locationtemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include <QComboBox>
#include <QLineEdit>

EditorLocController::EditorLocController(QObject *parent) : Controller(parent)
{
    locTemp = new LocationTemplate();
}

EditorLocController::~EditorLocController()
{
    delete locTemp;
}

void EditorLocController::setWidgets(QComboBox* editLocationCombo, QLineEdit* editLocationName)
{
    uiCombo = editLocationCombo;
    uiName = editLocationName;
}

void EditorLocController::deleteNPC(NPCTemplate* npcTemp)
{

}

void EditorLocController::toView()
{
    uiCombo->clear();
    uiCombo->addItem("Custom");
    foreach (LocationTemplate* aLoc, TalentData::getInstance().getLocTemplates())
    {
        uiCombo->addItem(aLoc->getName());
    }
    uiCombo->setCurrentText(locTemp->getName());

    uiName->setText(locTemp->getName());
}

void EditorLocController::fromModel()
{
    QString name = uiCombo->currentText();
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
    locTemp->setName(uiName->text());
}

void EditorLocController::toTemplate()
{
    fromView();

    LocationTemplate* temp = new LocationTemplate(locTemp);
    TalentData::getInstance().addLocTemplate(temp);

    toView();
}
