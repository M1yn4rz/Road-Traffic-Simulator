#include "edge.h"

#include <algorithm>
#include "node.h"
#include "vehicle.h"

Edge::Edge(Node* from_, Node* to_)
    : occupied(false)
    , emergencyPresent(false)
    , from(from_)
    , to(to_)
    , x1(from_->GetX())
    , y1(from_->GetY())
    , x2(to_->GetX())
    , y2(to_->GetY())
{
}

Node* Edge::GetTargetNode() const
{
    return to;
}

Node* Edge::GetSourceNode() const
{
    return from;
}

double Edge::GetX1() const
{
    return x1;
}

double Edge::GetY1() const
{
    return y1;
}

double Edge::GetX2() const
{
    return x2;
}

double Edge::GetY2() const
{
    return y2;
}

bool Edge::IsOccupied() const
{
    return occupied;
}

void Edge::SetOccupied(const bool status)
{
    occupied = status;
}

void Edge::SetEmergencyPresent(bool value)
{
    emergencyPresent = value;
}

bool Edge::HasEmergency() const
{
    return emergencyPresent;
}
