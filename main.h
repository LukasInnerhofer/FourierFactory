#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <map>
#include <string>

#include "Button.h"

std::map<std::string, sf::Button *> initButtons();
void drawBackground(sf::RenderWindow &window);

#endif // MAIN_H