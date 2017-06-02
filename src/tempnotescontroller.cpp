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

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
}

void TempNotesController::toView()
{
    uiNotes->setPlainText(notes);
}

void TempNotesController::toModel()
{
    TalentData::getTalentFile()->setNoteTemplate(notes);
    emit updateView(ConFreq::hash);
}

void TempNotesController::fromModel()
{
    notes = TalentData::getTalentFile()->getNoteTemplate();
}

void TempNotesController::fromView()
{
    notes = uiNotes->toPlainText();
}

