#include "tempnotescontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QTextEdit>

TempNotesController::TempNotesController(QObject *parent) : Controller(parent)
{

}

void TempNotesController::setWidgets(QTextEdit* tempEdit)
{
    uiNotes = tempEdit;

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
}

void TempNotesController::toView()
{
    uiNotes->setPlainText(notes);
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
    fromView();
    TalentData::getTalentFile()->setNoteTemplate(notes);
}
