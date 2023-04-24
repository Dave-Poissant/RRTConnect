#pragma once

#include "RRTConnect/Config.h"

#include "RRTConnect/Obstacle.h"
#include "RRTConnect/Vertex.h"
#include "RRTConnect/Edge.h"

#include <vector>

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
    {}

    void addObstacle(int xGridPos, int yGridPos)
    {
        m_obstacles.push_back(new Obstacle(xGridPos, yGridPos));
    }

    void addStartingPoint(int xGridPos, int yGridPos)
    {
        m_start = new Vertex(xGridPos, yGridPos, true, false);
        m_vertices.push_back(m_start);
    }

    void addGoalPoint(int xGridPos, int yGridPos)
    {
        m_goal = new Vertex(xGridPos, yGridPos, false, true);
        m_vertices.push_back(m_goal);
    }

    void addVertex(int xGridPos, int yGridPos)
    {
        m_vertices.push_back(new Vertex(xGridPos, yGridPos));
    }

    void addEdge(int xGridPos, int yGridPos, int nextXGridPos, int nextYGridPos)
    {
        m_edges.push_back(new Edge(xGridPos, yGridPos, nextXGridPos, nextYGridPos));
    }

    std::vector<Obstacle*> getObstacles() { return m_obstacles; }
    std::vector<Vertex*> getVertices() { return m_vertices; }
    std::vector<Edge*> getEdges() { return m_edges; }

private:

    std::vector<Obstacle*> m_obstacles;
    std::vector<Vertex*> m_vertices;
    std::vector<Edge*> m_edges;

    Vertex* m_start;
    Vertex* m_goal;


    const Config m_config;
    int m_width;
    int m_height;
};

