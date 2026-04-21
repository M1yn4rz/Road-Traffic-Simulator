#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "simulationcontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MapView;

/**
 * @brief Main application window of the traffic simulator.
 *
 * Responsible for user interface handling,
 * controlling the simulation, and displaying the map.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /** @brief Creates the main application window. */
    MainWindow(QWidget *parent = nullptr);

    /** @brief Destroys the window and releases resources. */
    ~MainWindow();

private slots:

    /** @brief Handles a single simulation tick update. */
    void OnTick();

    /** @brief Starts the simulation. */
    void OnStartButtonClicked();

    /** @brief Stops the simulation. */
    void OnStopButtonClicked();

    /** @brief Resets the simulation state. */
    void OnResetButtonClicked();

    /** @brief Closes the application. */
    void OnCloseButtonClicked();

    /**
     * @brief Changes simulation speed.
     * @param value New speed value.
     */
    void OnSpinBoxValueChanged(const int value);

    /** @brief Adds a new vehicle to the simulation. */
    void OnAddVehicleClicked();

private:

    QTimer* timer;
    MapView* mapView;
    Ui::MainWindow *ui;
    SimulationController controller;

    int lastEventIndex;
    bool vehiclesInitialized;
};

#endif
