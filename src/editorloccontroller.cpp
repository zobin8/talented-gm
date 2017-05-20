#include "editorloccontroller.h"
#include "locationtemplate.h"
#include "npctemplate.h"
#include "talentdata.h"
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>

EditorLocController::EditorLocController(QObject *parent) : Controller(parent)
{
    locTemp = new LocationTemplate();
}

EditorLocController::~EditorLocController()
{
    delete locTemp;
}

void EditorLocController::setWidgets(QComboBox *editLocationCombo, QLineEdit *editLocationName, QSpinBox *editMinionSpin1, QSpinBox *editMinionSpin2)
{
    uiCombo = editLocationCombo;
    uiName = editLocationName;
    uiMinions1 = editMinionSpin1;
    uiMinions2 = editMinionSpin2;
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
    uiMinions1->setValue(locTemp->minions1);
    uiMinions2->setValue(locTemp->minions2);
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
    locTemp->minions1 = uiMinions1->value();
    locTemp->minions2 = uiMinions2->value();
}

void EditorLocController::toTemplate()
{
    fromView();

    LocationTemplate* temp = new LocationTemplate(locTemp);
    TalentData::getInstance().addLocTemplate(temp);

    toView();
}
