#ifndef TALENTDATA_H
#define TALENTDATA_H

#include "talentfile.h"

class TalentFile;

class TalentData
{
public:
    static TalentData& getInstance()
    {
        static TalentData instance;
        return instance;
    }
    ~TalentData();

    static TalentFile* getTalentFile();
    static void setTalentFile(TalentFile*);

    TalentData(TalentData const&) = delete;
    void operator =(TalentData const&) = delete;

private:
    explicit TalentData();

    TalentFile* talentFile;
};

QDataStream& operator <<(QDataStream&, const TalentData&);
QDataStream& operator >>(QDataStream&, TalentData&);

#endif // TALENTDATA_H
