#pragma once

#include "RRTConnect/CollisionGeometry.h"

#include <SFML/Graphics/CircleShape.hpp>

class Vertex
{
public:

    Vertex(CollisionGeometry collisionGeometry, sf::CircleShape* circle)
    : m_circle(circle), m_collisionGeometry(collisionGeometry)
    {
        m_circle->setPosition(sf::Vector2f(m_collisionGeometry.x(), m_collisionGeometry.y()));
    }

    ~Vertex()
    {
        delete m_circle;
    }

    sf::CircleShape* getVertex() { return m_circle; }

    bool operator==(const Vertex& other) const { return (this->m_collisionGeometry==other.m_collisionGeometry); }

    float x() const { return m_collisionGeometry.x(); }

    float y()const { return m_collisionGeometry.y(); }

    float w() const { return m_collisionGeometry.w(); }

    float h() const { return m_collisionGeometry.h(); }

private:

    sf::CircleShape* m_circle;
    CollisionGeometry m_collisionGeometry;

};

