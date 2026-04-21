#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <string>

class Node;

/**
 * @brief Class representing traffic lights at an intersection.
 *
 * Controls traffic flow directions and supports
 * emergency lock mode.
 */
class TrafficLight
{
public:

    /**
     * @brief Creates traffic lights.
     * @param id_ Traffic light identifier.
     * @param node_ Controlled node.
     */
    TrafficLight(const int id, Node* node);

    /** @brief Updates traffic light state. */
    void Update();

    /**
     * @brief Checks whether a vehicle may pass.
     * @param from Source node.
     * @param to Destination node.
     * @return true if movement is allowed.
     */
    bool CanPass(Node* from, Node* to) const;

    /** @brief Returns traffic light identifier. */
    int GetId() const;

    /** @brief Returns controlled node. */
    Node* GetNode() const;

    /** @brief Returns current state description. */
    std::string GetState() const;

    /**
     * @brief Enables or disables emergency lock mode.
     * @param value Lock state.
     */
    void SetEmergencyLock(bool value);

    /** @brief Returns emergency lock state. */
    bool IsEmergencyLock() const;

private:

    Node* node;
    int id;
    int timer;
    bool verticalGreen;
    bool emergencyLock;
};

#endif
