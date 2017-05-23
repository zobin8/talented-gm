#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include "controller.h"
#include <QObject>

class QFile;
class QStatusBar;

class FileController : public Controller
{
    Q_OBJECT
public:
    explicit FileController(QObject *parent = 0);
    ~FileController();

    void setWidgets(QStatusBar* statusBar);
    void setStatus();

    void toView();
    void fromModel();
    void fromView();

    bool hasFile();
    void newFile();
    void openFile(QString);
    void loadFile();
    void closeFile();
    void saveFile();
    void exportToLog(QString);

    bool abortClose();
    void setUnsaved(bool);

signals:

public slots:
    void on_unsavedChange();

private:
    QFile* file;
    QStatusBar* uiStatusBar;
    bool unsaved;
};

#endif // FILECONTROLLER_H
