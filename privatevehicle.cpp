#include "privatevehicle.h"
#include "simulation.h"

PrivateVehicle::PrivateVehicle(Edge* start, Simulation* sim, int id)
    : Vehicle(start, sim, id)
    , route()
    , routeIndex(0)
    , startTick(sim->GetTick())
    , endTick(-1)
    , startNodeId(0)
    , endNodeId(0)
{
}

void PrivateVehicle::Move()
{
    if(endTick != -1)
    {
        return;
    }

    Vehicle::Move();

    if(routeIndex >= route.size() && progress >= 1.0 && endTick == -1)
    {
        endTick = simulation->GetTick();
    }
}

void PrivateVehicle::SetRoute(const std::vector<Edge*>& newRoute)
{
    route = newRoute;
    routeIndex = 1;

    if(!route.empty())
    {
        startNodeId =
            route.front()
                ->GetSourceNode()
                ->GetId();

        endNodeId =
            route.back()
                ->GetTargetNode()
                ->GetId();
    }
}

QColor PrivateVehicle::GetColor() const
{
    return Qt::green;
}

double PrivateVehicle::GetSpeed() const
{
    return 0.05;
}

bool PrivateVehicle::ShouldRespectLights() const
{
    return true;
}

Edge* PrivateVehicle::ChooseNextEdge(Node* currentNode)
{
    if(routeIndex >= route.size())
    {
        return nullptr;
    }

    Edge* nextEdge = route[routeIndex];

    if(nextEdge->GetSourceNode() != currentNode)
    {
        return nullptr;
    }

    if(nextEdge->IsOccupied())
    {
        return nullptr;
    }

    routeIndex++;
    return nextEdge;
}

int PrivateVehicle::GetTravelTime() const
{
    if(endTick == -1)
    {
        return simulation->GetTick() - startTick;
    }

    return endTick - startTick;
}

bool PrivateVehicle::IsFinished() const
{
    return routeIndex >= route.size() && progress >= 1.0;
}

int PrivateVehicle::GetStartNodeId() const
{
    return startNodeId;
}

int PrivateVehicle::GetEndNodeId() const
{
    return endNodeId;
}
