#include "filecontroller.h"
#include "talentdata.h"
#include <QFile>
#include <QDataStream>

FileController::FileController(QObject *parent) : Controller(parent)
{
    file = NULL;
}

FileController::~FileController()
{
    closeFile();
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
}

void FileController::exportToLog(QString)
{
    //TODO
}
