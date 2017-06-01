#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QLayout;
class QComboBox;
class Module;
class QLabel;

enum class ConFreq
{
    editLoc,
    editNPC,
    tempLoc,
    tempNPC,
    turnLoc,
    turnInit,
    turn,
    allButFile,
    all
};

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject* parent = 0);

    static void clearLayout(QLayout*);

    static void appendToLayout(Module*, QLayout*);
    static void appendToLayout(QLabel*, QLayout*);
    static void appendToLayout(QString, QLayout*);
    static void appendToCombo(QString, QComboBox*);

    virtual void toView() = 0;
    virtual void toModel() = 0;
    virtual void fromModel() = 0;
    virtual void fromView() = 0;

public slots:

signals:
    void updateView(ConFreq);
    void updateModel(ConFreq);
    void unsavedChange();
};

#endif // CONTROLLER_H
