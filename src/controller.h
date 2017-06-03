#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QVector>

class QLayout;
class QComboBox;
class Module;
class QLabel;
class QMutex;

enum class ConFreq
{
    editLoc,
    editNPC,
    tempLoc,
    tempNPC,
    turnLoc,
    turnInit,
    turn,
    hash,
    allButFile,
    all
};

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject* parent = 0);
    ~Controller();

    static void clearLayout(QLayout*);

    static void appendToLayout(Module*, QLayout*);
    static void appendToLayout(QLabel*, QLayout*);
    static void appendToLayout(QString, QLayout*);
    static void appendToCombo(QString, QComboBox*);

    void tryToView();
    void tryToModel();
    void tryFromView();
    void tryFromModel();

public slots:
    void on_viewUpdate();
    void on_modelUpdate();

signals:
    void updateView(ConFreq);
    void updateModel(ConFreq);

protected:
    void lockView();
    void unlockView();

    QVector<QWidget*> view;

private:
    virtual void toView() = 0;
    virtual void toModel() = 0;
    virtual void fromModel() = 0;
    virtual void fromView() = 0;

    QMutex* mutex;
};

#endif // CONTROLLER_H
