#pragma once
#include <Library.h>

namespace Ui {
class calculate;
}

class calculate : public QWidget
{
    Q_OBJECT

public:
    explicit calculate(QStackedWidget* stackedWidget, QList<QWidget*> hiddenWidgets, QWidget *parent = nullptr);
    ~calculate();

private:
    QStackedWidget* stackedWidget;
    QList<QWidget*> hiddenWidgets;
    QPointer<QWidget> errorMessagePointer;

    void onCalculateButtonClicked();
    void onBackButtonClicked();
    void onResetButtonClicked();

    void showErrorAnimation(QWidget* errorMessage);
    void hideErrorAnimation(QWidget* errorMessage);
    void hideErrorFinished();

    Ui::calculate *ui;
};

