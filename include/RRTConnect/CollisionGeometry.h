#pragma once

#include <SFML/System/Vector2.hpp>

#include <iostream>

class CollisionGeometry
{
public:

    CollisionGeometry(sf::Vector2f position, sf::Vector2f size)
    : m_position(position), m_size(size)
    {}

    ~CollisionGeometry()
    {}

    bool operator==(const CollisionGeometry& other) const
    {
        return (this->x() < other.x() + other.w() &&
        this->x() + this->w() > other.x() &&
        this->y() < other.y() + other.h() &&
        this->y() + this->h() > other.y());
    }

    bool isPointInside(sf::Vector2f point)
    {
        return (point.x >= m_position.x && point.x <= m_position.x + m_size.x &&
        point.y >= m_position.y && point.y <= m_position.y + m_size.y);
    }

    float x() const
    {
        return m_position.x;
    }

    float y()const
    {
        return m_position.y;
    }

    float w() const
    {
        return m_size.x;
    }

    float h() const
    {
        return m_size.y;
    }

public:

    sf::Vector2f m_position;
    sf::Vector2f m_size;

};