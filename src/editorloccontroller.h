#ifndef EDITORLOCCONTROLLER_H
#define EDITORLOCCONTROLLER_H

#include "controller.h"

class LocTemplate;
class NPCTemplate;
class QComboBox;
class QLineEdit;
class QSpinBox;
class QTextEdit;
class MenuModule;
class NPC;

class EditorLocController : public Controller
{
    Q_OBJECT
public:
    explicit EditorLocController(QObject *parent = 0);
    ~EditorLocController();

    void setWidgets(QComboBox* editLocationCombo, QLineEdit* editLocationName, QSpinBox* editMinionSpin1, QSpinBox* editMinionSpin2, QWidget* editLocContents, QComboBox* editlocNPCCombo, QTextEdit* editLocDesc);

    void addNPCModule(QString name = "");
    void toTemp();
    void toTurn();

signals:
    void viewNPC(NPC*);

public slots:
    void deleteNPC(MenuModule*);
    void on_NPCNamesChanged(QStringList);
    void on_load(QString);

private:
    LocTemplate* locTemp;
    QComboBox* uiCombo;
    QLineEdit* uiName;
    QSpinBox* uiMinions1;
    QSpinBox* uiMinions2;
    QWidget* uiNPCWidget;
    QComboBox* uiNPCCombo;
    QTextEdit* uiDescription;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // EDITORLOCCONTROLLER_H
