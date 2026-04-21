#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <QColor>

class Edge;
class Node;
class Simulation;
class TrafficLight;

/**
 * @brief Abstract base class representing a vehicle in the traffic simulation.
 *
 * The class stores the vehicle identifier, current position,
 * progress on the current road segment, and references to the
 * current edge and simulation object.
 *
 * It serves as a base class for all vehicle types.
 */
class Vehicle
{
public:

    /**
     * @brief Creates a new vehicle.
     * @param start Initial edge on which the vehicle is placed.
     * @param sim Pointer to the simulation object.
     * @param vehicleId Unique vehicle identifier.
     */
    Vehicle(Edge* start, Simulation* sim, int vehicleId);

    /**
     * @brief Virtual destructor of the Vehicle class.
     *
     * Ensures proper destruction of derived vehicle objects
     * when deleted through a base class pointer.
     */
    virtual ~Vehicle() = default;

    /**
     * @brief Performs one movement step of the vehicle.
     *
     * Updates the vehicle position, checks traffic lights,
     * and attempts to move onto the next road segment.
     */
    virtual void Move();

    /** @brief Returns the vehicle color. @return Vehicle color. */
    virtual QColor GetColor() const = 0;

    /** @brief Returns the vehicle speed. @return Vehicle speed value. */
    virtual double GetSpeed() const = 0;

    /** @brief Checks whether the vehicle obeys traffic lights. @return true if yes. */
    virtual bool ShouldRespectLights() const = 0;

    /** @brief Checks whether the vehicle has priority. @return true for priority vehicles. */
    virtual bool HasPriority() const { return false; }

    /** @brief Returns the vehicle identifier. @return Vehicle ID. */
    int GetId() const;

    /** @brief Returns the X coordinate. @return X position. */
    double GetX() const;

    /** @brief Returns the Y coordinate. @return Y position. */
    double GetY() const;

    /** @brief Returns movement progress on current edge. @return Value from 0.0 to 1.0. */
    double GetProgress() const;

    /** @brief Returns the current edge. @return Pointer to current road segment. */
    Edge* GetEdge() const;

protected:

    /**
     * @brief Selects the next edge for movement.
     * @param currentNode Current node.
     * @return Pointer to next edge or nullptr.
     */
    virtual Edge* ChooseNextEdge(Node* currentNode) = 0;

    /** @brief Updates vehicle coordinates based on current progress. */
    void UpdatePosition();

    /**
     * @brief Attempts to switch vehicle to another edge.
     * @param nextEdge Target edge.
     * @return true if switching succeeded.
     */
    bool TrySwitchToEdge(Edge* nextEdge);

    int id;
    double posX;
    double posY;
    double progress;

    Node* previousNode;
    Edge* currentEdge;
    Simulation* simulation;
};

#endif
