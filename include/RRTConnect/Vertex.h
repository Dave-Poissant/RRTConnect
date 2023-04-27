#pragma once

#include "RRTConnect/CollisionGeometry.h"
#include "RRTConnect/ShapeFactory.h"

#include <SFML/Graphics/CircleShape.hpp>

class Vertex
{
public:

    Vertex()
    : m_circle(ShapeFactory::createVertexShape()), m_collisionGeometry(sf::Vector2f(0,0), sf::Vector2f(0,0)), m_id(0), m_parentId(0)
    {}

    Vertex(CollisionGeometry collisionGeometry, sf::CircleShape* circle)
    : m_circle(circle), m_collisionGeometry(collisionGeometry), m_id(0), m_parentId(0)
    {
        m_circle->setPosition(sf::Vector2f(m_collisionGeometry.x(), m_collisionGeometry.y()));
    }

    ~Vertex()
    {}

    sf::CircleShape* getVertex() { return m_circle; }

    bool operator==(const Vertex& other) const { return (this->m_collisionGeometry==other.m_collisionGeometry); }

    float x() const { return m_collisionGeometry.x(); }

    float y()const { return m_collisionGeometry.y(); }

    float w() const { return m_collisionGeometry.w(); }

    float h() const { return m_collisionGeometry.h(); }

private:

    sf::CircleShape* m_circle;

public:
    CollisionGeometry m_collisionGeometry;
    int m_id;
    int m_parentId;

};

class VertexIdAsHash
{
public:
    size_t operator()(const Vertex& n) const
    {
        return n.m_id;
    }
};

struct CompareCoordinates
{
    bool operator()(const Vertex& n1, const Vertex& n2) const
    {
        return n1 == n2;
    }
};
