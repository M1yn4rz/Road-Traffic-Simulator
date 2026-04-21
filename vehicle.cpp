#include "vehicle.h"
#include "edge.h"
#include "node.h"
#include "simulation.h"
#include "trafficlight.h"

Vehicle::Vehicle(Edge* start, Simulation* sim, int vehicleId)
    : id(vehicleId)
    , posX(0)
    , posY(0)
    , progress(0)
    , previousNode(nullptr)
    , currentEdge(start)
    , simulation(sim)
{
    if(currentEdge)
    {
        currentEdge->SetOccupied(true);
    }
}

int Vehicle::GetId() const
{
    return id;
}

double Vehicle::GetX() const
{
    return posX;
}

double Vehicle::GetY() const
{
    return posY;
}

double Vehicle::GetProgress() const
{
    return progress;
}

Edge* Vehicle::GetEdge() const
{
    return currentEdge;
}

void Vehicle::UpdatePosition()
{
    double x1 = currentEdge->GetX1();
    double y1 = currentEdge->GetY1();
    double x2 = currentEdge->GetX2();
    double y2 = currentEdge->GetY2();

    posX = x1 + (x2 - x1) * progress;
    posY = y1 + (y2 - y1) * progress;
}

bool Vehicle::TrySwitchToEdge(Edge* nextEdge)
{
    if(!nextEdge)
    {
        return false;
    }

    if(nextEdge->IsOccupied() && !HasPriority())
    {
        return false;
    }

    if(HasPriority())
    {
        currentEdge->SetEmergencyPresent(false);
    }
    else
    {
        currentEdge->SetOccupied(false);
    }

    currentEdge = nextEdge;

    if(HasPriority())
    {
        currentEdge->SetEmergencyPresent(true);
    }
    else
    {
        currentEdge->SetOccupied(true);
    }

    progress = 0.0;
    return true;
}

void Vehicle::Move()
{
    progress += GetSpeed();
    UpdatePosition();

    if(progress < 1.0)
    {
        return;
    }

    Node* currentNode = currentEdge->GetTargetNode();

    if(ShouldRespectLights())
    {
        TrafficLight* light = simulation->GetLightForNode(currentNode);

        if(light)
        {
            Node* fromNode = currentEdge->GetSourceNode();
            Node* toNode   = currentEdge->GetTargetNode();

            if(!light->CanPass(fromNode, toNode))
            {
                progress = 0.99;
                UpdatePosition();
                return;
            }
        }
    }

    Edge* nextEdge = ChooseNextEdge(currentNode);

    if(nextEdge == nullptr)
    {
        progress = 1.0;
        UpdatePosition();
        return;
    }

    Node* target = nextEdge->GetTargetNode();

    if(target->HasCrosswalk() && target->IsPedestrianActive() && !HasPriority())
    {
        progress = 0.95;
        UpdatePosition();
        return;
    }

    if(!TrySwitchToEdge(nextEdge))
    {
        progress = 0.95;
        UpdatePosition();
        return;
    }

    previousNode = currentNode;
}
