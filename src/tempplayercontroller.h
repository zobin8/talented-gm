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

    void toTurn();
    void setWidgets(QWidget* tempPlayerContents);
    void addPlayer();

signals:
    void deletedPlayer(QString);

public slots:
    void on_deletionEvent(MenuModule*);

private:
    QLinkedList<SVP>* players;
    QWidget* uiPlayerContents;

    void addPlayerView(QString s = "", double v = 0);

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // TEMPPLAYERCONTROLLER_H
