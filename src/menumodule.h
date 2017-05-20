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

signals:
    void killMe(MenuModule* me);

public slots:
    void on_deletionEvent();

protected:
    QHBoxLayout* layout;

private:
    QPushButton* del;
};

#endif // MENUMODULE_H
