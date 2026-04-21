#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Node;
class Edge;

/**
 * @brief Class representing the road network graph.
 *
 * Stores nodes and edges of the map and provides
 * methods for creating roads and searching routes.
 */
class Graph
{
public:

    /** @brief Creates an empty graph. */
    Graph();

    /**
     * @brief Adds a new node to the graph.
     * @param id Node identifier.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @return Pointer to created node.
     */
    Node* AddNode(int id, double x, double y);

    /**
     * @brief Adds a directed road between two nodes.
     * @param source Start node.
     * @param target Destination node.
     * @return Pointer to created edge.
     */
    void AddRoad(Node* from, Node* to);

    /** @brief Returns all graph nodes. */
    const std::vector<Node*>& GetNodes() const;

    /** @brief Returns all graph edges. */
    const std::vector<Edge*>& GetEdges() const;

    /**
     * @brief Finds shortest path between two nodes.
     * @param start Start node.
     * @param end Destination node.
     * @return Sequence of edges forming the route.
     */
    std::vector<Edge*> FindShortestPath(Node* start, Node* end) const;

private:

    Edge* AddEdge(Node* from, Node* to);

    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

    int nextAutoNodeId;
};

#endif
