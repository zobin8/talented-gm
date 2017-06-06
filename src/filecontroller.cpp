#include "filecontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QStatusBar>
#include <QMutex>

FileController::FileController(QObject *parent) : Controller(parent)
{
    file = NULL;
    fileMutex = new QMutex();
}

FileController::~FileController()
{
    closeFile();
    delete fileMutex;
}

void FileController::setWidgets(QStatusBar* statusBar)
{
    uiStatusBar = statusBar;
}

void FileController::setUnsaved(bool aBool)
{
    unsaved = aBool;

    if (!unsaved)
    {
        emit savedChange();
    }

    setStatus();
}

void FileController::toView()
{
    emit updateView(ConFreq::allButFile);
    setStatus();
}

void FileController::fromModel()
{
    if (file)
    {
        loadFile();
    }
}

void FileController::toModel()
{
    if (file)
    {
        saveFile();
    }
}

void FileController::fromView()
{
    // Do nothing
}

void FileController::setStatus()
{
    QString status;

    if (file)
    {
        status = file->fileName();
    }
    else
    {
        status = "Unnamed file";
    }

    if (unsaved)
    {
        status += "*";
    }

    uiStatusBar->showMessage(status);
}

bool FileController::hasFile()
{
    return (file);
}

void FileController::newFile()
{
    closeFile();

    fileMutex->lock();

    TalentData::setTalentFile(new TalentFile());
    tryToView();
    setUnsaved(false);

    fileMutex->unlock();
}

void FileController::openFile(QString path)
{
    closeFile();
    file = new QFile(path);
}

void FileController::loadFile(QFile* f)
{
    fileMutex->lock();

    bool backup = f;
    if (!backup)
    {
        f = file;
    }

    if (!f->open(QIODevice::ReadOnly)) return;

    QDataStream in(f);
    in >> TalentData::getInstance();

    f->close();
    fileMutex->unlock();

    tryToView();

    setUnsaved(backup);
}

void FileController::closeFile()
{
    fileMutex->lock();

    if (file)
    {
        delete file;
        file = NULL;
        setStatus();
    }

    fileMutex->unlock();
}

void FileController::saveFile(QFile* f)
{
    fileMutex->lock();

    bool backup = f;
    if (!backup)
    {
        f = file;
    }

    if (!f->open(QIODevice::WriteOnly)) return;

    QDataStream out(f);
    out << TalentData::getInstance();

    f->close();
    fileMutex->unlock();

    if (!backup)
    {
        setUnsaved(false);
    }
}

void FileController::exportToLog(QString)
{
    //TODO
}

void FileController::loadBackup(int b)
{
    if (file)
    {
        QMessageBox msgBox;
        msgBox.setModal(true);
        msgBox.setText("Loading backup " + QString::number(b));
        msgBox.setInformativeText("Are you sure you want to load this backup?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes)
        {
            QFile* backup = new QFile(getBackupPath(b));
            loadFile(backup);
            delete backup;
        }
    }
}

void FileController::on_unsavedChange(bool b)
{
    if (unsaved != b)
    {
        setUnsaved(b);
    }
}

QString FileController::getBackupPath(int i)
{
    QString path = file->fileName();
    QString ext = "." + QString::number(i);
    return path + ext;
}

void FileController::on_backup()
{
    if (file)
    {
        QFile* oldestBackup = new QFile(getBackupPath(TOTAL_BACKUPS));
        oldestBackup->remove();
        delete oldestBackup;

        for (int i = TOTAL_BACKUPS - 1; i > 0; i--)
        {
            QFile* backup = new QFile(getBackupPath(i));
            backup->rename(getBackupPath(i + 1));
            delete backup;
        }

        QFile* newBackup = new QFile(getBackupPath(1));
        saveFile(newBackup);
        delete newBackup;
    }
}

FileAbortResponse FileController::abortClose()
{
    if (unsaved)
    {
        QMessageBox msgBox;
        msgBox.setModal(true);
        msgBox.setText("Unsaved changes exist.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret)
        {
        case QMessageBox::Save:
            return FileAbortResponse::Save;
        case QMessageBox::Discard:
            return FileAbortResponse::Okay;
        case QMessageBox::Cancel:
            return FileAbortResponse::Cancel;
        default:
            return FileAbortResponse::Cancel;
        }
    }
    else
    {
        return FileAbortResponse::Okay;
    }
}
