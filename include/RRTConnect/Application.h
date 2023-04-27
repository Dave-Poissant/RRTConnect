#pragma once

#include <iostream>
#include <thread>

#include "RRTConnect/Config.h"
#include "RRTConnect/Context.h"
#include "RRTConnect/Renderer.h"
#include "RRTConnect/SolverRRTConnect.h"


class Application
{
public:
    Application(const Config& config);
    

    void playingLoop();
    Grid* getGrid() { return m_grid; }

private:

    void handleEvents();
    void generateObstacles();
    void generateStartingPoint();
    void generateGoalPoint();

    const Config m_config;
    Context m_context;
    Renderer* m_renderer;
    Grid* m_grid;

    SolverRRTConnect* m_solver;
    std::thread* m_solverThread;

};
