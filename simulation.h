#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

class TrafficLight;
class Vehicle;
class Graph;
class Node;

struct TrafficEvent
{
    int tick;
    int nodeId;
    int vehicleA;
    int vehicleB;
};

/**
 * @brief Class managing the entire traffic simulation.
 *
 * Responsible for the road map, vehicles, traffic lights,
 * traffic events, and consecutive simulation time steps.
 */
class Simulation
{
public:

    /** @brief Creates a simulation object and initializes the map. */
    Simulation();

    /** @brief Releases dynamically allocated simulation resources. */
    ~Simulation();

    /**
     * @brief Copy constructor deleted.
     *
     * Copying Simulation objects is disabled because the class
     * manages dynamically allocated resources.
     */
    Simulation(const Simulation&) = delete;

    /**
     * @brief Copy assignment operator deleted.
     *
     * Assigning Simulation objects is disabled because the class
     * manages dynamically allocated resources.
     * @return Reference to this object.
     */
    Simulation& operator=(const Simulation&) = delete;

    /**
     * @brief Adds random standard vehicles.
     * @param numberVehicles Number of vehicles to create.
     */
    void AddVehicles(const int numberVehicles);

    /** @brief Creates the road map and intersections. */
    void CreateMap();

    /** @brief Executes one simulation tick. */
    void Tick();

    /** @brief Removes vehicles that finished their routes. */
    void RemoveFinishedVehicles();

    /** @brief Returns current simulation tick number. @return Tick value. */
    int GetTick() const;

    /** @brief Returns pointer to the road graph. @return Graph object. */
    Graph* GetGraph() const;

    /**
     * @brief Returns traffic light assigned to a node.
     * @param node Intersection node.
     * @return Pointer to traffic light or nullptr.
     */
    TrafficLight* GetLightForNode(Node* node);

    /** @brief Returns list of vehicles. */
    const std::vector<Vehicle*>& GetVehicles() const;

    /** @brief Returns list of traffic events. */
    const std::vector<TrafficEvent>& GetEvents() const;

    /** @brief Returns list of traffic lights. */
    const std::vector<TrafficLight*>& GetLights() const;

    /**
     * @brief Sets emergency vehicle spawn interval.
     * @param value Number of ticks between spawns.
     */
    void SetEmergencySpawnInterval(int value);

    /** @brief Spawns a random emergency vehicle. */
    void SpawnEmergencyVehicle();

    /**
     * @brief Adds a private vehicle between two nodes.
     * @param start Start node.
     * @param end Destination node.
     */
    void AddPrivateVehicle(Node* start, Node* end);

    /**
     * @brief Creates a private vehicle using node identifiers.
     * @param fromId Start node ID.
     * @param toId Destination node ID.
     */
    void SpawnPrivateVehicle(int fromId, int toId);

    /** @brief Returns simulation log messages. */
    const std::vector<std::string>& GetMessages() const;

    /** @brief Clears stored messages. */
    void ClearMessages();

private:

    std::vector<TrafficLight*> lights;
    std::vector<TrafficEvent> events;
    std::vector<Vehicle*> vehicles;
    Graph* graph;
    int nextVehicleId;
    int currentTick;
    int emergencySpawnInterval;
    std::vector<std::string> messages;

};

#endif
