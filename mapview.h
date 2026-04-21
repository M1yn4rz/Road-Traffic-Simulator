#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include <map>

class Graph;
class Vehicle;
class VehicleItem;
class TrafficLight;

/**
 * @brief Map view used to display the simulation.
 *
 * Responsible for drawing roads, vehicles,
 * and traffic light states.
 */
class MapView : public QGraphicsView
{
public:

    /** @brief Creates map view widget. */
    MapView(QWidget* parent = nullptr);

    /** @brief Draws the map using graph data. */
    void DrawMap(const Graph* graph);

    /** @brief Adds vehicles to the view. */
    void AddVehicles(const std::vector<Vehicle*>& vehicles);

    /** @brief Updates traffic light states. */
    void UpdateLights(const Graph* graph, const std::vector<TrafficLight*>& lights);

    /** @brief Updates vehicle positions. */
    void UpdateVehicles();

    /** @brief Removes all vehicles from the view. */
    void ClearVehicles();

protected:

    /** @brief Handles widget resize event. */
    void resizeEvent(QResizeEvent* event) override;

private:

    QGraphicsScene* scene;
    std::vector<VehicleItem*> vehicleItems;
    std::map<int, QGraphicsTextItem*> lightLabels;
    std::map<int, QGraphicsTextItem*> crosswalkLabels;
};

#endif
