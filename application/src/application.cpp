#include "application.h"

#include <QQuickWindow>

#include "gui/mainwindow.h"

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
    setApplicationName(APPLICATION_NAME);
    setApplicationVersion(BUILD_VERSION);
}

int Application::run()
{
    qInfo() << APPLICATION_NAME << "running...";
    qInfo() << "Version:" << BUILD_VERSION;
    qInfo() << "Branch:" << BUILD_BRANCH;
    qInfo() << "Commit:" << BUILD_COMMIT;

    MainWindow window;
    window.show();

    return exec();
}
