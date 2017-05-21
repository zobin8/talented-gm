#ifndef EDITORNPCCONTROLLER_H
#define EDITORNPCCONTROLLER_H

#include "controller.h"
#include <QString>

class NPCTemplate;
class SVPMenuModule;
class MenuModule;
class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

class EditorNPCController : public Controller
{
    Q_OBJECT

public:
    EditorNPCController(QObject* parent = 0);
    ~EditorNPCController();

    // RIP Code quality
    void setWidgets(QWidget* editHitScrollContents, QLineEdit* editNPCName, QSpinBox* editBodySpin, QSpinBox* editCoordSpin, QDoubleSpinBox* editSenseSpin, QSpinBox* editMindSpin, QSpinBox* editCharmSpin, QSpinBox* editCommSpin, QComboBox* editNPCCombo, QWidget* editSkillScrollContents);

    void toView();
    void fromModel();
    void addHitBox(QString s = "", double v = 0);
    void addSkill(QString s = "", double v = 0);
    void fromView();
    void toTemplate();

signals:
    void setNPCNames(QStringList);

public slots:
    void deleteHitBox(MenuModule*);
    void deleteSkill(MenuModule*);

private:
    NPCTemplate* npcTemp;
    QWidget* uiHitContents;
    QWidget* uiSkillContents;
    QLineEdit* uiName;
    QSpinBox* uiBody;
    QSpinBox* uiCoord;
    QDoubleSpinBox* uiSense;
    QSpinBox* uiMind;
    QSpinBox* uiCharm;
    QSpinBox* uiComm;
    QComboBox* uiCombo;
};

#endif // EDITORNPCCONTROLLER_H
