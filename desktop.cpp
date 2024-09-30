#include <desktop.h>
#include <ui_desktop.h>
#include <testingForInput.h>

struct UIElements {
    QPushButton* convertButton;
    QPushButton* resetButton;

    QComboBox* firstBox;
    QComboBox* secondBox;
    QComboBox* languageBox;

    QLabel* errorMessage;
    QLineEdit* input;
    QLineEdit* result;
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

mainWindow::mainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::mainWindow), mobileUi(new Ui::mobile){
    wgt = new QWidget(this);
    background(wgt);

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
    mobileUi->setupUi(this);
    mobileUi->errorMessage->hide();


    QAbstractItemView *view = mobileUi->firstBox->view();
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mobileUi->firstBox->setMaxVisibleItems(2);

    uiElements.convertButton = mobileUi->convertButton;
    uiElements.resetButton = mobileUi->resetButton;
    uiElements.firstBox = mobileUi->firstBox;
    uiElements.secondBox = mobileUi->secondBox;
    uiElements.languageBox = mobileUi->languageBox;
    uiElements.errorMessage = mobileUi->errorMessage;
    uiElements.input = mobileUi->input;
    uiElements.result = mobileUi->result;
#elif defined(Q_OS_MAC)
    ui = new Ui::mainWindow;
    ui->setupUi(this);
    ui->errorMessage->hide();

    uiElements.convertButton = ui->convertButton;
    uiElements.resetButton = ui->resetButton;
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

    //connect(ui->styleBox, &QComboBox::currentIndexChanged, this, &mainWindow::changeStyle);
}

void mainWindow::changeLanguage(){
    QString language = uiElements.languageBox->currentText();

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
    mobileUi->retranslateUi(this);
#elif defined(Q_OS_MAC)
    ui->retranslateUi(this);
#endif
}

void mainWindow::onConvertButtonClicked(){
    QString firstChoice = uiElements.firstBox->currentText();
    QString secondChoice = uiElements.secondBox->currentText();
    QString inputText = uiElements.input->text();

    QString binary = tr("2 (binary)");
    QString octal = tr("8 (octal)");
    QString ordinary = tr("10 (ordinary)");
    QString hexadecimal = tr("16 (hexadecimal)");

    QMap<QString, QMap<QString, std::function<QString(QString)>>> conversionMap;

    conversionMap[binary][octal] = binaryToEight;
    conversionMap[binary][ordinary] = binaryToOrdinary;
    conversionMap[binary][hexadecimal] = binaryToSixteen;

    conversionMap[octal][binary] = eightToBinary;
    conversionMap[octal][ordinary] = eightToTen;
    conversionMap[octal][hexadecimal] = eightToSixteen;

    conversionMap[ordinary][binary] = toBinaryCod;
    conversionMap[ordinary][octal] = toEight;
    conversionMap[ordinary][hexadecimal] = toSixteen;

    conversionMap[hexadecimal][binary] = sixteenToBinary;
    conversionMap[hexadecimal][octal] = sixteenToEight;
    conversionMap[hexadecimal][ordinary] = sixteenToTen;

    QMap<QString, std::function<bool(QString)>> validationMap;
    validationMap[binary] = testBinaryInput;
    validationMap[octal] = testEightInput;
    validationMap[ordinary] = testOrdinaryInput;
    validationMap[hexadecimal] = testHexadecimalInput;

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
    QString firstInput = uiElements.input->text();
    QString secondInput = uiElements.input->text();

    firstInput = "";
    secondInput = "";

    uiElements.input->setText(firstInput);
    uiElements.result->setText(secondInput);
    hideErrorWithAnimation(uiElements.errorMessage);
}

// void mainWindow::changeStyle(){
//     QString firstStyle = qApp->styleSheet();

//     QString inputStyle = ui->styleBox->currentText();

//     QString newStyle = firstStyle;
//     if (inputStyle == "Style 2"){
//         newStyle.replace("background-color: #728495;", "background-color: #124522;");
//         qApp->setStyleSheet(newStyle);
//     }else if (inputStyle == "Style 1"){
//         newStyle = "";
//     }

// }

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
}
