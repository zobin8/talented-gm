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
    void loadFile();
    void closeFile();
    void saveFile();
    void exportToLog(QString);

    FileAbortResponse abortClose();
    void setUnsaved(bool);

signals:
    void savedChange();

public slots:
    void on_unsavedChange(bool);

private:
    QFile* file;
    QStatusBar* uiStatusBar;
    bool unsaved;

    void toView() override;
    void toModel() override;
    void fromView() override;
    void fromModel() override;
};

#endif // FILECONTROLLER_H
