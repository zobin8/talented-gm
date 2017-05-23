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

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
}

void GeneralController::toView()
{
    uiNotes->setPlainText(notes);
}

void GeneralController::fromModel()
{
    notes = TalentData::getTalentFile()->getNotes();
}

void GeneralController::fromView()
{
    notes = uiNotes->toPlainText();
}

void GeneralController::on_textChanged()
{
    fromView();
    TalentData::getTalentFile()->setNotes(notes);
}
