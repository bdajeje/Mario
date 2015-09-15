#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "utils/configuration/configuration.hpp"
#include "utils/logging/easylogging++.h"
#include "game/map.hpp"
#include "game/player.hpp"
#include "managers/texture_manager.hpp"

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
  game::PlayerPtr player {new game::Player};
  game::Map map { {window_width, window_height}, "resources/map/1", player };

  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(map);
    window.display();
  }

  return EXIT_SUCCESS;
}

