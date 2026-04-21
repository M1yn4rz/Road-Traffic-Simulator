#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "mapview.h"
#include "trafficlight.h"
#include "simulation.h"
#include "privatevehicle.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , timer(new QTimer(this))
    , mapView(new MapView(this))
    , ui(new Ui::MainWindow)
    , lastEventIndex(0)
    , vehiclesInitialized(false)
{
    ui->setupUi(this);
    mapView->setSceneRect(0, 0, 2500, 850);

    ui->SimulationView->parentWidget()->layout()->replaceWidget(ui->SimulationView, mapView);
    delete ui->SimulationView;

    connect(timer, &QTimer::timeout, this, &MainWindow::OnTick);

    connect(ui->StartButton, &QPushButton::clicked, this, &MainWindow::OnStartButtonClicked);
    connect(ui->StopButton, &QPushButton::clicked, this, &MainWindow::OnStopButtonClicked);
    connect(ui->ResetButton, &QPushButton::clicked, this, &MainWindow::OnResetButtonClicked);
    connect(ui->CloseButton, &QPushButton::clicked, this, &MainWindow::OnCloseButtonClicked);
    connect(ui->AddVehicleButton, &QPushButton::clicked, this, &MainWindow::OnAddVehicleClicked);

    connect(ui->TickrateSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::OnSpinBoxValueChanged);

    mapView->DrawMap(controller.GetSimulation().GetGraph());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnTick()
{
    auto& sim = controller.GetSimulation();
    controller.Update();
    mapView->AddVehicles(sim.GetVehicles());
    mapView->UpdateVehicles();

    for(const auto& msg : sim.GetMessages())
    {
        ui->Logger->addItem(QString::fromStdString(msg));
    }

    sim.ClearMessages();

    QString info = "Tick: " + QString::number(sim.GetTick()) + "\n"
        + "Number of Vehicles: " + QString::number(sim.GetVehicles().size()) + "\n";

    int id = 1;
    QString end = "";
    QString step = "";

    for (const auto& light : sim.GetLights())
    {
        end = id % 2 ? "\t" : "\n";
        step = id < 10 ? "   " : " ";

        info += "Node " + QString::number(light->GetId()) +
                ": " + step + QString::fromStdString(light->GetState()) + end;

        id++;
    }

    for(auto v : sim.GetVehicles())
    {
        if(auto* pv = dynamic_cast<PrivateVehicle*>(v))
        {
            info +=
                "Private Vehicle " +
                QString::number(pv->GetId()) +
                " [" +
                QString::number(pv->GetStartNodeId()) +
                " -> " +
                QString::number(pv->GetEndNodeId()) +
                "] : " +
                QString::number(
                    pv->GetTravelTime()) +
                " ticks\n";
        }
    }

    ui->InformationPanel->setText(info);
    mapView->UpdateLights(controller.GetSimulation().GetGraph(), sim.GetLights());

    const auto& events = sim.GetEvents();

    for (int i = lastEventIndex; i < events.size(); i++)
    {
        const auto& e = events[i];

        QString msg = "[TICK " + QString::number(e.tick) + "] "
                      + "Intersection " + QString::number(e.nodeId)
                      + ": Vehicle " + QString::number(e.vehicleA)
                      + " & Vehicle " + QString::number(e.vehicleB)
                      + " collision risk";

        ui->Logger->addItem(msg);
    }

    for(auto v : sim.GetVehicles())
    {
        Q_UNUSED(v);
    }

    lastEventIndex = events.size();
}

void MainWindow::OnStartButtonClicked()
{
    controller.GetSimulation().SetEmergencySpawnInterval(ui->EmergencySpinBox->value());

    int interval = ui->TickrateSpinBox->value();
    timer->start(1000 / interval);

    if (!vehiclesInitialized)
    {
        int numberVehicles = ui->VehiclesSpinBox->value();
        controller.GetSimulation().AddVehicles(numberVehicles);

        auto& sim = controller.GetSimulation();
        mapView->AddVehicles(sim.GetVehicles());

        vehiclesInitialized = true;
    }
}

void MainWindow::OnStopButtonClicked()
{
    timer->stop();
}

void MainWindow::OnResetButtonClicked()
{
    timer->stop();
    mapView->ClearVehicles();
    controller.Reset();
    mapView->DrawMap(controller.GetSimulation().GetGraph());

    vehiclesInitialized = false;
}

void MainWindow::OnCloseButtonClicked()
{
    close();
}

void MainWindow::OnSpinBoxValueChanged(const int value)
{
    if (timer->isActive())
    {
        timer->start(value * 1000);
    }
}

void MainWindow::OnAddVehicleClicked()
{
    int fromId = ui->FromAddSpin->value();
    int toId   = ui->ToAddSpin->value();

    controller.GetSimulation().SpawnPrivateVehicle(fromId, toId);

    mapView->AddVehicles(controller.GetSimulation().GetVehicles());
}
