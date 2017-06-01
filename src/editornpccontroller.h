#ifndef EDITORNPCCONTROLLER_H
#define EDITORNPCCONTROLLER_H

#include "controller.h"
#include <QString>

class NPCTemplate;
class SVPMenuModule;
class SkillMenuModule;
class MenuModule;
class QLineEdit;
class QSpinBox;
class QComboBox;
class QTextEdit;

class EditorNPCController : public Controller
{
    Q_OBJECT

public:
    EditorNPCController(QObject* parent = 0);
    ~EditorNPCController();

    // RIP Code quality
    void setWidgets(QWidget* editHitScrollContents, QLineEdit* editNPCName, QSpinBox* editBodySpin, QSpinBox* editCoordSpin, QSpinBox* editSenseSpin, QSpinBox* editMindSpin, QSpinBox* editCharmSpin, QSpinBox* editCommSpin, QComboBox* editNPCCombo, QWidget* editSkillScrollContents, QTextEdit* editNPCDesc);

    void toView();
    void fromModel();
    void addSVPModule(QString s = "", double v = 0);
    void addSkillModule(QString n = "None", QString s = "", double v = 0);
    void fromView();
    void toModel();
    void toTemp();
    void toTurn();

signals:
    void setNPCNames(QStringList);

public slots:
    void deleteModule(MenuModule*);

private:
    NPCTemplate* npcTemp;
    QWidget* uiHitContents;
    QWidget* uiSkillContents;
    QLineEdit* uiName;
    QSpinBox* uiBody;
    QSpinBox* uiCoord;
    QSpinBox* uiSense;
    QSpinBox* uiMind;
    QSpinBox* uiCharm;
    QSpinBox* uiComm;
    QComboBox* uiCombo;
    QTextEdit* uiDescription;
};

#endif // EDITORNPCCONTROLLER_H
