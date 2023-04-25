#pragma once

#include <iostream>
#include <mutex>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class ShapeFactory
{
public:

    static sf::CircleShape* createStartingPointShape()
    {
        sf::CircleShape* circle = new sf::CircleShape(16.f);
        circle->setFillColor(sf::Color::Blue);
        circle->setOutlineThickness(-2.f);
        return circle;
    }

    static sf::CircleShape* createGoalPointShape()
    {
        sf::CircleShape* circle = new sf::CircleShape(16.f);
        circle->setFillColor(sf::Color::Red);
        circle->setOutlineThickness(-2.f);
        return circle;
    }

    static sf::CircleShape* createVertexShape()
    {
        sf::CircleShape* circle = new sf::CircleShape(8.f);
        circle->setFillColor(sf::Color::Black);
        circle->setOutlineThickness(-2.f);
        circle->setOutlineColor(sf::Color::Black);
        return circle;
    }
};

