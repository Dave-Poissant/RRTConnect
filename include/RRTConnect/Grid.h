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

    std::vector<Obstacle*> getObstacles() { return m_obstacles; }

private:

    std::vector<Obstacle*> m_obstacles;
    std::vector<Vertex*> m_vertices;
    std::vector<Edge*> m_edges;


    const Config m_config;
    int m_width;
    int m_height;
};

