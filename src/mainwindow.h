#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>

namespace Ui
{
    class MainWindow;
}

class NPCTemplate;
class EditorNPCController;
class EditorLocController;
class TempLocController;
class TempNPCController;
class TempPlayerController;
class FileController;
class GeneralController;
class TempNotesController;
class TurnController;
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_editNPCCombo_activated(const QString &arg1);
    void on_editNPCtoTempButton_clicked();
    void on_editAddHitButton_clicked();
    void on_editLocationCombo_activated(const QString &arg1);
    void on_editAddLocTempButton_clicked();
    void on_editAddNPCButton_clicked();
    void on_editAddSkillButton_clicked();
    void on_tempAddTempButton_clicked();
    void on_tempNewPlayerButton_clicked();
    void on_actionQuit_triggered();
    void on_actionGeneral_triggered();
    void on_actionTurns_triggered();
    void on_actionTemplates_triggered();
    void on_actionEditor_triggered();
    void closeEvent(QCloseEvent*);
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExport_to_log_triggered();
    void on_actionAdd_triggered();
    void on_actionDelete_triggered();
    void on_actionPrevious_turn_triggered();
    void on_actionNext_triggered();
    void on_turnDeleteButton_clicked();
    void on_turnPrevButton_clicked();
    void on_turnNextButton_clicked();
    void on_turnAddButton_clicked();
    void on_turnLoadButton_clicked();
    void on_editAddLocTurnButton_clicked();
    void on_editNPCToTurn_clicked();

private:
    Ui::MainWindow* ui;
    QLinkedList<Controller*> controllers;

    EditorNPCController* editorNPCController;
    EditorLocController* editorLocController;
    TempLocController* tempLocController;
    TempNPCController* tempNPCController;
    TempPlayerController* tempPlayerController;
    FileController* fileController;
    GeneralController* generalController;
    TempNotesController* tempNotesController;
    TurnController* turnController;

    void setControllerWidgets();
    void connectControllers();

    QString pickFile(bool allowNew, QString filter, QString suffix);
    QString pickTGMFile(bool allowNew);
    QString pickLogFile();

    bool running;
};

#endif // MAINWINDOW_H
