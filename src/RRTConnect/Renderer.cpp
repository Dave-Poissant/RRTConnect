#include "RRTConnect/Renderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>

Renderer::Renderer(const Config& config, Context* context, Grid* grid)
: m_config(config), m_context(context), m_grid(grid)
{}

Renderer::~Renderer()
{}

void Renderer::render()
{
    m_context->window.clear(sf::Color(128, 128, 128));

    renderObstacles();
    m_context->window.display();
}

void Renderer::renderObstacles()
{
    for (size_t i = 0; i < m_grid->getObstacles().size(); i++)
    {
        m_context->window.draw(*(m_grid->getObstacles().at(i)->getObstacle()));
    }
}