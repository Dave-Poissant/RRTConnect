#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Edge
{
public:

    Edge(Vertex* vertex1, Vertex* vertex2)
    {
        m_line[0] = sf::Vertex(sf::Vector2f(vertex1->x()+(vertex1->w()/2.f), vertex1->y()+(vertex1->h()/2.f)));
        m_line[1] = sf::Vertex(sf::Vector2f(vertex2->x()+(vertex2->w()/2.f), vertex2->y()+(vertex2->h()/2.f)));

        // Set color to black
        m_line[0].color = sf::Color::Black;
        m_line[1].color = sf::Color::Black;
    }
    
    ~Edge()
    {}

    void setColor(sf::Color color)
    {
        m_line[0].color = color;
        m_line[1].color = color;
    }

    sf::Vertex* getEdge() { return m_line; }

private:

    sf::Vertex m_line[2];

};

