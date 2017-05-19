#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QLinkedList>

class NPCTemplate;
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

    void addNPCTemplate(NPCTemplate*);
    QLinkedList<NPCTemplate*> getNPCTemplates();

    TalentData(TalentData const&) = delete;
    void operator =(TalentData const&) = delete;

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    explicit TalentData();
};

#endif // TALENTDATA_H
