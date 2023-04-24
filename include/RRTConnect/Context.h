#pragma once

#include <SFML/Graphics.hpp>

#include "Config.h"

struct Context {
    Context(const Config &config);

    sf::RenderWindow window;
};
