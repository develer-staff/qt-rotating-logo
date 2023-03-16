#pragma once

#include <QMainWindow>

#include <libcommon/applicationmodel.h>

/**
 * @brief The main application window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)
    Q_PROPERTY(common::ApplicationModel* applicationModel MEMBER applicationModel CONSTANT)

public:
    /**
     * @brief Constructor.
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget* parent = nullptr);

private:
    // The application model.
    common::ApplicationModel* applicationModel {};
};
