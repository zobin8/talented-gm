#ifndef MENUMODULE_H
#define MENUMODULE_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;

class MenuModule : public QWidget
{
    Q_OBJECT
public:
    explicit MenuModule(QWidget *parent = 0);
    ~MenuModule();

    void setDeleteText(QString);
    QPushButton* getDeleteButton();

    void setIdentifier(QString);
    QString getIdentifier();

signals:
    void killMe(MenuModule* me);

public slots:
    void on_deletionEvent();

protected:
    QHBoxLayout* layout;

private:
    QPushButton* del;
    QString identifier;
};

#endif // MENUMODULE_H
