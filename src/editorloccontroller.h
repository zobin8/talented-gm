#ifndef EDITORLOCCONTROLLER_H
#define EDITORLOCCONTROLLER_H

#include "controller.h"

class LocationTemplate;
class NPCTemplate;
class QComboBox;
class QLineEdit;
class QSpinBox;

class EditorLocController : public Controller
{
    Q_OBJECT
public:
    explicit EditorLocController(QObject *parent = 0);
    ~EditorLocController();

    void setWidgets(QComboBox* editLocationCombo, QLineEdit* editLocationName, QSpinBox* editMinionSpin1, QSpinBox* editMinionSpin2);

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
    QSpinBox* uiMinions1;
    QSpinBox* uiMinions2;
};

#endif // EDITORLOCCONTROLLER_H
