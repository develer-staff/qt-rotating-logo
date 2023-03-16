#pragma once

#include <QObject>

namespace common {

/**
 * @brief The application model object.
 */
class ApplicationModel : public QObject
{
    Q_DISABLE_COPY(ApplicationModel)
    Q_OBJECT
    Q_PROPERTY(bool rotating READ isRotating WRITE setRotating NOTIFY rotatingChanged)

public:
    /**
     * @brief Constructor.
     * @param parent The parent object.
     */
    explicit ApplicationModel(QObject* parent = nullptr);

    /**
     * @brief Get the rotating property.
     * @return The rotating property value.
     */
    bool isRotating() const;

    /**
     * @brief Set the rotating property.
     * @param newValue The new rotating property value.
     */
    void setRotating(bool newValue);

signals:
    /**
     * @brief Signal emitted when the rotating property changes.
     */
    void rotatingChanged();

private:
    // True if the logo is rotating, false otherwise.
    bool rotating {};
};

} // namespace common
