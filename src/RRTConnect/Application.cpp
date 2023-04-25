#include "RRTConnect/Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <chrono>
#include <thread>


Application::Application(const Config& config)
: m_config(config), m_context(config)
{
    m_grid = new Grid(m_config);
    m_renderer = new Renderer(m_config, &m_context, m_grid);

    generateObstacles();
    generateStartingPoint();
    generateGoalPoint();
    //generateEdges();

    m_solver = new SolverRRTConnect(m_grid, &m_config);
    m_solverThread = nullptr;
    
}

void Application::generateObstacles()
{
    // External frame
    for (size_t i = 0; i < 60; ++i) {
        if (i < 45)
            m_grid->addObstacle(0, i);

        if (i != 0)
        {
            m_grid->addObstacle(i, 0);
            if (i < 45)
                m_grid->addObstacle(59, i);

            if (i != 59)
                m_grid->addObstacle(i, 44);
        }
    }


    // Internal frame
    for (size_t x = 9; x < 11; ++x) {
        for (size_t y = 1; y < 24; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 15; x < 30; ++x) {
        for (size_t y = 26; y < 39; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 22; x < 31; ++x) {
        for (size_t y = 9; y < 20; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 37; x < 39; ++x) {
        for (size_t y = 12; y < 35; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 45; x < 52; ++x) {
        for (size_t y = 1; y < 13; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 47; x < 59; ++x) {
        for (size_t y = 25; y < 27; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 51; x < 53; ++x) {
        for (size_t y = 37; y < 44; ++y) {
            m_grid->addObstacle(x, y);
        }
    }

    for (size_t x = 6; x < 15; ++x) {
        for (size_t y = 32; y < 34; ++y) {
            m_grid->addObstacle(x, y);
        }
    }
}

void Application::generateStartingPoint()
{
    m_grid->addStartingPoint(80, 94);
}

void Application::generateGoalPoint()
{
    m_grid->addGoalPoint(54*32.f, 41*32.f);
}

void Application::generateEdges()
{
    Vertex* vertex1 = m_grid->addVertex(250, 800);
    m_grid->addEdge(m_grid->getStart(), vertex1);
    Vertex* vertex2 = m_grid->addVertex(1400, 750);
    m_grid->addEdge(vertex1, vertex2);
    m_grid->addEdge(vertex2, m_grid->getGoal());
}

void Application::playingLoop()
{
    /*sf::RenderWindow* renderer = new sf::RenderWindow(sf::VideoMode(1600, 900), "Spoofy");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));*/
    sf::Clock dtTimer;
    sf::Clock dt;

    sf::Time m;

    while (m_context.window.isOpen()/* && !m_states.empty()*/) {
        //auto deltaTime = dtTimer.restart();
        //auto &state = *m_states.back();

        if (!m_solverThread) {
            m_solverThread = new std::thread(&SolverRRTConnect::solve, m_solver);
        }
        /*state.handleInput();
        state.update(deltaTime.asSeconds());
        m_camera.update();*/

        //state.render(m_masterRenderer);
        //m_masterRenderer.finishRender(m_context.window, m_camera);

        handleEvents();
        /*if (m_isPopState) {
            m_isPopState = false;
            m_states.pop_back();
        }*/
        m_renderer->render();

        m = dt.restart();

        //g_timeElapsed += m.asSeconds();
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (m_context.window.pollEvent(e)) {
        //m_states.back()->handleEvent(e);
        switch (e.type) {
            case sf::Event::Closed:
                m_context.window.close();
                break;

            case sf::Event::KeyPressed:
                switch (e.key.code) {
                    case sf::Keyboard::Escape:
                        m_context.window.close();
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}
