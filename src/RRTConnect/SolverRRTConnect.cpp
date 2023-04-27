#include "RRTConnect/SolverRRTConnect.h"
#include "RRTConnect/ShapeFactory.h"

#include <iostream>
#include <cmath>
#include <thread>
#include <random>

#define MAX_DISTANCE 200.0
#define RESOLUTION 1.0

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

double angle(const Vertex* n1, const Vertex* n2)
{
    return atan2(n2->y() - n1->y(), n2->x() - n1->x());
}

double dist(const Vertex* n1, const Vertex* n2)
{
    return sqrt(pow(n1->x() - n2->x(), 2) + pow(n1->y() - n2->y(), 2));
}

int SolverRRTConnect::grid2Index(int x, int y)
{
  return x + m_config->windowX * y;
}

void SolverRRTConnect::index2Grid(int i, int& x, int& y)
{
  x = i % m_config->windowX;
  y = i / m_config->windowX;
}

Vertex* createVertexAtPos(float x, float y)
{
    sf::CircleShape* circle = ShapeFactory::createVertexShape();
    CollisionGeometry collisionGeometry = CollisionGeometry(
        sf::Vector2f(x, y), 
        sf::Vector2f(circle->getRadius()*2, circle->getRadius()*2));

    return new Vertex(collisionGeometry, circle);
}

Vertex* SolverRRTConnect::findNearestNode(std::unordered_set<Vertex, VertexIdAsHash, CompareCoordinates> list, Vertex* node)
{
    Vertex* nearest = nullptr;
    Vertex* newNode = createVertexAtPos(node->x(), node->y());
    newNode->m_id = node->m_id;
    newNode->m_parentId = node->m_parentId;

    double minDistance = std::numeric_limits<double>::max();

    for (auto& vertex : list)
    {
        float distance = dist(&vertex, newNode);
        if (distance < minDistance)
        {
            nearest = createVertexAtPos(vertex.x(), vertex.y());
            nearest->m_id = vertex.m_id;
            nearest->m_parentId = vertex.m_parentId;
            newNode->m_parentId = nearest->m_id;

            minDistance = distance;
        }
    }

    if (minDistance > MAX_DISTANCE)
    {
        double theta = angle(nearest, newNode);
        newNode->m_collisionGeometry.m_position.x = nearest->x() + (int)(MAX_DISTANCE * cos(theta));
        newNode->m_collisionGeometry.m_position.y = nearest->y() + (int)(MAX_DISTANCE * sin(theta));

        newNode->m_id = grid2Index(newNode->x(), newNode->y());
    }

    if (isObstacleBetween(newNode, nearest))
        newNode->m_id = -1;

    return newNode;
}

bool SolverRRTConnect::isObstacleBetween(Vertex* n1, Vertex* n2)
{
    double theta = angle(n1, n2);
    double distance = dist(n1, n2);

    if (distance > MAX_DISTANCE)
        return true;

    float nStep = (int)(distance / RESOLUTION);
    for (size_t i = 0; i < nStep; i++)
    {
        float lineX = (float)n1->x() + (float)(i * RESOLUTION * cos(theta));
        float lineY = (float)n1->y() + (float)(i * RESOLUTION * sin(theta));
        //std::cout << "Pos x: " << lineX << " y: " << lineY << std::endl;

        for (auto& obstacle : m_grid->getObstacles())
        {
            if (obstacle->isPointInside(sf::Vector2f(lineX, lineY)))
            {
                std::cout << "There is obstacle" << std::endl;
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

float randomizeFromRange(float x1, float x2)
{
    // obtain a random number from hardware
    std::random_device rd;
    // seed the generator
    std::mt19937 eng(rd());
    // define the range
    std::uniform_real_distribution<float> p(x1, x2);
    return p(eng);
}

Vertex* SolverRRTConnect::createRandomNode()
{
    Vertex* vertex = createVertexAtPos(
        randomizeFromRange(0, m_config->windowX), 
        randomizeFromRange(0, m_config->windowY));
    vertex->m_id = grid2Index(vertex->x(), vertex->y());
    return vertex;
}

bool SolverRRTConnect::solve()
{
    sampleListFront.clear();
    sampleListBack.clear();

    Vertex* start = m_grid->getStart();
    Vertex* goal = m_grid->getGoal();

    if (!start)
    {
        std::cout << "No starting point" << std::endl;
        return false;
    }

    if (!goal)
    {
        std::cout << "No goal point" << std::endl;
        return false;
    }

    if (start == goal)
    {
        std::cout << "Starting point is the same as the goal point, path already exist" << std::endl;
        return false;
    }

    start->m_id = grid2Index(start->x(), start->y());
    goal->m_id = grid2Index(goal->x(), goal->y());

    sampleListFront.insert(*start);
    sampleListBack.insert(*goal);

    m_solved = false;
    m_solving = true;
    int i = 0;
    while (!m_solved && i < 1000)
    {
        std::cout << "Iteration: " << i << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));

        Vertex* sampleNode = createRandomNode();

        // obstacle
        if (isInObstacle(sampleNode))
        {
            std::cout << "sampleNode in obstacle" << std::endl;
            continue;
        }

        // visited
        if (sampleListFront.find(*sampleNode) != sampleListFront.end() ||
            sampleListBack.find(*sampleNode) != sampleListBack.end())
        {
            std::cout << "sampleNode visited" << std::endl;   
            continue;
        }

        Vertex* newNode = findNearestNode(sampleListFront, sampleNode);
        std::cout << "newNode found" << std::endl;

        if (newNode->m_id == -1)
        {
            std::cout << "newNode id is -1" << std::endl;
            continue;
        }
        else
        {
            std::cout << "addVertex newNode" << std::endl;
            m_grid->addVertex(newNode->x(), newNode->y());
            sampleListFront.insert(*newNode);

            Vertex* newNodeBack = findNearestNode(sampleListBack, newNode);
            std::cout << "NewNodeBack at pos x: " << newNodeBack->x() << " y: " << newNodeBack->y() << std::endl;

            if (newNodeBack->m_id != -1)
            {
                std::cout << "newNodeBack id is not -1" << std::endl;
                sampleListBack.insert(*newNodeBack);
                std::cout << "addVertex newNodeBack" << std::endl;
                m_grid->addVertex(newNodeBack->x(), newNodeBack->y());

                // greedy extending
                while (true)
                {
                    //std::cout << "getting greedy" << std::endl;
                    double distance = std::min(MAX_DISTANCE, dist(newNode, newNodeBack));
                    double theta = angle(newNodeBack, newNode);

                    int x = newNodeBack->x() + (int)(distance * cos(theta));
                    int y = newNodeBack->y() + (int)(distance * sin(theta));

                    Vertex* newNodeBack2 = createVertexAtPos(x, y);
                    newNodeBack2->m_id = grid2Index(newNodeBack2->x(), newNodeBack2->y());
                    newNodeBack2->m_parentId = newNodeBack->m_id;

                    if (!isObstacleBetween(newNodeBack, newNodeBack2))
                    {
                        //std::cout << "Adding node in greedy" << std::endl;
                        m_grid->addVertex(newNodeBack2->x(), newNodeBack2->y());
                        sampleListBack.insert(*newNodeBack2);

                        newNodeBack = createVertexAtPos(newNodeBack2->x(), newNodeBack2->y());
                        newNodeBack->m_id = newNodeBack2->m_id;
                        newNodeBack->m_parentId = newNodeBack2->m_parentId;
                    }
                    else
                    {
                        std::cout << "breaking" << std::endl;
                        break;
                    }

                    // goal found
                    if (newNodeBack == newNode)
                    {
                        std::cout << "Path found" << std::endl;
                        return true;
                    }
                }
            }
        }

        // swap
        if (sampleListBack.size() < sampleListFront.size())
            std::swap(sampleListFront, sampleListBack);

        
        //std::cout << "After greedy" << std::endl;

        //m_grid->addEdge(qNear, qNew);
        i++;
    }
    std::cout << "DONE" << std::endl;

    return false;
}