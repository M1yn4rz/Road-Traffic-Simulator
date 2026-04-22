#ifndef EMERGENCYVEHICLE_H
#define EMERGENCYVEHICLE_H

#include "vehicle.h"

/**
 * @brief Class representing an emergency vehicle.
 *
 * Emergency vehicles have movement priority,
 * may ignore traffic lights, and affect traffic control.
 */
class EmergencyVehicle : public Vehicle
{
public:

    /**
     * @brief Creates an emergency vehicle.
     * @param start Initial edge.
     * @param sim Pointer to simulation object.
     * @param vehicleId Unique vehicle identifier.
     */
    EmergencyVehicle(Edge* start, Simulation* sim, int vehicleId);

    /** @brief Returns vehicle display color. */
    VehicleColor GetColor() const override;

    /** @brief Returns movement speed. */
    double GetSpeed() const override;

    /** @brief Emergency vehicles ignore traffic lights. @return false. */
    bool ShouldRespectLights() const override;

    /** @brief Emergency vehicles have priority. @return true. */
    bool HasPriority() const override;

    /** @brief Checks whether route is finished. */
    bool IsFinished() const;

    /**
     * @brief Assigns route to the vehicle.
     * @param newRoute Sequence of edges.
     */
    void SetRoute(const std::vector<Edge*>& newRoute);

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
};

#endif
