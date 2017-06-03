#include "talentdata.h"
#include "talentfile.h"
#include <QMessageBox>
#include <QTime>
#include <QCoreApplication>
#include <QRegularExpressionMatchIterator>
#include <QMutex>

TalentData::TalentData()
{
    talentFile = new TalentFile();
    fileLock = new QMutex();
}

TalentData::~TalentData()
{
    delete talentFile;
    delete fileLock;
}

TalentFile* TalentData::lockTalentFile()
{
    TalentData* inst = &TalentData::getInstance();
    inst->fileLock->lock();

    return inst->getTalentFile();
}

void TalentData::unlockTalentFile()
{
    TalentData::getInstance().fileLock->unlock();
}

TalentFile* TalentData::getTalentFile()
{
    return talentFile;
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

void TalentData::smartifyString(QString& string)
{
    int offset = 0;

    QRegularExpression re("[\\d]+");
    QRegularExpressionMatchIterator i = re.globalMatch(string);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch())
        {
            int index = match.capturedStart();
            int length = match.capturedLength();
            int count = 10 - length;
            for (int i = count; i > 0; i--)
            {
                string.insert(index + offset, "0");
                offset++;
            }
        }
    }
}

int TalentData::smartStringCompare(const QString s1, const QString s2)
{
    QString comp1 = s1;
    QString comp2 = s2;

    TalentData::smartifyString(comp1);
    TalentData::smartifyString(comp2);

    int c = QString::localeAwareCompare(comp1, comp2);
    return c;
}

QDataStream& operator <<(QDataStream& out, const TalentData& data)
{
    out << QString("TalentData1");

    out << *data.lockTalentFile();

    TalentData::unlockTalentFile();

    return out;
}

QDataStream& operator >>(QDataStream& in, TalentData& data)
{
    QString version;
    in >> version;
    int v = TalentData::versionNumber(version, "TalentData");

    if (v >= 1)
    {
        TalentFile* f = new TalentFile();
        data.setTalentFile(f);
        in >> *f;
    }

    return in;
}
