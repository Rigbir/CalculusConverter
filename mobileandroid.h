#ifndef MOBILEANDROID_H
#define MOBILEANDROID_H

#include <QWidget>

namespace Ui {
class mobileAndroid;
}

class mobileAndroid : public QWidget
{
    Q_OBJECT

public:
    explicit mobileAndroid(QWidget *parent = nullptr);
    ~mobileAndroid();

private:
    Ui::mobileAndroid *ui;
};

#endif // MOBILEANDROID_H
