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

public slots:

signals:

private:
    QString notes;
    QTextEdit* uiNotes;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TEMPNOTESCONTROLLER_H
