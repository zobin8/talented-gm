#include "turnnotescontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include "turn.h"
#include <QTextEdit>

TurnNotesController::TurnNotesController(QObject* parent) : Controller(parent)
{
    notes = "";
}

void TurnNotesController::setWidgets(QTextEdit* turnNotes)
{
    uiNotes = turnNotes;
}

void TurnNotesController::toView()
{
    uiNotes->setText(notes);
}

void TurnNotesController::toModel()
{
    TalentData::getTalentFile()->currentTurn()->setNotes(notes);
}

void TurnNotesController::fromModel()
{
    notes = TalentData::getTalentFile()->currentTurn()->getNotes();
}

void TurnNotesController::fromView()
{
    notes = uiNotes->toPlainText();
}
