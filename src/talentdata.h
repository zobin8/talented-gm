#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QString>
#include <QDataStream>

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

    static Qt::CheckState intToState(int);
    static int stateToInt(Qt::CheckState);

    static int smartStringCompare(const QString, const QString);
    static void smartifyString(QString&);

    static int versionNumber(QString version, QString prefix);

    TalentData(TalentData const&) = delete;
    void operator =(TalentData const&) = delete;

private:
    explicit TalentData();

    TalentFile* talentFile;
};

QDataStream& operator <<(QDataStream&, const TalentData&);
QDataStream& operator >>(QDataStream&, TalentData&);

#endif // TALENTDATA_H
