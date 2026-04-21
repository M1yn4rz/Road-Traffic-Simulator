#ifndef VEHICLEITEM_H
#define VEHICLEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Vehicle;

/**
 * @brief Graphical representation of a vehicle on the map.
 *
 * Responsible for drawing the vehicle
 * and updating its screen position.
 */
class VehicleItem : public QGraphicsRectItem
{
public:

    /** @brief Creates graphical vehicle object. @param v Pointer to vehicle. */
    VehicleItem(Vehicle* v);

    /** @brief Updates vehicle position on the scene. */
    void UpdatePosition();

private:

    Vehicle* vehicle;
    QGraphicsTextItem* label;
};

#endif
