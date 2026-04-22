#include "emergencyvehicle.h"

EmergencyVehicle::EmergencyVehicle(Edge* start, Simulation* sim, int id)
    : Vehicle(start, sim, id)
    , route()
    , routeIndex(0)
{
}

void EmergencyVehicle::Move()
{
    Vehicle::Move();
}

void EmergencyVehicle::SetRoute(const std::vector<Edge*>& newRoute)
{
    route = newRoute;
    routeIndex = 1;
}

VehicleColor EmergencyVehicle::GetColor() const
{
    return VehicleColor::Red;
}

double EmergencyVehicle::GetSpeed() const
{
    return 0.08;
}

bool EmergencyVehicle::ShouldRespectLights() const
{
    return false;
}

bool EmergencyVehicle::HasPriority() const
{
    return true;
}

Edge* EmergencyVehicle::ChooseNextEdge(Node*)
{
    if(routeIndex >= route.size())
    {
        return nullptr;
    }

    return route[routeIndex++];
}

bool EmergencyVehicle::IsFinished() const
{
    return routeIndex >= route.size() && progress >= 1.0;
}
