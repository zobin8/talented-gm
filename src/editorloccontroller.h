#ifndef EDITORLOCCONTROLLER_H
#define EDITORLOCCONTROLLER_H

#include "controller.h"

class LocationTemplate;
class NPCTemplate;
class QComboBox;
class QLineEdit;

class EditorLocController : public Controller
{
    Q_OBJECT
public:
    explicit EditorLocController(QObject *parent = 0);
    ~EditorLocController();

    void setWidgets(QComboBox* editLocationCombo, QLineEdit* editLocationName);

    void toView();
    void fromModel();
    void addNPC(NPCTemplate*);
    void fromView();
    void toTemplate();

signals:

public slots:
    void deleteNPC(NPCTemplate*);

private:
    LocationTemplate* locTemp;
    QComboBox* uiCombo;
    QLineEdit* uiName;

};

#endif // EDITORLOCCONTROLLER_H
