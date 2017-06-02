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
    hashTimer = new QTimer();

    connect(hashTimer, SIGNAL(timeout()), this, SLOT(on_timeout()));
}

HashController::~HashController()
{
    delete hashTimer;
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
    emit unsavedChange(currentHash != fileHash);
}

void HashController::fromModel()
{
    if (!hashTimer->isActive())
    {
        hashTimer->start(500);
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

void HashController::on_timeout()
{
    hashTimer->stop();
    currentHash = getHash();
    toModel();
}

void HashController::on_savedChange()
{
    fileHash = getHash();
    currentHash = getHash();
    toModel();
}
