#ifndef EDITORLOCCONTROLLER_H
#define EDITORLOCCONTROLLER_H

#include "controller.h"

class LocTemplate;
class NPCTemplate;
class QComboBox;
class QLineEdit;
class QSpinBox;
class MenuModule;

class EditorLocController : public Controller
{
    Q_OBJECT
public:
    explicit EditorLocController(QObject *parent = 0);
    ~EditorLocController();

    void setWidgets(QComboBox* editLocationCombo, QLineEdit* editLocationName, QSpinBox* editMinionSpin1, QSpinBox* editMinionSpin2, QWidget* editLocContents, QComboBox* editlocNPCCombo);

    void toView();
    void fromModel();
    void addNPCModule(QString name = "");
    void fromView();
    void toTemplate();

signals:
    void update();

public slots:
    void deleteNPC(MenuModule*);
    void on_NPCNamesChanged(QStringList);

private:
    LocTemplate* locTemp;
    QComboBox* uiCombo;
    QLineEdit* uiName;
    QSpinBox* uiMinions1;
    QSpinBox* uiMinions2;
    QWidget* uiNPCWidget;
    QComboBox* uiNPCCombo;
};

#endif // EDITORLOCCONTROLLER_H
