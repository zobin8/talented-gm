#ifndef TEMPNOTESCONTROLLER_H
#define TEMPNOTESCONTROLLER_H

#include "controller.h"

class QTextEdit;

class TempNotesController : public Controller
{
    Q_OBJECT
public:
    explicit TempNotesController(QObject *parent = 0);

    void setWidgets(QTextEdit* tempEdit);

    void toView();
    void fromModel();
    void fromView();
    void toModel();

public slots:

signals:

private:
    QString notes;
    QTextEdit* uiNotes;
};

#endif // TEMPNOTESCONTROLLER_H
