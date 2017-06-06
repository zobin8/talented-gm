#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include "controller.h"
#include <QObject>

class QFile;
class QStatusBar;

enum class FileAbortResponse
{
    Cancel,
    Save,
    Okay
};

class FileController : public Controller
{
    Q_OBJECT
public:
    explicit FileController(QObject *parent = 0);
    ~FileController();

    void setWidgets(QStatusBar* statusBar);
    void setStatus();

    bool hasFile();
    void newFile();
    void openFile(QString);
    void loadFile(QFile* f = 0);
    void closeFile();
    void saveFile(QFile* f = 0);
    void exportToLog(QString);

    void loadBackup(int);

    FileAbortResponse abortClose();
    void setUnsaved(bool);

signals:
    void savedChange();

public slots:
    void on_unsavedChange(bool);
    void on_backup();

private:
    const int TOTAL_BACKUPS = 3;

    QFile* file;
    QStatusBar* uiStatusBar;
    bool unsaved;
    QMutex* fileMutex;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;

    QString getBackupPath(int);
};

#endif // FILECONTROLLER_H
