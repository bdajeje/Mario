#include "game.hpp"

namespace game {

Game::Game(sf::RenderWindow& window, std::string map_folder)
  :  _window { window }
  , _map  { _window.getSize(), map_folder }
  , _hud { window.getSize() }
  , _menu { window.getSize(), {0,0} } // \todo set menu correct size and position
  , _keyboard_event_handler {&_map}
{}

void Game::run()
{
  sf::Time last_update {sf::Time::Zero};
  _timer.start();

  while(_window.isOpen())
  {
    sf::Event event;
    while(_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
        {
          _window.close();
          break;
        }
        case sf::Event::KeyPressed:
        {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            toggleMenu();
          else
            _keyboard_event_handler->handleKeyboardEvent(event);
        }
      }
    }

    if( isRunning() )
    {
      // Get elapsed time since last update
      const sf::Time elapsed_time = _timer.getElapsedTime() - last_update;

      // Update objects
      _hud.setTime( _timer.getElapsedTime().asSeconds() );
      _map.update( elapsed_time );

      // Save last update time
      last_update = _timer.getElapsedTime();
    }

    // Draw everything
    draw();
  }
}

void Game::draw()
{
  _window.clear();

  _window.draw(_map);
  _window.draw(_hud);

  if( _state == State::Menu )
    _window.draw(_menu);

  _window.display();
}

bool Game::isRunning() const
{
  return _state == State::Running;
}

void Game::toggleMenu()
{
  if( isRunning() )
  {
    _state = State::Menu;
    _timer.pause();
    _keyboard_event_handler = &_menu;
  }
  else
  {
    _state = State::Running;
    _timer.start();
    _keyboard_event_handler = &_map;
  }
}

}
