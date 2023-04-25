#include "RRTConnect/SolverRRTConnect.h"
#include "RRTConnect/ShapeFactory.h"

#include <iostream>
#include <cmath>
#include <thread>

SolverRRTConnect::SolverRRTConnect(Grid* grid, const Config* config)
: m_grid(grid), m_config(config), m_existingPath(false), m_solved(false), m_solving(false)
{}

SolverRRTConnect::~SolverRRTConnect()
{}

bool SolverRRTConnect::isGoalReached()
{
    Vertex* goal = m_grid->getGoal();
    Vertex* last = m_grid->getVertices().back();

    if (last->x() == goal->x() && last->y() == goal->y())
    {
        m_solved = true;
        return true;
    }

    return false;
}

Vertex* SolverRRTConnect::findNearestNode(Vertex* qNew)
{
    Vertex* nearest = nullptr;
    float minDistance = 10000.0f;

    for (auto& vertex : m_grid->getVertices())
    {
        float distance = sqrt(pow(vertex->x() - qNew->x(), 2) + pow(vertex->y() - qNew->y(), 2));
        if (distance < minDistance)
        {
            minDistance = distance;
            nearest = vertex;
        }
    }

    return nearest;
}

bool SolverRRTConnect::isObstacleBetween(Vertex* qNear, Vertex* qNew)
{
    float x1 = qNear->x();
    float y1 = qNear->y();
    float x2 = qNew->x();
    float y2 = qNew->y();

    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = std::max(abs(dx), abs(dy));

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i < steps; i++)
    {
        x += xInc;
        y += yInc;

        for (auto& obstacle : m_grid->getObstacles())
        {
            if (obstacle->isPointInside(sf::Vector2f(x, y)))
            {
                return true;
            }
        }
    }

    return false;
}

bool SolverRRTConnect::isInObstacle(Vertex* qNew)
{
    for (auto& obstacle : m_grid->getObstacles())
    {
        if (obstacle->isPointInside(sf::Vector2f(qNew->x(), qNew->y())) ||
            obstacle->isPointInside(sf::Vector2f(qNew->x() + qNew->w(), qNew->y())) ||
            obstacle->isPointInside(sf::Vector2f(qNew->x(), qNew->y() + qNew->h())) ||
            obstacle->isPointInside(sf::Vector2f(qNew->x() + qNew->w(), qNew->y() + qNew->h())))
        {
            return true;
        }
    }

    return false;
}

Vertex* SolverRRTConnect::createRandomNode()
{
    sf::CircleShape* circle = ShapeFactory::createVertexShape();
    CollisionGeometry collisionGeometry = CollisionGeometry(
        sf::Vector2f(rand() % m_config->windowX, rand() % m_config->windowY), 
        sf::Vector2f(circle->getRadius()*2, circle->getRadius()*2));

    Vertex* qNew = new Vertex(collisionGeometry, circle);
    if (isInObstacle(qNew))
    {
        delete qNew;
        return createRandomNode();
    }

    return qNew;
}

void SolverRRTConnect::solve()
{
    Vertex* start = m_grid->getStart();
    Vertex* goal = m_grid->getGoal();

    if (!start)
    {
        std::cout << "No starting point" << std::endl;
        return;
    }

    if (!goal)
    {
        std::cout << "No goal point" << std::endl;
        return;
    }

    if (start == goal)
    {
        std::cout << "Starting point is the same as the goal point, path already exist" << std::endl;
        return;
    }

    Vertex* qNew = nullptr;
    Vertex* qNear = nullptr;

    m_solved = false;
    m_solving = true;
    int i = 0;
    std::cout << "Iteration: " << i << std::endl;
    while (!m_solved && i <= 1000)
    {
        i++;
        std::cout << "Iteration: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        qNew = createRandomNode();
        qNear = findNearestNode(qNew);

        if (qNear->x() == qNew->x() && qNear->y() == qNew->y())
        {
            continue;
        }

        if (isObstacleBetween(qNear, qNew))
        {
            continue;
        }

        m_grid->addVertex(qNew->x(), qNew->y());
        m_grid->addEdge(qNear, qNew);

        if (isGoalReached())
        {
            m_solved = true;
            break;
        }
    }
}