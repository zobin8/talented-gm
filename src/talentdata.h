#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QString>
#include <QDataStream>
#include <QLinkedList>

class TalentFile;
class QMutex;
class NPCTemplate;

class TalentData
{
public:
    static TalentData& getInstance()
    {
        static TalentData instance;
        return instance;
    }
    ~TalentData();

    static TalentFile* lockTalentFile();
    static void unlockTalentFile();
    static void setTalentFile(TalentFile*);
    static const TalentFile* getTalentFile();

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
    TalentFile* copyFile;
    QMutex* fileLock;
};

QDataStream& operator <<(QDataStream&, const TalentData&);
QDataStream& operator >>(QDataStream&, TalentData&);

#endif // TALENTDATA_H
