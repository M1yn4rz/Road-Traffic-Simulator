#include "graph.h"

#include <cmath>
#include "node.h"
#include "edge.h"
#include <queue>
#include <map>

const double SEGMENT_LENGTH = 50.0;

Graph::Graph()
    : nextAutoNodeId(100)
    , nodes()
    , edges()
{
}

Node* Graph::AddNode(const int id, const double x, const double y)
{
    Node* node = new Node(id, x, y);
    nodes.push_back(node);

    return node;
}

void Graph::AddRoad(Node* from, Node* to)
{
    const double x1 = from->GetX();
    const double y1 = from->GetY();
    const double x2 = to->GetX();
    const double y2 = to->GetY();

    const double dx = x2 - x1;
    const double dy = y2 - y1;

    const double length = sqrt(dx*dx + dy*dy);
    const unsigned int segments = length / SEGMENT_LENGTH;

    Node* prev = from;

    double t = 0;
    double nx = 0;
    double ny = 0;

    for (int i = 1; i < segments; i++)
    {
        t = (double) i / segments;

        nx = x1 + dx * t;
        ny = y1 + dy * t;

        Node* next = AddNode(nextAutoNodeId++, nx, ny);
        next->SetIsIntersection(false);

        AddEdge(prev, next);
        prev = next;
    }

    AddEdge(prev, to);
}

const std::vector<Node*>& Graph::GetNodes() const
{
    return nodes;
}

const std::vector<Edge*>& Graph::GetEdges() const
{
    return edges;
}

Edge* Graph::AddEdge(Node* from, Node* to)
{
    Edge* edge = new Edge(from, to);
    from->AddEdge(edge);
    edges.push_back(edge);

    return edge;
}

std::vector<Edge*> Graph::FindShortestPath(Node* start, Node* end) const
{
    std::queue<Node*> q;
    std::map<Node*, Edge*> prev;
    q.push(start);
    prev[start]=nullptr;

    while(!q.empty())
    {
        Node* n=q.front(); q.pop();

        if(n==end)
        {
            break;
        }

        for(auto e:n->GetEdges())
        {
            Node* next=e->GetTargetNode();

            if(!prev.count(next))
            {
                prev[next]=e;
                q.push(next);
            }
        }
    }

    std::vector<Edge*> path;

    if(!prev.count(end))
    {
        return path;
    }

    Node* cur=end;

    while(cur!=start)
    {
        Edge* e=prev[cur];
        path.insert(path.begin(), e);
        cur=e->GetSourceNode();
    }

    return path;
}
