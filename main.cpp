#include <QApplication>
#include "desktop.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef Q_OS_IOS
    mainWindow menu;
    menu.show();
#elif defined(Q_OS_ANDROID)
    mainWindow menu;
    menu.show();
#elif defined(Q_OS_MAC)
    mainWindow menu;
    menu.setFixedSize(700, 500);
    menu.show();
#endif

    return app.exec();
}
