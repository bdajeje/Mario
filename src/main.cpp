#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "utils/configuration/configuration.hpp"
#include "utils/logging/easylogging++.h"
#include "managers/texture_manager.hpp"
#include "managers/font_manager.hpp"
#include "game/game.hpp"

_INITIALIZE_EASYLOGGINGPP

int main()
{
  // Read configuration file
  utils::Configuration configurations { "resources/game.conf" };

  const unsigned int window_width  = configurations.get<unsigned int>("window_width");
  const unsigned int window_height = configurations.get<unsigned int>("window_height");
  sf::RenderWindow window(sf::VideoMode(window_width, window_height),
                          configurations.get<std::string>("window_title"));
  window.setFramerateLimit(60);

  texture::TextureManager::init("resources/textures/");
  font::FontManager::init("resources/fonts/");

  game::Game game {window, "resources/map/1"};
  game.run();

  return EXIT_SUCCESS;
}

