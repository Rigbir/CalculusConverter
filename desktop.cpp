#include "desktop.h"
#include "ui_desktop.h"
#include "testingForInput.h"

struct UIElements {
    QPushButton* convertButton;
    QPushButton* resetButton;
    QPushButton* nextButton;

    QComboBox* firstBox;
    QComboBox* secondBox;
    QComboBox* languageBox;

    QLabel* errorMessage;
    QLineEdit* input;
    QLineEdit* result;

    QRadioButton* radioButton_1;
    QRadioButton* radioButton_2;
    QRadioButton* radioButton_3;
    QRadioButton* radioButton_4;
    QRadioButton* radioButton_5;
    QRadioButton* radioButton_6;
    QRadioButton* radioButton_7;
    QRadioButton* radioButton_8;
    QRadioButton* radioButton_En;
    QRadioButton* radioButton_Ru;
};

UIElements uiElements;

void mainWindow::showErrorWithAnimation(QWidget *errorMessage) {
    QPropertyAnimation *animation = new QPropertyAnimation(errorMessage, "geometry");
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

void mainWindow::hideErrorWithAnimation(QWidget *errorMessage){
    errorMessagePointer = errorMessage;

    QPropertyAnimation* animation = new QPropertyAnimation(errorMessage, "geometry");
    animation->setDuration(300);

    QRect startGeometry = errorMessage->geometry();
    startGeometry.setHeight(31);
    QRect endGeometry = errorMessage->geometry();
    endGeometry.setHeight(0);

    animation->setStartValue(startGeometry);
    animation->setEndValue(endGeometry);

    connect(animation, &QPropertyAnimation::finished, this, &mainWindow::onHideErrorFinished);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void mainWindow::onHideErrorFinished(){
    if (errorMessagePointer)
        errorMessagePointer->hide();
}

QButtonGroup* firstPartButton;
QButtonGroup* secondPartButton;
QButtonGroup* languagePartButton;

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent),
    stackedWidget(new QStackedWidget(this)),
    ui(new Ui::mainWindow),
    mobileUi(new Ui::mobile),
    mobileAndroidUi(new Ui::mobileAndroid){

    wgt = new QWidget(this);
    background(wgt);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stackedWidget);

    stackedWidget->addWidget(wgt);
    stackedWidget->setCurrentWidget(wgt);

#ifdef Q_OS_IOS
    mobileUi->setupUi(this);
    mobileUi->errorMessage->hide();

    uiElements.convertButton = mobileUi->convertButton;
    uiElements.resetButton = mobileUi->resetButton;
    uiElements.firstBox = mobileUi->firstBox;
    uiElements.secondBox = mobileUi->secondBox;
    uiElements.languageBox = mobileUi->languageBox;
    uiElements.errorMessage = mobileUi->errorMessage;
    uiElements.input = mobileUi->input;
    uiElements.result = mobileUi->result;
#elif defined(Q_OS_ANDROID)
    mobileAndroidUi->setupUi(this);
    mobileAndroidUi->errorMessage->hide();

    uiElements.convertButton = mobileAndroidUi->convertButton;
    uiElements.resetButton = mobileAndroidUi->resetButton;

    firstPartButton = new QButtonGroup(this);
    firstPartButton->addButton(mobileAndroidUi->radioButton_1);
    firstPartButton->addButton(mobileAndroidUi->radioButton_2);
    firstPartButton->addButton(mobileAndroidUi->radioButton_3);
    firstPartButton->addButton(mobileAndroidUi->radioButton_4);

    secondPartButton = new QButtonGroup(this);
    secondPartButton->addButton(mobileAndroidUi->radioButton_5);
    secondPartButton->addButton(mobileAndroidUi->radioButton_6);
    secondPartButton->addButton(mobileAndroidUi->radioButton_7);
    secondPartButton->addButton(mobileAndroidUi->radioButton_8);

    languagePartButton = new QButtonGroup(this);
    languagePartButton->addButton(mobileAndroidUi->radioButton_En);
    languagePartButton->addButton(mobileAndroidUi->radioButton_Ru);

    uiElements.errorMessage = mobileAndroidUi->errorMessage;
    uiElements.input = mobileAndroidUi->input;
    uiElements.result = mobileAndroidUi->result;

    connect(languagePartButton, &QButtonGroup::buttonClicked, this, &mainWindow::changeLanguage);
#elif defined(Q_OS_MAC)
    ui = new Ui::mainWindow;
    ui->setupUi(this);
    ui->errorMessage->hide();

    uiElements.convertButton = ui->convertButton;
    uiElements.resetButton = ui->resetButton;
    uiElements.nextButton = ui->nextButton;
    uiElements.firstBox = ui->firstBox;
    uiElements.secondBox = ui->secondBox;
    uiElements.languageBox = ui->languageBox;
    uiElements.errorMessage = ui->errorMessage;
    uiElements.input = ui->input;
    uiElements.result = ui->result;
#endif

    connect(uiElements.convertButton, &QPushButton::clicked, this, &mainWindow::onConvertButtonClicked);
    connect(uiElements.resetButton, &QPushButton::clicked, this, &mainWindow::onResetButtonClicked);
    connect(uiElements.languageBox, &QComboBox::currentIndexChanged, this, &mainWindow::changeLanguage);
    connect(uiElements.nextButton, &QPushButton::clicked, this, &mainWindow::onNextButtonClicked);
}

void mainWindow::changeLanguage(){
    QString language;

#ifdef Q_OS_ANDROID
    if (languagePartButton->checkedButton() == mobileAndroidUi->radioButton_Ru) {
        language = "Русский";
    } else {
        language = "English";
    }
#else
    language = uiElements.languageBox->currentText();
#endif

    if(language == "Русский"){
        if (!translator.load(":/translations/CalculusSystem_ru_RU.qm"))
            qDebug() << "Error loading translate";
        qApp->installTranslator(&translator);
    }else{
        qApp->removeTranslator(&translator);
    }

#ifdef Q_OS_IOS
    mobileUi->retranslateUi(this);
#elif defined(Q_OS_ANDROID)
    mobileAndroidUi->retranslateUi(this);
#elif defined(Q_OS_MAC)
    ui->retranslateUi(this);
#endif
}

void mainWindow::onConvertButtonClicked(){
    QString firstChoice;
    QString secondChoice;

    QString binary = tr("2 (binary)");
    QString octal = tr("8 (octal)");
    QString ordinary = tr("10 (ordinary)");
    QString hexadecimal = tr("16 (hexadecimal)");
    QString bcd = tr("BCD");
    QString gray = tr("Gray");

#ifdef Q_OS_ANDROID
    if (firstPartButton->checkedButton() == mobileAndroidUi->radioButton_1)
        firstChoice = binary;
    else if (firstPartButton->checkedButton() == mobileAndroidUi->radioButton_2)
        firstChoice = octal;
    else if (firstPartButton->checkedButton() == mobileAndroidUi->radioButton_3)
        firstChoice = ordinary;
    else if (firstPartButton->checkedButton() == mobileAndroidUi->radioButton_4)
        firstChoice = hexadecimal;

    if (secondPartButton->checkedButton() == mobileAndroidUi->radioButton_5)
        secondChoice = binary;
    else if (secondPartButton->checkedButton() == mobileAndroidUi->radioButton_6)
        secondChoice = octal;
    else if (secondPartButton->checkedButton() == mobileAndroidUi->radioButton_7)
        secondChoice = ordinary;
    else if (secondPartButton->checkedButton() == mobileAndroidUi->radioButton_8)
        secondChoice = hexadecimal;
#else
    firstChoice = uiElements.firstBox->currentText();
    secondChoice = uiElements.secondBox->currentText();
#endif
    QString inputText = uiElements.input->text();

    QMap<QString, QMap<QString, std::function<QString(QString)>>> conversionMap;

    //2
    conversionMap[binary][octal] = binaryToEight;
    conversionMap[binary][ordinary] = binaryToOrdinary;
    conversionMap[binary][hexadecimal] = binaryToSixteen;
    conversionMap[binary][bcd] = binaryToBCD;
    conversionMap[binary][gray] = binaryToGrey;

    //8
    conversionMap[octal][binary] = eightToBinary;
    conversionMap[octal][ordinary] = eightToTen;
    conversionMap[octal][hexadecimal] = eightToSixteen;
    conversionMap[octal][bcd] = eightToBCD;
    conversionMap[octal][gray] = eightToGrey;

    //10
    conversionMap[ordinary][binary] = toBinaryCod;
    conversionMap[ordinary][octal] = toEight;
    conversionMap[ordinary][hexadecimal] = toSixteen;
    conversionMap[ordinary][bcd] = toBCD;
    conversionMap[ordinary][gray] = toGrey;

    //16
    conversionMap[hexadecimal][binary] = sixteenToBinary;
    conversionMap[hexadecimal][octal] = sixteenToEight;
    conversionMap[hexadecimal][ordinary] = sixteenToTen;
    conversionMap[hexadecimal][bcd] = sixteenToBCD;
    conversionMap[hexadecimal][gray] = sixteenToGrey;

    //BCD
    conversionMap[bcd][ordinary] = BCDtoOrdinary;
    conversionMap[bcd][binary] = BCDtoBinary;
    conversionMap[bcd][octal] = BCDtoOctal;
    conversionMap[bcd][hexadecimal] = BCDtoHexadecimal;
    conversionMap[bcd][gray] = BCDtoGrey;

    //Grey
    conversionMap[gray][binary] = grayToBinary;
    conversionMap[gray][octal] = grayToOctal;
    conversionMap[gray][ordinary] = grayToOrdinary;
    conversionMap[gray][hexadecimal] = grayToSixteen;
    conversionMap[gray][bcd] = grayToBCD;

    QMap<QString, std::function<bool(QString)>> validationMap;
    validationMap[binary] = testBinaryInput;
    validationMap[octal] = testEightInput;
    validationMap[ordinary] = testOrdinaryInput;
    validationMap[hexadecimal] = testHexadecimalInput;
    validationMap[bcd] = testBCDInput;
    validationMap[gray] = testBinaryInput;

    uiElements.result->setText("");

    if (!validationMap[firstChoice](inputText)) {
        showErrorWithAnimation(uiElements.errorMessage);
        return;
    } else {
        hideErrorWithAnimation(uiElements.errorMessage);
    }

    if (conversionMap.contains(firstChoice) && conversionMap[firstChoice].contains(secondChoice)) {
        QString result = conversionMap[firstChoice][secondChoice](inputText);
        uiElements.result->setText(result);
    }
}

void mainWindow::onResetButtonClicked(){
    uiElements.input->setText("");
    uiElements.result->setText("");
    hideErrorWithAnimation(uiElements.errorMessage);
}

void mainWindow::onNextButtonClicked(){

    hiddenWidgets.clear();
    QList<QWidget*> widgetToHide = {
        uiElements.convertButton,
        uiElements.resetButton,
        uiElements.nextButton,
        uiElements.firstBox,
        uiElements.secondBox,
        uiElements.languageBox,
        uiElements.input,
        uiElements.result,
        ui->label,
        ui->label_2
    };

    uiElements.errorMessage->hide();

    for (QWidget* wgt : widgetToHide){
        wgt->hide();
        hiddenWidgets.append(wgt);
    }

    calculateWindow = new calculate(stackedWidget, hiddenWidgets, this);
    background(calculateWindow);

    stackedWidget->addWidget(calculateWindow);

    stackedWidget->setCurrentWidget(calculateWindow);
}

void mainWindow::background(QWidget* wgt){
    QPalette palette;
    palette.setColor(wgt->backgroundRole(), QColor(0x8E99AF));
    wgt->setAutoFillBackground(true);
    wgt->setPalette(palette);
}

void mainWindow::resizeEvent(QResizeEvent *event){
    wgt->resize(this->size());
    QWidget::resizeEvent(event);
}

mainWindow::~mainWindow(){
    delete ui;
    delete mobileUi;
    delete mobileAndroidUi;
}
