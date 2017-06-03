#include "generalcontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QTextEdit>

GeneralController::GeneralController(QObject *parent) : Controller(parent)
{

}

void GeneralController::setWidgets(QTextEdit* generalNotes)
{
    uiNotes = generalNotes;

    view.append(uiNotes);

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
}

void GeneralController::toView()
{
    uiNotes->setPlainText(notes);
}

void GeneralController::toModel()
{
    TalentData::lockTalentFile()->setNotes(notes);
    TalentData::unlockTalentFile();
}

void GeneralController::fromModel()
{
    notes = TalentData::lockTalentFile()->getNotes();
    TalentData::unlockTalentFile();
}

void GeneralController::fromView()
{
    notes = uiNotes->toPlainText();
}
