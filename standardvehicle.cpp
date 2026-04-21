#include "standardvehicle.h"
#include "node.h"
#include "edge.h"
#include <cstdlib>

StandardVehicle::StandardVehicle(Edge* start, Simulation* sim, int id)
    : Vehicle(start, sim, id)
{
}

QColor StandardVehicle::GetColor() const
{
    return Qt::blue;
}

double StandardVehicle::GetSpeed() const
{
    return 0.05;
}

bool StandardVehicle::ShouldRespectLights() const
{
    return true;
}

Edge* StandardVehicle::ChooseNextEdge(Node* currentNode)
{
    std::vector<Edge*> options;

    for(auto edge : currentNode->GetEdges())
    {
        if(edge->GetTargetNode() != previousNode && !edge->IsOccupied())
        {
            options.push_back(edge);
        }
    }

    if(options.empty())
    {
        return nullptr;
    }

    return options[rand() % options.size()];
}
