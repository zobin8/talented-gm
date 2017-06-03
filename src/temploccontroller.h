#ifndef TEMPLOCCONTROLLER_H
#define TEMPLOCCONTROLLER_H

#include "controller.h"
#include <QLinkedList>

class MenuModule;
class LocTemplate;

class TempLocController : public Controller
{
    Q_OBJECT
public:
    explicit TempLocController(QObject *parent = 0);

    void setWidgets(QWidget* tempLocContents);

signals:

public slots:
    void on_deletionEvent(MenuModule*);

private:
    QLinkedList<LocTemplate*> locTemplates;
    QWidget* uiLocContents;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TEMPLOCCONTROLLER_H
