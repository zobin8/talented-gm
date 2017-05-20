#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QLinkedList>

class NPCTemplate;
class LocationTemplate;
class SVP;

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
    LocationTemplate* getLocFromName(const QString);

    void addNPCTemplate(NPCTemplate*);
    QLinkedList<NPCTemplate*> getNPCTemplates();

    void addLocTemplate(LocationTemplate*);
    QLinkedList<LocationTemplate*> getLocTemplates();

    TalentData(TalentData const&) = delete;
    void operator =(TalentData const&) = delete;

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QLinkedList<LocationTemplate*> locTemplates;
    explicit TalentData();
};

#endif // TALENTDATA_H
