#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLinkedList>

namespace Ui
{
    class MainWindow;
}

class TalentData;
class NPC;
class MenuModule;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    NPC* currentEditorNPC(QString name = "Custom");
    void updateEditorNPC(QString name = "Custom");

private slots:
    void on_editNPCCombo_activated(const QString &arg1);
    void on_editNPCtoTempButton_clicked();

    void on_editAddHitButton_clicked();

private:
    Ui::MainWindow* ui;
    TalentData* data;
    QLinkedList<MenuModule*> hitBoxModules;

    QString randName();
};

#endif // MAINWINDOW_H
