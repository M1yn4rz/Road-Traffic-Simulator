#ifndef NODE_H
#define NODE_H

#include <vector>

class Edge;

/**
 * @brief Class representing a map node or intersection.
 *
 * Stores coordinates, identifier, connected roads,
 * and pedestrian crossing information.
 */
class Node
{
public:

    /**
     * @brief Creates a node.
     * @param id Node identifier.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Node(const int id, const double x, const double y);

    /**
     * @brief Adds outgoing edge to the node.
     * @param edge Edge to add.
     */
    void AddEdge(Edge* edge);

    /**
     * @brief Sets whether the node is an intersection.
     * @param status true if the node should be marked as an intersection,
     * false otherwise.
     */
    void SetIsIntersection(const bool status);

    /** @brief Returns outgoing edges. */
    const std::vector<Edge*>& GetEdges() const;

    /** @brief Checks whether node is an intersection. @return true if yes. */
    bool GetIsIntersection() const;

    /** @brief Returns X coordinate. @return X position. */
    double GetX() const;

    /** @brief Returns Y coordinate. @return Y position. */
    double GetY() const;

    /** @brief Returns node identifier. @return Node ID. */
    int GetId() const;

    /**
     * @brief Enables or disables pedestrian crossing.
     * @param value Crossing state.
     */
    void SetCrosswalk(bool value);

    /** @brief Returns crossing state. @return true if crossing exists. */
    bool HasCrosswalk() const;

    /** @brief Checks if pedestrians are currently active. */
    bool IsPedestrianActive() const;

    /**
     * @brief Activates pedestrian crossing at this node.
     *
     * Enables pedestrian movement for the crossing,
     * temporarily blocking vehicle passage if applicable.
     */
    void ActivatePedestrian();

    /** @brief Updates pedestrian crossing state. */
    void UpdateCrosswalk();

    /**
     * @brief Sets paired pedestrian crossing node.
     * @param node Paired node.
     */
    void SetPairedCrosswalk(Node* node);

    /** @brief Returns paired crossing node. */
    Node* GetPairedCrosswalk() const;

private:

    int id;
    double x;
    double y;
    bool isIntersection;
    std::vector<Edge*> outgoingEdges;
    bool hasCrosswalk;
    bool pedestrianActive;
    int pedestrianTicks;
    Node* pairedCrosswalk;
};

#endif
