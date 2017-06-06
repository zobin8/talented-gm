#include "hashcontroller.h"
#include "talentdata.h"
#include <QCryptographicHash>
#include <QBuffer>
#include <QDataStream>
#include <QTimer>

HashController::HashController(QObject *parent) : Controller(parent)
{
    fileHash = QByteArray();
    currentHash = QByteArray();
    changeTimer = new QTimer();
    backupTimer = new QTimer();

    connect(changeTimer, SIGNAL(timeout()), this, SLOT(on_changeTimeout()));
    connect(backupTimer, SIGNAL(timeout()), this, SLOT(on_backupTimeout()));
}

HashController::~HashController()
{
    delete changeTimer;
    delete backupTimer;
}

QByteArray HashController::getHash()
{
    QByteArray out = QByteArray();

    QBuffer buf;
    if (!buf.open(QIODevice::WriteOnly)) return out;

    QDataStream data(&buf);
    data << TalentData::getInstance();

    buf.close();

    QCryptographicHash h(QCryptographicHash::Sha256);
    if (!buf.open(QIODevice::ReadOnly)) return out;
    h.addData(&buf);

    out = h.result();
    buf.close();
    return out;
}

void HashController::toModel()
{
    bool change = currentHash != fileHash;
    emit unsavedChange(change);

    if (change && !backupTimer->isActive())
    {
        backupTimer->start(30000);
    }
}

void HashController::fromModel()
{
    if (!changeTimer->isActive())
    {
        changeTimer->start(100);
    }
}

void HashController::toView()
{
    //Do nothing. Model only.
}

void HashController::fromView()
{
    //Do nothing. Model only.
}

void HashController::on_changeTimeout()
{
    changeTimer->stop();
    currentHash = getHash();
    toModel();
}

void HashController::on_backupTimeout()
{
    backupTimer->stop();

    //TODO: More logic here, maybe?
    emit backup();
}

void HashController::on_savedChange()
{
    fileHash = getHash();
    currentHash = getHash();
    toModel();
}
