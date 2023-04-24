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
    renderVertices();
    renderEdges();
    m_context->window.display();
}

void Renderer::renderObstacles()
{
    for (size_t i = 0; i < m_grid->getObstacles().size(); i++)
    {
        m_context->window.draw(*(m_grid->getObstacles().at(i)->getObstacle()));
    }
}

void Renderer::renderVertices()
{
    for (size_t i = 0; i < m_grid->getVertices().size(); i++)
    {
        m_context->window.draw(*(m_grid->getVertices().at(i)->getVertex()));
    }
}

void Renderer::renderEdges()
{
    for (size_t i = 0; i < m_grid->getEdges().size(); i++)
    {
        m_context->window.draw(m_grid->getEdges().at(i)->getEdge(), 2, sf::Lines);
    }
}