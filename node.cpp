#include "node.h"
#include "edge.h"
#include <cstdlib>

Node::Node(const int id_, const double x_, const double y_)
    : id(id_)
    , x(x_)
    , y(y_)
    , isIntersection(true)
    , outgoingEdges()
    , hasCrosswalk(false)
    , pedestrianActive(false)
    , pedestrianTicks(0)
    , pairedCrosswalk(nullptr)
{
}

void Node::AddEdge(Edge* edge)
{
    outgoingEdges.push_back(edge);
}

void Node::SetIsIntersection(const bool status)
{
    isIntersection = status;
}

const std::vector<Edge*>& Node::GetEdges() const
{
    return outgoingEdges;
}

bool Node::GetIsIntersection() const
{
    return isIntersection;
}

double Node::GetX() const
{
    return x;
}

double Node::GetY() const
{
    return y;
}

int Node::GetId() const
{
    return id;
}

void Node::UpdateCrosswalk()
{
    if(!hasCrosswalk)
        return;

    if(pedestrianActive)
    {
        pedestrianTicks--;

        if(pedestrianTicks <= 0)
        {
            pedestrianActive = false;

            if(pairedCrosswalk)
                pairedCrosswalk->pedestrianActive = false;
        }
    }
    else
    {
        if(rand() % 200 == 0)
        {
            pedestrianActive = true;
            pedestrianTicks = 100;

            if(pairedCrosswalk)
            {
                pairedCrosswalk->pedestrianActive = true;
                pairedCrosswalk->pedestrianTicks = 100;
            }
        }
    }
}

void Node::SetCrosswalk(bool value)
{
    hasCrosswalk = value;
}

bool Node::HasCrosswalk() const
{
    return hasCrosswalk;
}

bool Node::IsPedestrianActive() const
{
    return pedestrianActive;
}

void Node::ActivatePedestrian()
{
    if(!hasCrosswalk)
        return;

    pedestrianActive = true;
    pedestrianTicks = 100;
}

void Node::SetPairedCrosswalk(Node* node)
{
    pairedCrosswalk = node;
}

Node* Node::GetPairedCrosswalk() const
{
    return pairedCrosswalk;
}
