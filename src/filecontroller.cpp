#include "filecontroller.h"
#include "talentdata.h"
#include <QFile>

FileController::FileController(QObject *parent) : Controller(parent)
{
    newFile();
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
    reloadFile();
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
    //TODO
}

void FileController::openFile(QString)
{
    //TODO
}

void FileController::reloadFile()
{
    //TODO
}

void FileController::closeFile()
{
    //TODO
}

void FileController::saveFile()
{
    //TODO
}

void FileController::exportToLog(QString)
{
    //TODO
}
