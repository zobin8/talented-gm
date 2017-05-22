#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QLinkedList>
#include <QString>

class NPCTemplate;
class LocTemplate;
class SVP;
class QLayout;

class TalentData
{
public:
    static TalentData& getInstance()
    {
        static TalentData instance;
        return instance;
    }
    ~TalentData();

    NPCTemplate* getNPCFromName(const QString);
    LocTemplate* getLocFromName(const QString);

    void addNPCTemplate(NPCTemplate*);
    QLinkedList<NPCTemplate*> getNPCTemplates();
    void setNPCTemplates(QLinkedList<NPCTemplate*>);

    void addLocTemplate(LocTemplate*);
    QLinkedList<LocTemplate*> getLocTemplates();
    void setLocTemplates(QLinkedList<LocTemplate*>);

    QLinkedList<SVP>* getPlayers();
    void setPlayers(QLinkedList<SVP>*);

    QString getNoteTemplate();
    void setNoteTemplate(QString);

    TalentData(TalentData const&) = delete;
    void operator =(TalentData const&) = delete;

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QLinkedList<LocTemplate*> locTemplates;

    QLinkedList<SVP>* players;
    QString noteTemplate;

    explicit TalentData();
};

#endif // TALENTDATA_H
