#pragma once

#include <SFML/Graphics/RectangleShape.hpp>



class Obstacle
{
public:

    Obstacle(int xGridPos, int yGridPos)
    : m_xGridPos(xGridPos), m_yGridPos(yGridPos), m_width(28.f), m_height(28.f), m_outlineWidth(4.f)
    {
        m_rectangle = new sf::RectangleShape(sf::Vector2f(m_width, m_width));

        // Set color to green
        m_rectangle->setFillColor(sf::Color(100, 250, 50));
        // set a 4-pixel wide black outline
        m_rectangle->setOutlineThickness(m_outlineWidth);
        m_rectangle->setOutlineColor(sf::Color(0, 0, 0));

        // Set pos in grid
        m_rectangle->setPosition(sf::Vector2f((m_xGridPos*m_width) + (m_xGridPos*m_outlineWidth), (m_yGridPos*m_height) + (m_yGridPos*m_outlineWidth)));
    }

    ~Obstacle()
    {
        if (m_rectangle)
            delete m_rectangle;
    }

    sf::RectangleShape* getObstacle() { return m_rectangle; }

private:

    sf::RectangleShape* m_rectangle;
    int m_xGridPos;
    int m_yGridPos;
    float m_width;
    float m_height;
    float m_outlineWidth;

};

