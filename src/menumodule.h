#ifndef MENUMODULE_H
#define MENUMODULE_H

#include <QFrame>
#include <QObject>

class SVP;
class QHBoxLayout;
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

//TODO: Change to QWidget

class MenuModule : public QFrame
{
    Q_OBJECT

public:
    MenuModule(QWidget* parent = 0);
    ~MenuModule();

    SVP getValue();
    void setValue(SVP);

    void setDecimals(int);

    QPushButton* getDeleteButton();

signals:
    void killMe(MenuModule* me);

public slots:
    void on_deletionEvent();

private:
    QHBoxLayout* layout;
    QDoubleSpinBox* spin;
    QLineEdit* edit;
    QPushButton* del;
};

#endif // MENUMODULE_H
