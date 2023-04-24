#pragma once

#include <iostream>

#include "RRTConnect/Config.h"
#include "RRTConnect/Context.h"
#include "RRTConnect/Renderer.h"
#include "RRTConnect/Grid.h"


class Application
{
public:
    Application(const Config& config);


    void playingLoop();

private:

    void handleEvents();
    void generateObstacles();
    void generateStartingPoint();
    void generateGoalPoint();
    void generateEdges();

    const Config m_config;
    Context m_context;
    Renderer* m_renderer;
    Grid* m_grid;

};
