#ifndef TURNNOTESCONTROLLER_H
#define TURNNOTESCONTROLLER_H

#include "controller.h"

class QTextEdit;

class TurnNotesController : public Controller
{
    Q_OBJECT
public:
    explicit TurnNotesController(QObject *parent = 0);

    void setWidgets(QTextEdit* turnNotes);

    void toView();
    void toModel();
    void fromModel();
    void fromView();

signals:

public slots:

private:
    QTextEdit* uiNotes;
    QString notes;
};

#endif // TURNNOTESCONTROLLER_H
