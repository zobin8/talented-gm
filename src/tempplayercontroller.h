#ifndef TEMPPLAYERCONTROLLER_H
#define TEMPPLAYERCONTROLLER_H

#include "controller.h"

class SVP;
class MenuModule;

class TempPlayerController : public Controller
{
    Q_OBJECT
public:
    explicit TempPlayerController(QObject *parent = 0);
    ~TempPlayerController();

    void toView();
    void fromModel();
    void toModel();
    void fromView();
    void setWidgets(QWidget* tempPlayerContents);
    void addPlayer();

signals:

public slots:
    void on_deletionEvent(MenuModule*);
    void on_uiUpdate();

private:
    QLinkedList<SVP>* players;
    QWidget* uiPlayerContents;

    void addPlayerView(QString s = "", double v = 0);
};

#endif // TEMPPLAYERCONTROLLER_H
