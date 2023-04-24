#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Edge
{
public:

    Edge(int xGridPos, int yGridPos, int nextXGridPos, int nextYGridPos)
    : m_xGridPos(xGridPos), m_yGridPos(yGridPos), m_nextXGridPos(nextXGridPos), m_nextYGridPos(nextYGridPos)
    {
        m_line[0] = sf::Vertex(sf::Vector2f(m_xGridPos*32.f, m_yGridPos*32.f));
        m_line[1] = sf::Vertex(sf::Vector2f(m_nextXGridPos*32.f, m_nextXGridPos*32.f));

        // Set color to black
        m_line[0].color = sf::Color(255, 255, 255);
        m_line[1].color = sf::Color(255, 255, 255);
    }
    
    ~Edge();

    sf::Vertex* getEdge() { return m_line; }

private:

    sf::Vertex m_line[2];
    int m_xGridPos;
    int m_yGridPos;
    int m_nextXGridPos;
    int m_nextYGridPos;

};

