#pragma once

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT
    Q_DISABLE_COPY(Application)

public:
    explicit Application(int& argc, char** argv);

    int run();
};
