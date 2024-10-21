#pragma once
#include <Library.h>
#include <mobile.h>
#include <mobileandroid.h>
#include <ui_mobile.h>
#include <ui_mobileandroid.h>
#include <calculate.h>

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
    QWidget* calculateWindow;
    QStackedWidget* stackedWidget;
    QList<QWidget*> hiddenWidgets;
    QPointer<QWidget> errorMessagePointer;
    QTranslator translator;

    void background(QWidget* wgt);
    void resizeEvent(QResizeEvent* event);
    void resizeEventSecond(QResizeEvent* event);
    void onConvertButtonClicked();
    void onResetButtonClicked();
    void onNextButtonClicked();
    void onBackButtonClicked();
    void changeLanguage();
    void showErrorWithAnimation(QWidget* errorMessage);
    void hideErrorWithAnimation(QWidget* errorMessage);
    void onHideErrorFinished();

    void onSourceRadioButtonClicked(QAbstractButton* button);
    void onTargetRadioButtonClicked(QAbstractButton* button);

    Ui::mainWindow *ui;
    Ui::mobile* mobileUi;
    Ui::mobileAndroid* mobileAndroidUi;
};
