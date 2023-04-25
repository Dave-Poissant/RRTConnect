#include "RRTConnect/Renderer.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>

Renderer::Renderer(const Config& config, Context* context, Grid* grid)
: m_config(config), m_context(context), m_grid(grid)
{}

Renderer::~Renderer()
{
    delete m_grid;
    delete m_context;
}

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
    for (auto obstacle : m_grid->getObstacles())
    {
        m_context->window.draw(*(obstacle->getObstacle()));
    }
}

void Renderer::renderVertices()
{
    for (auto vertex : m_grid->getVertices())
    {
        m_context->window.draw(*(vertex->getVertex()));
    }
}

void Renderer::renderEdges()
{
    for (auto edge : m_grid->getEdges())
    {
        m_context->window.draw(edge->getEdge(), 2, sf::Lines);
    }
}