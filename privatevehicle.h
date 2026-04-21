#ifndef PRIVATEVEHICLE_H
#define PRIVATEVEHICLE_H

#include "vehicle.h"
#include "node.h"
#include "edge.h"

/**
 * @brief Class representing a private vehicle with a planned route.
 *
 * The vehicle follows a predefined path between
 * selected start and destination nodes.
 */
class PrivateVehicle : public Vehicle
{
public:

    /**
     * @brief Creates a private vehicle.
     * @param start Initial edge.
     * @param sim Pointer to simulation object.
     * @param vehicleId Unique vehicle identifier.
     */
    PrivateVehicle(Edge* start, Simulation* sim, int vehicleId);

    /** @brief Returns vehicle display color. */
    QColor GetColor() const override;

    /** @brief Returns movement speed. */
    double GetSpeed() const override;

    /** @brief Checks if traffic lights are respected. @return true. */
    bool ShouldRespectLights() const override;

    /**
     * @brief Assigns route to the vehicle.
     * @param newRoute Sequence of edges.
     */
    void SetRoute(const std::vector<Edge*>& newRoute);

    /** @brief Checks whether route is finished. */
    bool IsFinished() const;

    /** @brief Returns start node identifier. */
    int GetStartNodeId() const;

    /** @brief Returns destination node identifier. */
    int GetEndNodeId() const;

    /** @brief Returns total travel time in ticks. */
    int GetTravelTime() const;

    /**
     * @brief Performs one movement step of the emergency vehicle.
     */
    void Move() override;

protected:

    /**
     * @brief Selects next edge from assigned route.
     * @param currentNode Current node.
     * @return Next route edge or nullptr.
     */
    Edge* ChooseNextEdge(Node* currentNode) override;

private:

    std::vector<Edge*> route;
    int routeIndex;

    int startTick;
    int endTick;

    int startNodeId;
    int endNodeId;
};

#endif
