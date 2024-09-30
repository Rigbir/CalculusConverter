#pragma once
#include <Library.h>
#include <mobile.h>
#include <ui_mobile.h>
#include <QListWidget>

namespace Ui {
class mainWindow;
}

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
private:
    QWidget* wgt;
    QTranslator translator;
    QListWidget* list;
    QPointer<QWidget> errorMessagePointer;
    void background(QWidget* wgt);
    void resizeEvent(QResizeEvent* event);
    void onConvertButtonClicked();
    void onResetButtonClicked();
    //void changeStyle();
    void changeLanguage();
    void showErrorWithAnimation(QWidget* errorMessage);
    void hideErrorWithAnimation(QWidget* errorMessage);
    void onHideErrorFinished();
    Ui::mainWindow *ui;
    Ui::mobile* mobileUi;
};
