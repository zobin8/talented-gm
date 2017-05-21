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

private:
    Ui::MainWindow* ui;
    QLinkedList<Controller*> controllers;

    EditorNPCController* editorNPCController;
    EditorLocController* editorLocController;
    TempLocController* tempLocController;
    TempNPCController* tempNPCController;
    TempPlayerController* tempPlayerController;

    void setControllerWidgets();
    void connectControllers();
};

#endif // MAINWINDOW_H
