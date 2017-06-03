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

signals:

public slots:

private:
    QTextEdit* uiNotes;
    QString notes;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TURNNOTESCONTROLLER_H
