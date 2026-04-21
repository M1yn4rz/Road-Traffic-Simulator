#include "trafficlight.h"

#include <cstdlib>
#include "node.h"

TrafficLight::TrafficLight(const int id_, Node* node_)
    : node(node_)
    , id(id_)
    , timer(0)
    , verticalGreen(rand() % 2)
    , emergencyLock(false)
{
}

void TrafficLight::Update()
{
    timer++;

    if (timer > 1000)
    {
        verticalGreen = !verticalGreen;
        timer = 0;
    }
}

bool TrafficLight::CanPass(Node* from, Node* to) const
{
    if(emergencyLock)
    {
        return false;
    }

    const double dx = to->GetX() - from->GetX();
    const double dy = to->GetY() - from->GetY();

    return abs(dx) > abs(dy) ? !verticalGreen : verticalGreen;
}

int TrafficLight::GetId() const
{
    return id;
}

Node* TrafficLight::GetNode() const
{
    return node;
}

std::string TrafficLight::GetState() const
{
    if(emergencyLock)
    {
        return "ALL RED";
    }

    return verticalGreen ? "NS GREEN" : "EW GREEN";
}

void TrafficLight::SetEmergencyLock(bool value)
{
    emergencyLock = value;
}

bool TrafficLight::IsEmergencyLock() const
{
    return emergencyLock;
}
