#pragma once

#include <iostream>

#include "RRTConnect/Config.h"
#include "RRTConnect/Context.h"
#include "RRTConnect/Grid.h"


class Renderer
{
public:
    Renderer(const Config& config,  Context* context, Grid* grid);
    ~Renderer();

    void render();

private:

    void renderObstacles();
    void renderVertices();
    void renderEdges();

    const Config m_config;
    Context* m_context;
    Grid* m_grid;

};
