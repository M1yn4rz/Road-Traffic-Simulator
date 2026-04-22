#include "vehicleitem.h"
#include "vehicle.h"
#include <QBrush>
#include "edge.h"
#include <QFont>

static QColor ToQtColor(VehicleColor color)
{
    switch(color)
    {
        case VehicleColor::Blue: return Qt::blue;
        case VehicleColor::Red: return Qt::red;
        case VehicleColor::Green: return Qt::green;
        case VehicleColor::Yellow: return Qt::yellow;
        default: return Qt::white;
    }
}

VehicleItem::VehicleItem(Vehicle* vehicle_)
    : vehicle(vehicle_)
    , label(new QGraphicsTextItem(QString::number(vehicle->GetId()), this))
{
    setTransformOriginPoint(0, 0);
    setRect(-60, -8, 30, 16);
    setBrush(QBrush(ToQtColor(vehicle->GetColor())));

    QFont font;
    font.setPointSize(20);
    font.setBold(true);

    label->setFont(font);
    label->setDefaultTextColor(Qt::red);
    label->setPos(-50, -20);
}

void VehicleItem::UpdatePosition()
{
    auto edge = vehicle->GetEdge();

    if (!edge)
    {
        return;
    }

    const double x = vehicle->GetX();
    const double y = vehicle->GetY();

    const double x1 = edge->GetX1();
    const double y1 = edge->GetY1();
    const double x2 = edge->GetX2();
    const double y2 = edge->GetY2();

    const double dx = x2 - x1;
    const double dy = y2 - y1;

    const double length = sqrt(dx*dx + dy*dy);

    if (length < 0.001)
    {
        return;
    }

    double offset = 10.0;

    if(!vehicle->HasPriority() &&
        edge->HasEmergency())
    {
        offset = 25.0;
    }

    const double nx = -dy / length;
    const double ny = dx / length;

    const double ox = nx * offset;
    const double oy = ny * offset;

    const double angle = atan2(dy, dx) * 180.0 / M_PI;

    setPos(x + ox, y + oy);
    setRotation(angle);
    label->setRotation(-rotation());
}
