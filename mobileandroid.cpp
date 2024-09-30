#include "mobileandroid.h"
#include "ui_mobileandroid.h"

mobileAndroid::mobileAndroid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mobileAndroid)
{
    ui->setupUi(this);
}

mobileAndroid::~mobileAndroid()
{
    delete ui;
}
