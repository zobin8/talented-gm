#ifndef MENUMODULE_H
#define MENUMODULE_H

#include <QFrame>

class QHBoxLayout;
class QLineEdit;
class QLabel;
class QPushButton;
class QSpinBox;
class QDoubleSpinBox;

class MenuModule : public QFrame
{
public:
    explicit MenuModule(QWidget* parent = 0);
    ~MenuModule();

    QLineEdit* addLineEdit(QString = "");
    QLabel* addLabel(QString = "");
    QPushButton* addButton(QString = "");
    QSpinBox* addSpinBox(int = 0);
    QDoubleSpinBox* addDoubleSpinBox(double = 0);

private:
    QHBoxLayout* layout;
};

#endif // MENUMODULE_H
