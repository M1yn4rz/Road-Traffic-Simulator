# Road Traffic Simulator

## Project Description

Road Traffic Simulator is a desktop application written in C++ using the Qt framework.  
The program simulates road traffic in a city grid environment with vehicles, intersections, traffic lights, and pedestrian crossings.

The application allows the user to observe traffic flow in real time, manage simulation speed, and generate different vehicle types such as private cars and emergency vehicles.

---

## Main Features

- simulation of vehicle movement on a road network,
- city map based on graph structure,
- intersections with traffic light control,
- pedestrian crossings,
- private vehicles with selected routes,
- emergency vehicles with traffic priority,
- dynamic vehicle spawning,
- real-time graphical visualization,
- event logging and simulation statistics,
- adjustable simulation speed.

---

## Technologies Used

- **C++17**
- **Qt Widgets**
- **CMake**
- Object-Oriented Programming
- Doxygen documentation

---

## Project Structure

### Core Logic

- `Simulation` – manages simulation flow,
- `SimulationController` – connects GUI with logic,
- `Graph` – road network representation,
- `Node` – intersections / points on map,
- `Edge` – road connections,
- `TrafficLight` – traffic signal logic.

### Vehicles

- `Vehicle` – abstract base class,
- `StandardVehicle` – regular traffic vehicle,
- `PrivateVehicle` – route-based vehicle,
- `EmergencyVehicle` – priority vehicle.

### Graphical Interface

- `MainWindow` – main application window,
- `MapView` – simulation rendering,
- `VehicleItem` – graphical vehicle representation.

---

## How to Build

### Requirements

- Qt 5 or Qt 6
- CMake 3.16+
- C++17 compatible compiler

### Build Steps

```bash
mkdir build
cd build
cmake ..
cmake --build .
