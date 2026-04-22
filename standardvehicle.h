#ifndef STANDARDVEHICLE_H
#define STANDARDVEHICLE_H

#include "vehicle.h"

/**
 * @brief Class representing a standard vehicle in the simulation.
 *
 * Standard vehicles move through the map using default
 * movement rules and obey traffic lights.
 */
class StandardVehicle : public Vehicle
{
public:

    /**
     * @brief Creates a standard vehicle.
     * @param start Initial edge.
     * @param sim Pointer to simulation object.
     * @param vehicleId Unique vehicle identifier.
     */
    StandardVehicle(Edge* start, Simulation* sim, int vehicleId);

    /** @brief Returns vehicle display color. */
    VehicleColor GetColor() const override;

    /** @brief Returns movement speed. */
    double GetSpeed() const override;

    /** @brief Checks if traffic lights are respected. @return true. */
    bool ShouldRespectLights() const override;

protected:

    /**
     * @brief Selects next edge after reaching a node.
     * @param currentNode Current node.
     * @return Pointer to next road segment.
     */
    Edge* ChooseNextEdge(Node* currentNode) override;
};

#endif
