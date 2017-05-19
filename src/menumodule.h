#ifndef MENUMODULE_H
#define MENUMODULE_H

#include <QFrame>

class SVP;
class QHBoxLayout;
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

class MenuModule : public QFrame
{
public:
    explicit MenuModule(QWidget* parent = 0);
    ~MenuModule();

    SVP getValue();
    void setValue(SVP);

private:
    QHBoxLayout* layout;
    QDoubleSpinBox* spin;
    QLineEdit* edit;
    QPushButton* del;
};

#endif // MENUMODULE_H
