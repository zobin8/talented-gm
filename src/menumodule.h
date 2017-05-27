#ifndef MENUMODULE_H
#define MENUMODULE_H

#include "module.h"

class QPushButton;

class MenuModule : public Module
{
    Q_OBJECT
public:
    explicit MenuModule(QWidget *parent = 0);
    ~MenuModule();

    void addWidgets();
    void requireConfirmation(bool con = true);

    void setDeleteText(QString);
    QString getDeleteText();

    QPushButton* getDeleteButton();

    void setIdentifier(QString);
    QString getIdentifier();

signals:
    void killMe(MenuModule* me);

public slots:
    void on_deletionEvent();
    void on_confirmationTimeout();

protected:
    QPushButton* del;
    QString deleteText;

    bool confirmationNeeded;
    QTimer* confirmationTimer;

private:
    QString identifier;
};

#endif // MENUMODULE_H
