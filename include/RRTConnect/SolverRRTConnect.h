#pragma once

#include "RRTConnect/Grid.h"
#include "RRTConnect/Config.h"

#include <unordered_set>


class SolverRRTConnect
{
public:
    SolverRRTConnect(Grid* grid, const Config* config);

    ~SolverRRTConnect();

    bool solve();

    bool isSolving() const { return m_solving; }

private:
    
    bool isGoalReached();
    int grid2Index(int x, int y);
    void index2Grid(int i, int& x, int& y);
    Vertex* findNearestNode(std::unordered_set<Vertex, VertexIdAsHash, CompareCoordinates> list, Vertex* qNew);
    Vertex* createRandomNode();
    bool isObstacleBetween(Vertex* qNear, Vertex* qNew);
    bool isInObstacle(Vertex* qNew);

    Grid* m_grid;
    const Config* m_config;

    std::unordered_set<Vertex, VertexIdAsHash, CompareCoordinates> sampleListFront;
    std::unordered_set<Vertex, VertexIdAsHash, CompareCoordinates> sampleListBack;

    bool m_existingPath;
    bool m_solved;
    bool m_solving;

};

