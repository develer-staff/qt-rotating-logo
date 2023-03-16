#include "mainwindow.h"

#include <QQmlContext>
#include <QQuickWidget>
#include <QUrl>

namespace {

const auto MIN_WIDTH { 640 };
const auto MIN_HEIGHT { 480 };

} // namespace

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), applicationModel(new common::ApplicationModel(this))
{
    setMinimumSize(MIN_WIDTH, MIN_HEIGHT);

    auto qml = new QQuickWidget(this);
    qml->setResizeMode(QQuickWidget::SizeRootObjectToView);
    qml->rootContext()->setContextObject(this);
    qml->setSource(QUrl { "qrc:/qml/RotatingLogo.qml" });

    setCentralWidget(qml);
}
