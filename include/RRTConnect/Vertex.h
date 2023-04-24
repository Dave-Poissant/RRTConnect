#pragma once

#include <SFML/Graphics/CircleShape.hpp>

class Vertex
{
public:

    Vertex(int xGridPos, int yGridPos)
    : Vertex(xGridPos, yGridPos, false, false)
    {}

    Vertex(int xGridPos, int yGridPos, bool isStartingPoint, bool isGoalPoint)
    : Vertex(xGridPos, yGridPos, 14.f, 4.f, isStartingPoint, isGoalPoint)
    {}

    Vertex(int xGridPos, int yGridPos, float radius, float outlineWidth, bool isStartingPoint, bool isGoalPoint)
    : m_xGridPos(xGridPos), m_yGridPos(yGridPos), m_radius(radius), m_outlineWidth(outlineWidth),
    m_isStartingPoint(isStartingPoint), m_isGoalPoint(isGoalPoint)
    {
        m_circle = new sf::CircleShape(m_radius);

        if (m_isStartingPoint && !m_isGoalPoint)
        {
            // Set color to blue
            m_circle->setFillColor(sf::Color(0, 0, 255));
        }
        else if (!m_isStartingPoint && m_isGoalPoint)
        {
            // Set color to red
            m_circle->setFillColor(sf::Color(255, 0, 0));
        }
        else
        {
            // Set color to black
            m_circle->setFillColor(sf::Color(0, 0, 0));
        }
        
        // set a 4-pixel wide black outline
        m_circle->setOutlineThickness(m_outlineWidth);
        m_circle->setOutlineColor(sf::Color(0, 0, 0));

        // Set pos in grid
        m_circle->setPosition(sf::Vector2f((m_xGridPos*m_radius*2) + (m_xGridPos*m_outlineWidth), (m_yGridPos*m_radius*2) + (m_yGridPos*m_outlineWidth)));
    }

    ~Vertex();

    sf::CircleShape* getVertex() { return m_circle; }

private:

    sf::CircleShape* m_circle;
    int m_xGridPos;
    int m_yGridPos;

    float m_radius;
    float m_outlineWidth;

    bool m_isStartingPoint;
    bool m_isGoalPoint;

};

