#pragma once

#include "RRTConnect/Grid.h"
#include "RRTConnect/Config.h"


class SolverRRTConnect
{
public:
    SolverRRTConnect(Grid* grid, const Config* config);

    ~SolverRRTConnect();

    void solve();

    bool isSolving() const { return m_solving; }

private:
    
    bool isGoalReached();
    Vertex* findNearestNode(Vertex* qNew);
    Vertex* createRandomNode();
    bool isObstacleBetween(Vertex* qNear, Vertex* qNew);
    bool isInObstacle(Vertex* qNew);

    Grid* m_grid;
    const Config* m_config;

    bool m_existingPath;
    bool m_solved;
    bool m_solving;

};

