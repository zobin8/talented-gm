#ifndef MODULE_H
#define MODULE_H

#include <QWidget>

class QGridLayout;

class Module : public QWidget
{
    Q_OBJECT
public:
    explicit Module(QWidget *parent = 0);
    ~Module();

    void setSortID(QString);
    QString getSortID();
    bool needsSort();

signals:
    void viewUpdate();

public slots:
    void on_update();

protected:
    QGridLayout* layout;

private:
    QString sortID;
    bool sort;
};

#endif // MODULE_H
