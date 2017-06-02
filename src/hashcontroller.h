#ifndef HASHCONTROLLER_H
#define HASHCONTROLLER_H

#include "controller.h"
#include <QByteArray>

class QTimer;

class HashController : public Controller
{
    Q_OBJECT
public:
    explicit HashController(QObject *parent = 0);
    ~HashController();

    QByteArray getHash();

    void toView();
    void toModel();
    void fromModel();
    void fromView();

signals:
    void unsavedChange(bool);

public slots:
    void on_savedChange();
    void on_timeout();

private:
    QByteArray currentHash;
    QByteArray fileHash;
    QTimer* hashTimer;
};

#endif // HASHCONTROLLER_H
