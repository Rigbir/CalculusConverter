#pragma once
#include <QWidget>

namespace Ui {
class mobile;
}

class mobile : public QWidget
{
    Q_OBJECT

public:
    explicit mobile(QWidget *parent = nullptr);
    ~mobile();

private:
    Ui::mobile *ui;
};

