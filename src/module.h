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

public slots:

protected:
    QGridLayout* layout;

private:
    QString sortID;
    bool sort;
};

#endif // MODULE_H
