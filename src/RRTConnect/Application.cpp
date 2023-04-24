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
}

void Application::generateObstacles()
{
    m_grid->addObstacle(0, 0);
    m_grid->addObstacle(0, 1);
}

void Application::playingLoop()
{
    /*sf::RenderWindow* renderer = new sf::RenderWindow(sf::VideoMode(1600, 900), "Spoofy");
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));*/
    sf::Clock dtTimer;
    sf::Clock dt;

    sf::Time m;

    while (m_context.window.isOpen()/* && !m_states.empty()*/) {
        auto deltaTime = dtTimer.restart();
        //auto &state = *m_states.back();

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
