#ifndef MAIN_H
#define MAIN_H

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <chrono>
#include <fstream>
#include <map>
#include <string>
#include <thread>

#include "Button.h"
#include "LineShape.h"
#include "List.h"

#define ANGULAR_FREQUENCY	1
#define FPS_GOAL			60

/// <ui>
#define TOOLBAR_HEIGHT		40

inline sf::Vector2f vectorDiagramOrigin(const sf::Vector2u &windowSize) { return { windowSize.x / 4.0f, (windowSize.y - 40) / 2.0f + 40 }; }
inline sf::Vector2f vectorDiagramSize(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f - 20, windowSize.y - 60.0f }; }
inline sf::Vector2f lineDiagramOrigin(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f + 20, (windowSize.y - 40) / 2.0f + 40 }; }
inline sf::Vector2f lineDiagramSize(const sf::Vector2u &windowSize) { return { windowSize.x / 2.0f - 20, windowSize.y - 60.0f }; }
/// </ui>

std::map<std::string, sf::Button *> initButtons();
void drawBackground(sf::RenderWindow &window);

#endif // MAIN_H