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

    connect(uiNotes, SIGNAL(textChanged()), this, SLOT(on_viewUpdate()));
}

void GeneralController::toView()
{
    uiNotes->setPlainText(notes);
}

void GeneralController::toModel()
{
    TalentData::getTalentFile()->setNotes(notes);
    emit updateView(ConFreq::hash);
}

void GeneralController::fromModel()
{
    notes = TalentData::getTalentFile()->getNotes();
}

void GeneralController::fromView()
{
    notes = uiNotes->toPlainText();
}
