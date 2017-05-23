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
    void on_tempAddLocationButton_clicked();
    void on_tempAddNPCButton_clicked();
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

    void setControllerWidgets();
    void connectControllers();

    QString pickFile(bool allowNew);

    bool running;
};

#endif // MAINWINDOW_H
