#pragma once

#include "RRTConnect/Config.h"

#include "RRTConnect/Obstacle.h"
#include "RRTConnect/Vertex.h"
#include "RRTConnect/Edge.h"
#include "RRTConnect/ShapeFactory.h"

#include <vector>
#include <mutex>

class Grid
{
public:

    Grid(const Config& config)
    : Grid(config, 60, 45)
    {}

    Grid(const Config& config, int width, int height)
    : m_config(config), m_width(width), m_height(height)
    {
        m_obstacles = std::vector<Obstacle*>();
    }

    ~Grid()
    {
        for (auto obstacle : m_obstacles)
            delete obstacle;

        for (auto vertex : m_vertices)
            delete vertex;

        for (auto edge : m_edges)
            delete edge;

        if (m_start)
            delete m_start;

        if (m_goal)
            delete m_goal;
    }

    Obstacle* addObstacle(int xGridPos, int yGridPos)
    {
        Obstacle* obstacle = new Obstacle(xGridPos, yGridPos);
        m_obstacles.push_back(obstacle);
        return obstacle;
    }

    Vertex* addStartingPoint(float xPos, float yPos)
    {
        sf::CircleShape* shape = ShapeFactory::createStartingPointShape();
        m_start = new Vertex(
            CollisionGeometry(sf::Vector2f(xPos, yPos), sf::Vector2f(shape->getRadius()*2, shape->getRadius()*2)), 
            shape);

        m_verticesMutex.lock();
        m_vertices.push_back(m_start);
        m_verticesMutex.unlock();
        return m_start;
    }

    Vertex* addGoalPoint(float xPos, float yPos)
    {
        sf::CircleShape* shape = ShapeFactory::createGoalPointShape();
        m_goal = new Vertex(
            CollisionGeometry(sf::Vector2f(xPos, yPos), sf::Vector2f(shape->getRadius()*2, shape->getRadius()*2)), 
            shape);

        m_verticesMutex.lock();
        m_vertices.push_back(m_goal);
        m_verticesMutex.unlock();
        return m_goal;
    }

    Vertex* addVertex(float xPos, float yPos)
    {
        sf::CircleShape* shape = ShapeFactory::createVertexShape();
        Vertex* vertex = new Vertex(
            CollisionGeometry(sf::Vector2f(xPos, yPos), sf::Vector2f(shape->getRadius()*2, shape->getRadius()*2)), 
            shape);
        
        m_verticesMutex.lock();
        m_vertices.push_back(vertex);
        m_verticesMutex.unlock();
        return vertex;
    }

    std::vector<Edge*> addPath(std::vector<Vertex*> path)
    {
        for (auto vertex : path)
        {
            int x1 = vertex->m_id % m_config.windowX;
            int y1 = vertex->m_id / m_config.windowX;
            int x2 = vertex->m_parentId % m_config.windowX;
            int y2 = vertex->m_parentId / m_config.windowX;

            Vertex* vertex1Ptr = new Vertex(x1, y1);
            Vertex* vertex2Ptr = new Vertex(x2, y2);
            Edge* edge = new Edge(vertex1Ptr, vertex2Ptr);
            edge->setColor(sf::Color::Red);

            m_pathEdges.push_back(edge);
        }

        return m_pathEdges;
    }

    Edge* addEdge(int gridId, int parentGridId)
    {
        int x1 = gridId % m_config.windowX;
        int y1 = gridId / m_config.windowX;
        int x2 = parentGridId % m_config.windowX;
        int y2 = parentGridId / m_config.windowX;

        Vertex* vertex1Ptr = new Vertex(x1, y1);
        Vertex* vertex2Ptr = new Vertex(x2, y2);
        Edge* edge = new Edge(vertex1Ptr, vertex2Ptr);
        
        m_edges.push_back(edge);
        return edge;
    }

    std::vector<Obstacle*> getObstacles() { return m_obstacles; }
    std::vector<Vertex*> getVertices() { return m_vertices; }
    std::vector<Edge*> getPathEdges() { return m_pathEdges; }
    std::vector<Edge*> getEdges() { return m_edges; }

    Vertex* getStart() { return m_start; }
    Vertex* getGoal() { return m_goal; }

private:

    std::vector<Obstacle*> m_obstacles;
    std::vector<Vertex*> m_vertices;
    std::vector<Edge*> m_pathEdges;
    std::vector<Edge*> m_edges;

    Vertex* m_start;
    Vertex* m_goal;


    const Config m_config;
    int m_width;
    int m_height;

    std::mutex m_verticesMutex;
    std::mutex m_edgesMutex;
};

