#include "tempnotescontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QTextEdit>

TempNotesController::TempNotesController(QObject *parent) : Controller(parent)
{
    naturalChange = false;
}

void TempNotesController::setWidgets(QTextEdit* tempEdit)
{
    uiNotes = tempEdit;

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
}

void TempNotesController::toView()
{
    naturalChange = true;
    uiNotes->setPlainText(notes);
    naturalChange = false;
}

void TempNotesController::toModel()
{
    TalentData::getTalentFile()->setNoteTemplate(notes);
}

void TempNotesController::fromModel()
{
    notes = TalentData::getTalentFile()->getNoteTemplate();
}

void TempNotesController::fromView()
{
    notes = uiNotes->toPlainText();
}

void TempNotesController::on_textChanged()
{
    if (!naturalChange) emit unsavedChange();

    fromView();
    toModel();
}
