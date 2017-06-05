#ifndef TALENTFILE_H
#define TALENTFILE_H

#include <QLinkedList>
#include <QList>
#include <QString>

class NPCTemplate;
class LocTemplate;
class SVP;
class QLayout;
class Turn;

class TalentFile
{
public:
    TalentFile();
    TalentFile(const TalentFile&);
    ~TalentFile();

    const NPCTemplate* constNPCFromName(const QString) const;
    NPCTemplate* getNPCFromName(const QString);
    LocTemplate* getLocFromName(const QString);

    void addNPCTemplate(NPCTemplate*);
    QLinkedList<NPCTemplate*> getNPCTemplates() const;
    void setNPCTemplates(QLinkedList<NPCTemplate*>);

    void addLocTemplate(LocTemplate*);
    QLinkedList<LocTemplate*> getLocTemplates() const;
    void setLocTemplates(QLinkedList<LocTemplate*>);

    void setCurrentNPC(const NPCTemplate*);
    void setCurrentLoc(const LocTemplate*);
    const NPCTemplate* getCurrentNPC() const;
    const LocTemplate* getCurrentLoc() const;

    QLinkedList<SVP>* getPlayers() const;
    void setPlayers(QLinkedList<SVP>*);

    QString getNoteTemplate() const;
    void setNoteTemplate(QString);

    QString getNotes() const;
    void setNotes(QString);

    Turn* currentTurn();
    Turn* lastTurn();
    const QList<Turn*> getTurns() const;
    void setTurns(QList<Turn*>);

    void resetInitiative();

    int currentTurnIndex() const;
    void updateTurnIndex();
    void previousTurn();
    void nextTurn();
    void addTurn();
    void deleteTurn();

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QLinkedList<LocTemplate*> locTemplates;

    QLinkedList<SVP>* players;
    QString noteTemplate;

    NPCTemplate* currentNPC;
    LocTemplate* currentLoc;

    QString generalNotes;

    QList<Turn*> turns;
    int turnIndex;
};


QDataStream& operator <<(QDataStream&, const TalentFile&);
QDataStream& operator >>(QDataStream&, TalentFile&);

#endif // TALENTFILE_H
