#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>

namespace Ui
{
    class MainWindow;
}

class NPCTemplate;
class MainController;

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
    void on_tempToTurnButton_clicked();
    void on_actionNext_Tab_triggered();
    void on_actionPrevious_Tab_triggered();
    void on_actionLoad_1_triggered();
    void on_actionLoad_2_triggered();
    void on_actionLoad_3_triggered();

private:
    Ui::MainWindow* ui;
    bool running;
    MainController* mc;

    void setControllerWidgets();

    bool fileOkay(QString path, bool allowNew);
    QString pickFile(bool allowNew, QString filter, QString suffix);
    QString pickTGMFile(bool allowNew);
    QString pickLogFile();

    const QString TGM_VERSION = "v0.8.3";
};

#endif // MAINWINDOW_H
