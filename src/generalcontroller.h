#ifndef GENERALCONTROLLER_H
#define GENERALCONTROLLER_H

#include "controller.h"

class QTextEdit;

class GeneralController : public Controller
{
    Q_OBJECT
public:
    explicit GeneralController(QObject *parent = 0);

    void setWidgets(QTextEdit* generalNotes);

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

#endif // GENERALCONTROLLER_H
