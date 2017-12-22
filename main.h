#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <map>
#include <string>

#include "Button.h"
#include "LineShape.h"
#include "List.h"

#define ANGULAR_FREQUENCY 1

std::map<std::string, sf::Button *> initButtons();
void drawBackground(sf::RenderWindow &window);
inline sf::Vector2f vectorDiagramOrigin(const sf::Vector2u &windowSize) { return { windowSize.x / 4.0f, (windowSize.y - 60) / 2.0f }; }
inline sf::Vector2f lineDiagramOrigin(const sf::Vector2u &windowSize) { return { (windowSize.x / 2.0f) + 10, (windowSize.y - 50) / 2.0f }; }

#endif // MAIN_H