#include "calculate.h"
#include "ui_calculate.h"
#include "desktop.h"
#include "testingForInput.h"

struct UIElementsCalcul{
    QPushButton* calculateButton;
    QPushButton* backButton;
    QPushButton* resetButton;

    QComboBox* firstBox;
    QComboBox* secondBox;
    QComboBox* operatorBox;

    QLabel* errorMessage;
    QLineEdit* inputFirst;
    QLineEdit* inputSecond;
    QLineEdit* result;
};

UIElementsCalcul uiElementsCalc;

void calculate::showErrorAnimation(QWidget* errorMessage){
    QPropertyAnimation* animation = new QPropertyAnimation(errorMessage, "geometry");
    animation->setDuration(300);

    QRect startGeometry = errorMessage->geometry();
    startGeometry.setHeight(0);

    QRect endGeometry = errorMessage->geometry();
    endGeometry.setHeight(31);

    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);

    errorMessage->show();
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void calculate::hideErrorAnimation(QWidget *errorMessage){
    errorMessagePointer = errorMessage;

    QPropertyAnimation* animation = new QPropertyAnimation(errorMessage, "geometry");
    animation->setDuration(300);

    QRect startGeometry = errorMessage->geometry();
    startGeometry.setHeight(31);

    QRect endGeometry = errorMessage->geometry();
    endGeometry.setHeight(0);

    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);

    connect(animation, &QPropertyAnimation::finished, this, &calculate::hideErrorFinished);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void calculate::hideErrorFinished(){
    if (errorMessagePointer)
        errorMessagePointer->hide();
}

calculate::calculate(QStackedWidget* stackedWidget, QList<QWidget*> hiddenWidgets, QWidget *parent)
    : QWidget(parent),
    stackedWidget(stackedWidget),
    hiddenWidgets(hiddenWidgets),
    ui(new Ui::calculate)
    {

    ui->setupUi(this);
    ui->errorMessage->hide();

    uiElementsCalc.calculateButton = ui->calculateButton;
    uiElementsCalc.backButton = ui->backButton;
    uiElementsCalc.resetButton = ui->resetButton;
    uiElementsCalc.firstBox = ui->firstBox;
    uiElementsCalc.secondBox = ui->secondBox;
    uiElementsCalc.operatorBox = ui->operatorBox;
    uiElementsCalc.errorMessage = ui->errorMessage;
    uiElementsCalc.inputFirst = ui->inputFirst;
    uiElementsCalc.inputSecond = ui->inputSecond;
    uiElementsCalc.result = ui->result;

    connect(uiElementsCalc.backButton, &QPushButton::clicked, this, &calculate::onBackButtonClicked);
    connect(uiElementsCalc.calculateButton, &QPushButton::clicked, this, &calculate::onCalculateButtonClicked);
    connect(uiElementsCalc.resetButton, &QPushButton::clicked, this, &calculate::onResetButtonClicked);
}

void calculate::onBackButtonClicked(){
    stackedWidget->setCurrentIndex(0);
    for (QWidget* wgt : hiddenWidgets){
        wgt->show();
    }
}

void calculate::onResetButtonClicked(){
    uiElementsCalc.inputFirst->setText("");
    uiElementsCalc.inputSecond->setText("");
    uiElementsCalc.result->setText("");
    hideErrorAnimation(uiElementsCalc.errorMessage);
}

void calculate::onCalculateButtonClicked(){
    QString firstChoice = uiElementsCalc.firstBox->currentText();
    QString secondChoice = uiElementsCalc.secondBox->currentText();
    QString operatorChoice = uiElementsCalc.operatorBox->currentText();

    QString inputFirstText = uiElementsCalc.inputFirst->text();
    QString inputSecondText = uiElementsCalc.inputSecond->text();

    QString binary = tr("2 (binary)");
    QString octal = tr("8 (octal)");
    QString ordinary = tr("10 (ordinary)");
    QString hexadecimal = tr("16 (hexadecimal)");
    QString bcd = tr("BCD");
    QString gray = tr("Gray");

    QMap<QString, std::function<QString(QString)>> calculateMap = {
        {binary, binaryToOrdinary},
        {octal, eightToTen},
        {ordinary, [](QString input) { return input; }},
        {hexadecimal, sixteenToTen},
        {bcd, BCDtoOrdinary},
        {gray, grayToOrdinary},
    };

    QMap<QString, std::function<QString(QString)>> conversionMap = {
        {binary, toBinaryCod},
        {octal, toEight},
        {ordinary, [](QString input) { return input; }},
        {hexadecimal, toSixteen},
        {bcd, toBCD},
        {gray, toGrey}
    };

    QMap<QString, std::function<bool(QString)>> validationMap = {
        {binary, testBinaryInput},
        {octal, testEightInput},
        {ordinary, testOrdinaryInput},
        {hexadecimal, testHexadecimalInput},
        {bcd, testBCDInput},
        {gray, testBinaryInput},
    };

    uiElementsCalc.result->setText("");

    if (!validationMap[firstChoice](inputFirstText) || !validationMap[secondChoice](inputSecondText)){
        showErrorAnimation(uiElementsCalc.errorMessage);
        return;
    }else{
        hideErrorAnimation(uiElementsCalc.errorMessage);
    }

    QString firstDecimal = calculateMap[firstChoice](inputFirstText);
    QString secondDecimal = calculateMap[secondChoice](inputSecondText);

    double num1 = firstDecimal.toDouble();
    double num2 = secondDecimal.toDouble();

    double calculateResult;
    if (operatorChoice == "+"){
        calculateResult = num1 + num2;
    }else if (operatorChoice == "-"){
        calculateResult = num1 - num2;
    }else if (operatorChoice == "*"){
        calculateResult = num1 * num2;
    }else if (operatorChoice == "/"){
        if (num2 == 0){
            showErrorAnimation(uiElementsCalc.errorMessage);
            return;
        }
        calculateResult = num1 / num2;
    }

    QString finalResult = conversionMap[firstChoice](QString::number(calculateResult));
    uiElementsCalc.result->setText(finalResult);
}

calculate::~calculate(){
    delete ui;
}
