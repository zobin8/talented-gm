#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class TalentData;
class QMainWindow;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject* parent = 0, QMainWindow* aUi = 0);

    void setData(TalentData*);
    virtual void draw() = 0;

signals:

public slots:

private:
    QMainWindow* ui;
    TalentData* data;
};

#endif // CONTROLLER_H
