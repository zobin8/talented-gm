#ifndef MODULE_H
#define MODULE_H

#include <QWidget>

class QHBoxLayout;

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
    QHBoxLayout* layout;

private:
    QString sortID;
    bool sort;
};

#endif // MODULE_H
