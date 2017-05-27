#include "menumodule.h"
#include "talentdata.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>

MenuModule::MenuModule(QWidget *parent) : Module(parent)
{
    del = new QPushButton("Delete");

    confirmationNeeded = false;
    confirmationTimer = new QTimer();
    connect(confirmationTimer, SIGNAL(timeout()), this, SLOT(on_confirmationTimeout()));

    del->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    layout->setContentsMargins(0, 0, 0, 0);

    connect(del, SIGNAL(clicked()), this, SLOT(on_deletionEvent()));
}

void MenuModule::addWidgets()
{
    layout->addWidget(del);
}

MenuModule::~MenuModule()
{
    delete del;
    delete confirmationTimer;
}

void MenuModule::requireConfirmation(bool con)
{
    confirmationNeeded = con;
}

void MenuModule::setDeleteText(QString text)
{
    del->setText(text);
}

QString MenuModule::getDeleteText()
{
    return del->text();
}

QPushButton* MenuModule::getDeleteButton()
{
    return del;
}

void MenuModule::on_deletionEvent()
{
    if (confirmationNeeded)
    {
        if (confirmationTimer->isActive())
        {
            confirmationTimer->stop();
            emit killMe(this);
        }
        else
        {
            deleteText = del->text();
            del->setText("Are you sure?");

            confirmationTimer->start(3000);
        }
    }
    else
    {
        emit killMe(this);
    }
}

void MenuModule::on_confirmationTimeout()
{
    del->setText(deleteText);
    confirmationTimer->stop();
}

void MenuModule::setIdentifier(QString i)
{
    identifier = i;
}

QString MenuModule::getIdentifier()
{
    return identifier;
}
