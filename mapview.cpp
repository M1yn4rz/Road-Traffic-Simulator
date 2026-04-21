#include "mapview.h"

#include <QResizeEvent>
#include "vehicleitem.h"
#include "vehicle.h"
#include "graph.h"
#include "edge.h"
#include "node.h"
#include "trafficlight.h"

MapView::MapView(QWidget* parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , vehicleItems()
    , lightLabels()
    , crosswalkLabels()
{
    scene->setSceneRect(0, 0, 2500, 850);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setScene(scene);
}

void MapView::DrawMap(const Graph* graph)
{
    scene->clear();
    const double widthRoad = 40;

    for (const auto& edge : graph->GetEdges())
    {
        const double x1 = edge->GetX1();
        const double y1 = edge->GetY1();
        const double x2 = edge->GetX2();
        const double y2 = edge->GetY2();

        const double dx = x2 - x1;
        const double dy = y2 - y1;

        const double length = sqrt(dx*dx + dy*dy);

        if (!length)
        {
            continue;
        }

        scene->addLine(
            x1, y1,
            x2, y2,
            QPen(Qt::darkGray, widthRoad)
            );
    }

    int nodeId = 1;
    int space = 0;

    for (const auto& node : graph->GetNodes())
    {
        if (node->GetIsIntersection())
        {
            auto text = scene->addText(QString::number(nodeId));
            auto lightText = scene->addText("-");

            text->setPos(node->GetX() + 20, node->GetY() + 10);
            space = nodeId < 10 ? 50 : 70;
            lightText->setPos(node->GetX() + space, node->GetY() + 10);

            lightLabels[nodeId] = lightText;

            QFont font;
            font.setPointSize(24);
            font.setBold(true);

            text->setFont(font);
            lightText->setFont(font);

            nodeId++;
        }
    }

    for(auto node : graph->GetNodes())
    {
        if(!node->HasCrosswalk())
        {
            continue;
        }

        scene->addEllipse(
            node->GetX() - 8,
            node->GetY() - 8,
            16,
            16,
            QPen(Qt::yellow, 20),
            QBrush(Qt::yellow));

        auto text = scene->addText("P[WAIT]");
        text->setDefaultTextColor(Qt::black);
        text->setPos(
            node->GetX() - 30,
            node->GetY() - 60);

        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        text->setFont(font);

        crosswalkLabels[node->GetId()] = text;
    }
}

void MapView::AddVehicles(const std::vector<Vehicle*>& vehicles)
{
    if (vehicleItems.size())
    {
        for (auto& item : vehicleItems)
        {
            delete item;
        }

        vehicleItems.clear();
    }

    for (const auto& v : vehicles)
    {
        auto item = new VehicleItem(v);
        scene->addItem(item);
        vehicleItems.push_back(item);
    }
}

void MapView::UpdateLights(const Graph* graph, const std::vector<TrafficLight*>& lights)
{
    for (const auto& light : lights)
    {
        int id = light->GetId();

        if (lightLabels.count(id))
        {
            QString symbol =
                light->GetState() == "ALL RED" ? "X" :
                light->GetState() == "EW GREEN" ? "-"
                : "|";
            lightLabels[id]->setPlainText(symbol);
        }
    }

    for(auto node : graph->GetNodes())
    {
        if(!node->HasCrosswalk())
        {
            continue;
        }

        QString status =
            node->IsPedestrianActive()
                ? "P[GO]"
                : "P[WAIT]";

        crosswalkLabels[node->GetId()]
            ->setPlainText(status);
    }
}

void MapView::UpdateVehicles()
{
    for (auto& item : vehicleItems)
    {
        item->UpdatePosition();
    }
}

void MapView::ClearVehicles()
{
    for (auto& item : vehicleItems)
    {
        scene->removeItem(item);
        delete item;
    }

    vehicleItems.clear();
}

void MapView::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
