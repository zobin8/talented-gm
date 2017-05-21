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

private:
    Ui::MainWindow* ui;
    EditorNPCController* editorNPCController;
    EditorLocController* editorLocController;

    void setControllerWidgets();
};

#endif // MAINWINDOW_H
