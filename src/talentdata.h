#ifndef TALENTDATA_H
#define TALENTDATA_H

#include <QLinkedList>

class NPC;

class TalentData
{
public:
    explicit TalentData();
    ~TalentData();

    NPC* getNPCFromName(const QString);

    void addNPCTemplate(NPC*);
    QLinkedList<NPC*> getNPCTemplates();

private:
    QLinkedList<NPC*> npcTemplates;
};

#endif // TALENTDATA_H
