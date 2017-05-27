#include "talentdata.h"
#include "talentfile.h"
#include <QMessageBox>
#include <QTime>
#include <QCoreApplication>

TalentData::TalentData()
{
    talentFile = new TalentFile();
}

TalentData::~TalentData()
{
    delete talentFile;
}

TalentFile* TalentData::getTalentFile()
{
    return TalentData::getInstance().talentFile;
}

void TalentData::setTalentFile(TalentFile* tf)
{
    delete TalentData::getInstance().talentFile;
    TalentData::getInstance().talentFile = tf;
}

int TalentData::versionNumber(QString version, QString prefix)
{
    if (!version.startsWith(prefix)) return -1;

    QString str(version);
    str.remove(prefix);

    return str.toInt();
}

Qt::CheckState TalentData::intToState(int i)
{
    switch(i)
    {
    case 0: return Qt::Unchecked;
    case 1: return Qt::PartiallyChecked;
    case 2: return Qt::Checked;
    default: return Qt::Unchecked;
    }
}

int TalentData::stateToInt(Qt::CheckState state)
{
    switch(state)
    {
    case Qt::Unchecked: return 0;
    case Qt::PartiallyChecked: return 1;
    case Qt::Checked: return 2;
    default: return 0;
    }
}

//Because qSleep() requires huge dependencies (QTest).
void TalentData::sleep(int ms)
{
    QTime stop = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < stop)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, ms / 10);
    }
}

QDataStream& operator <<(QDataStream& out, const TalentData& data)
{
    out << QString("TalentData1");

    out << *data.getTalentFile();

    return out;
}

QDataStream& operator >>(QDataStream& in, TalentData& data)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "TalentData");

    if (v == 1)
    {
        TalentFile* f = new TalentFile();
        data.setTalentFile(f);
        in >> *f;
    }

    return in;
}
