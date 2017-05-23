#include "filecontroller.h"
#include "talentdata.h"
#include "talentfile.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

FileController::FileController(QObject *parent) : Controller(parent)
{
    file = NULL;
}

FileController::~FileController()
{
    closeFile();
}

void FileController::setUnsaved(bool aBool)
{
    unsaved = aBool;
}

void FileController::toView()
{
    emit update();
}

void FileController::fromModel()
{
    if (file)
    {
        loadFile();
    }
}

void FileController::fromView()
{
    // Do nothing
}

bool FileController::hasFile()
{
    return (file);
}

void FileController::newFile()
{
    closeFile();
    TalentData::setTalentFile(new TalentFile());
    toView();
    setUnsaved(false);
}

void FileController::openFile(QString path)
{
    closeFile();
    file = new QFile(path);
}

void FileController::loadFile()
{
    if (!file->open(QIODevice::ReadOnly)) return;

    QDataStream in(file);
    in >> TalentData::getInstance();

    file->close();

    toView();
    setUnsaved(false);
}

void FileController::closeFile()
{
    if (file)
    {
        delete file;
        file = NULL;
    }
}

void FileController::saveFile()
{
    if (!file->open(QIODevice::WriteOnly)) return;

    QDataStream out(file);
    out << TalentData::getInstance();

    file->close();

    setUnsaved(false);
}

void FileController::exportToLog(QString)
{
    //TODO
}

void FileController::on_unsavedChange()
{
    setUnsaved(true);
}

bool FileController::abortClose()
{
    if (unsaved && file)
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
            saveFile();
            return false;
        case QMessageBox::Discard:
            return false;
        case QMessageBox::Cancel:
            return true;
        default:
            return true;
        }
    }
    else
    {
        return false;
    }
}
