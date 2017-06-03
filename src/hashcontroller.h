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

signals:
    void unsavedChange(bool);

public slots:
    void on_savedChange();
    void on_timeout();

private:
    QByteArray currentHash;
    QByteArray fileHash;
    QTimer* hashTimer;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // HASHCONTROLLER_H
