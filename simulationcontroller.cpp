#include "simulationcontroller.h"

#include "simulation.h"

SimulationController::SimulationController() : simulation(new Simulation())
{
}

Simulation& SimulationController::GetSimulation()
{
    return *simulation;
}

void SimulationController::Update()
{
    simulation->Tick();
}

void SimulationController::Reset()
{
    simulation = new Simulation();
}
