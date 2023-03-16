#include "applicationmodel.h"

namespace common {

ApplicationModel::ApplicationModel(QObject* parent) : QObject(parent) { }

bool ApplicationModel::isRotating() const
{
    return rotating;
}

void ApplicationModel::setRotating(bool newValue)
{
    if (rotating == newValue)
        return;

    rotating = newValue;

    emit rotatingChanged();
}

} // namespace common
