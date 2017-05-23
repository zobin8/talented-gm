#include "talentdata.h"

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

    if (version == "TalentData1")
    {
        TalentFile* f = new TalentFile();
        in >> *f;
        data.setTalentFile(f);
    }

    return in;
}
