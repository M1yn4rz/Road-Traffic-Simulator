#include "simulation.h"

#include <stdlib.h>
#include "node.h"
#include "edge.h"
#include "graph.h"
#include "vehicle.h"
#include "trafficlight.h"
#include "standardvehicle.h"
#include "emergencyvehicle.h"
#include "privatevehicle.h"
#include "idgenerator.h"

Simulation::Simulation()
    : lights()
    , events()
    , vehicles()
    , graph(nullptr)
    , nextVehicleId(1)
    , currentTick(0)
    , emergencySpawnInterval(0)
    , messages()
{
    CreateMap();
}

Simulation::~Simulation()
{
    for (auto v : vehicles)
    {
        delete v;
    }

    for (auto l : lights)
    {
        delete l;
    }

    delete graph;
}

void Simulation::Tick()
{
    currentTick++;

    for(auto node : graph->GetNodes())
    {
        node->UpdateCrosswalk();
    }

    if(emergencySpawnInterval > 0)
    {
        if(currentTick % emergencySpawnInterval == 0)
        {
            SpawnEmergencyVehicle();
        }
    }

    for(auto light : lights)
    {
        light->SetEmergencyLock(false);
    }

    for(auto v : vehicles)
    {
        auto* ev = dynamic_cast<EmergencyVehicle*>(v);

        if(!ev)
        {
            continue;
        }

        Node* target = ev->GetEdge()->GetTargetNode();

        TrafficLight* light = GetLightForNode(target);

        if(light)
        {
            light->SetEmergencyLock(true);
        }
    }

    for(auto light : lights)
    {
        light->Update();
    }

    for(int i = (int)vehicles.size() - 1; i >= 0; i--)
    {
        vehicles[i]->Move();
    }

    RemoveFinishedVehicles();

    for(size_t i = 0; i < vehicles.size(); i++)
    {
        for(size_t j = i + 1; j < vehicles.size(); j++)
        {
            auto v1 = vehicles[i];
            auto v2 = vehicles[j];

            if(v1->GetProgress() >= 0.95 && v2->GetProgress() >= 0.95)
            {
                Node* n1 = v1->GetEdge()->GetTargetNode();

                Node* n2 = v2->GetEdge()->GetTargetNode();

                if(n1 == n2)
                {
                    TrafficLight* light = GetLightForNode(n1);

                    if(!light)
                    {
                        continue;
                    }

                    Node* v1_from = v1->GetEdge()->GetSourceNode();
                    Node* v1_to = v1->GetEdge()->GetTargetNode();
                    Node* v2_from = v2->GetEdge()->GetSourceNode();
                    Node* v2_to = v2->GetEdge()->GetTargetNode();

                    bool v1_can = light->CanPass(v1_from, v1_to);
                    bool v2_can = light->CanPass(v2_from, v2_to);

                    if(v1_can && v2_can)
                    {
                        events.push_back({
                            currentTick,
                            light->GetId(),
                            v1->GetId(),
                            v2->GetId()
                        });
                    }
                }
            }
        }
    }
}

void Simulation::AddVehicles(const int numberVehicles)
{
    auto edges = graph->GetEdges();

    for(int i=0;i<numberVehicles;i++)
    {
        Edge* start = edges[rand()%edges.size()];
        vehicles.push_back(new StandardVehicle(start,this,IdGenerator<Vehicle>::Next()));
    }
}

void Simulation::CreateMap()
{
    graph = new Graph();

    std::vector<std::vector<Node*>> grid;

    std::vector<int> xs = {300, 900, 1500, 2100};
    std::vector<int> ys = {150, 350, 550};

    int id = 1;

    for (int y : ys)
    {
        std::vector<Node*> row;

        for (int x : xs)
        {
            row.push_back(graph->AddNode(id++, x, y));
        }

        grid.push_back(row);
    }

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size() - 1; j++)
        {
            graph->AddRoad(grid[i][j], grid[i][j+1]);
            graph->AddRoad(grid[i][j+1], grid[i][j]);
        }
    }

    for (int j = 0; j < grid[0].size(); j++)
    {
        for (int i = 0; i < grid.size() - 1; i++)
        {
            graph->AddRoad(grid[i][j], grid[i+1][j]);
            graph->AddRoad(grid[i+1][j], grid[i][j]);
        }
    }

    for (auto node : graph->GetNodes())
    {
        if (node->GetIsIntersection())
        {
            lights.push_back(new TrafficLight(IdGenerator<TrafficLight>::Next(), node));
        }
    }

    std::vector<int> seedIds =
        {
            125, 150, 180, 213,
            238, 270
        };

    std::vector<std::pair<double,double>> points;

    for(auto node : graph->GetNodes())
    {
        for(int id : seedIds)
        {
            if(node->GetId() == id)
            {
                points.push_back(
                    {
                        node->GetX(),
                        node->GetY()
                    });
            }
        }
    }

    for(auto node : graph->GetNodes())
    {
        for(auto& p : points)
        {
            if(std::abs(node->GetX() - p.first)  < 0.1 && std::abs(node->GetY() - p.second) < 0.1)
            {
                node->SetCrosswalk(true);
            }
        }
    }

    for(auto a : graph->GetNodes())
    {
        if(!a->HasCrosswalk())
        {
            continue;
        }

        for(auto b : graph->GetNodes())
        {
            if(a == b)
            {
                continue;
            }

            if(!b->HasCrosswalk())
            {
                continue;
            }

            if(std::abs(a->GetX() - b->GetX()) < 0.1 && std::abs(a->GetY() - b->GetY()) < 0.1)
            {
                a->SetPairedCrosswalk(b);
            }
        }
    }
}

int Simulation::GetTick() const
{
    return currentTick;
}

Graph* Simulation::GetGraph() const
{
    return graph;
}

TrafficLight* Simulation::GetLightForNode(Node* node)
{
    for (const auto& l : lights)
    {
        if (l->GetNode() == node)
        {
            return l;
        }
    }

    return nullptr;
}

const std::vector<Vehicle*>& Simulation::GetVehicles() const
{
    return vehicles;
}

const std::vector<TrafficEvent>& Simulation::GetEvents() const
{
    return events;
}

const std::vector<TrafficLight*>& Simulation::GetLights() const
{
    return lights;
}

void Simulation::AddPrivateVehicle(Node* start, Node* end)
{
    auto route = graph->FindShortestPath(start,end);

    if(route.empty())
    {
        return;
    }

    auto* v = new PrivateVehicle(route[0], this, IdGenerator<Vehicle>::Next());
    v->SetRoute(route);
    vehicles.push_back(v);
}

void Simulation::SpawnEmergencyVehicle()
{
    std::vector<Node*> intersections;

    for(auto node : graph->GetNodes())
    {
        if(node->GetIsIntersection())
        {
            intersections.push_back(node);
        }
    }

    if(intersections.size() < 2)
    {
        return;
    }

    Node* start = intersections[rand() % intersections.size()];
    Node* end = intersections[rand() % intersections.size()];

    while(end == start)
    {
        end = intersections[rand() % intersections.size()];
    }

    std::vector<Edge*> route = graph->FindShortestPath(start, end);

    if(route.empty())
    {
        return;
    }

    auto* vehicle = new EmergencyVehicle(route[0], this, IdGenerator<Vehicle>::Next());
    vehicle->SetRoute(route);
    vehicles.push_back(vehicle);
}

void Simulation::RemoveFinishedVehicles()
{
    for(int i = (int)vehicles.size() - 1; i >= 0; i--)
    {
        bool remove = false;

        if(auto* ev = dynamic_cast<EmergencyVehicle*>(vehicles[i]))
        {
            remove = ev->IsFinished();
        }

        if(auto* pv = dynamic_cast<PrivateVehicle*>(vehicles[i]))
        {
            if(pv->IsFinished())
            {
                events.push_back({
                    currentTick,
                    -2,
                    pv->GetStartNodeId(),
                    pv->GetEndNodeId()
                });

                messages.push_back(
                    "[TICK " +
                    std::to_string(currentTick) +
                    "] Private Vehicle " +
                    std::to_string(pv->GetId()) +
                    " route " +
                    std::to_string(pv->GetStartNodeId()) +
                    " -> " +
                    std::to_string(pv->GetEndNodeId()) +
                    " finished in " +
                    std::to_string(pv->GetTravelTime()) +
                    " ticks");

                remove = true;
            }
        }

        if(remove)
        {
            Edge* edge = vehicles[i]->GetEdge();

            if(edge)
            {
                edge->SetOccupied(false);
                edge->SetEmergencyPresent(false);
            }

            delete vehicles[i];

            vehicles.erase(vehicles.begin() + i);
        }
    }
}

void Simulation::SetEmergencySpawnInterval(int value)
{
    emergencySpawnInterval = value;
}

void Simulation::SpawnPrivateVehicle(int fromId, int toId)
{
    if(fromId == toId)
    {
        return;
    }

    Node* start = nullptr;
    Node* goal  = nullptr;

    for(auto node : graph->GetNodes())
    {
        if(node->GetId() == fromId)
        {
            start = node;
        }

        if(node->GetId() == toId)
        {
            goal = node;
        }
    }

    if(!start || !goal)
    {
        return;
    }

    std::vector<Edge*> route = graph->FindShortestPath(start, goal);

    if(route.empty())
    {
        return;
    }

    Edge* firstEdge = route[0];

    if(firstEdge->IsOccupied())
    {
        return;
    }

    auto* vehicle =
        new PrivateVehicle(
            firstEdge,
            this,
            IdGenerator<Vehicle>::Next());

    vehicle->SetRoute(route);
    vehicles.push_back(vehicle);
}

const std::vector<std::string>& Simulation::GetMessages() const
{
    return messages;
}

void Simulation::ClearMessages()
{
    messages.clear();
}
