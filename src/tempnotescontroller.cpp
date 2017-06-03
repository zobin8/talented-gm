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

    view.append(uiNotes);

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
}

void TempNotesController::toView()
{
    uiNotes->setPlainText(notes);
}

void TempNotesController::toModel()
{
    TalentData::lockTalentFile()->setNoteTemplate(notes);
    TalentData::unlockTalentFile();
}

void TempNotesController::fromModel()
{
    notes = TalentData::lockTalentFile()->getNoteTemplate();
    TalentData::unlockTalentFile();
}

void TempNotesController::fromView()
{
    notes = uiNotes->toPlainText();
}

