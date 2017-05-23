#include "talentdata.h"
#include "talentfile.h"
#include <QMessageBox>

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
