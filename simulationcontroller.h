#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H

class Simulation;

/**
 * @brief Controller class managing communication
 * between GUI and simulation logic.
 *
 * Provides simplified access to simulation operations.
 */
class SimulationController
{
public:

    /** @brief Creates simulation controller. */
    SimulationController();

    /** @brief Returns simulation object. */
    Simulation& GetSimulation();

    /** @brief Performs one simulation update step. */
    void Update();

    /** @brief Resets simulation state. */
    void Reset();

private:

    Simulation* simulation;
};

#endif
