#ifndef TALENTFILE_H
#define TALENTFILE_H

#include <QLinkedList>
#include <QString>

class NPCTemplate;
class LocTemplate;
class SVP;
class QLayout;

class TalentFile
{
public:
    TalentFile();
    TalentFile(QString notes);
    ~TalentFile();

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

    QString getNotes() const;
    void setNotes(QString);

private:
    QLinkedList<NPCTemplate*> npcTemplates;
    QLinkedList<LocTemplate*> locTemplates;

    QLinkedList<SVP>* players;
    QString noteTemplate;

    QString generalNotes;
};


QDataStream& operator <<(QDataStream&, const TalentFile&);
QDataStream& operator >>(QDataStream&, TalentFile&);

#endif // TALENTFILE_H
