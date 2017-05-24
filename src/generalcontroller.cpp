#include "generalcontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QTextEdit>

GeneralController::GeneralController(QObject *parent) : Controller(parent)
{
    naturalChange = false;
}

void GeneralController::setWidgets(QTextEdit* generalNotes)
{
    uiNotes = generalNotes;

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
}

void GeneralController::toView()
{
    uiNotes->setPlainText(notes);
}

void GeneralController::toModel()
{
    TalentData::getTalentFile()->setNotes(notes);
}

void GeneralController::fromModel()
{
    notes = TalentData::getTalentFile()->getNotes();
}

void GeneralController::fromView()
{
    naturalChange = true;
    notes = uiNotes->toPlainText();
    naturalChange = false;
}

void GeneralController::on_textChanged()
{
    if (!naturalChange) emit unsavedChange();

    fromView();
}
