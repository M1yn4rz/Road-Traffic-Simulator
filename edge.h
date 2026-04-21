#ifndef EDGE_H
#define EDGE_H

#include <vector>

class Node;
class Vehicle;

/**
 * @brief Class representing a directed road segment.
 *
 * Connects two nodes and stores occupancy state
 * used by vehicles in the simulation.
 */
class Edge
{
public:

    /**
     * @brief Creates an edge between two nodes.
     * @param source Start node.
     * @param target Destination node.
     */
    Edge(Node* from_, Node* to_);

    /** @brief Returns target node. */
    Node* GetTargetNode() const;

    /** @brief Returns source node. */
    Node* GetSourceNode() const;

    /** @brief Returns source X coordinate. */
    double GetX1() const;

    /** @brief Returns source Y coordinate. */
    double GetY1() const;

    /** @brief Returns target X coordinate. */
    double GetX2() const;

    /** @brief Returns target Y coordinate. */
    double GetY2() const;

    /** @brief Checks whether edge is occupied. */
    bool IsOccupied() const;

    /**
     * @brief Sets occupancy state.
     * @param value Occupancy flag.
     */
    void SetOccupied(const bool status);

    /** @brief Checks if emergency vehicle is present. */
    bool HasEmergency() const;

    /**
     * @brief Sets emergency presence state.
     * @param value Emergency flag.
     */
    void SetEmergencyPresent(bool value);

private:

    bool occupied;
    bool emergencyPresent;

    Node* from;
    Node* to;

    double x1;
    double y1;
    double x2;
    double y2;
};

#endif
