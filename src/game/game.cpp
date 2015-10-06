#include "game.hpp"

namespace game {

Game::Game(sf::RenderWindow& window, std::string map_folder)
  :  _window { window }
  , _map  { _window.getSize(), map_folder }
  , _hud { window.getSize() }
  , _menu { window.getSize(), {0,0} } // \todo set menu correct size and position
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
//          else if(_keyboard_event_handler)
//            _keyboard_event_handler->handleKeyboardEvent(event);
        }
      }
    }

    // Get elapsed time since last update
    const sf::Time elapsed_time = _timer.getElapsedTime() - last_update;

    switch( _state )
    {
      case State::StartAnimation:
      {
        _hud.update(elapsed_time);

        // Start animation finished? Start the game
        if(!_hud.isInStartAnimation())
          startGame();

        break;
      }
      case State::Running:
      {
        // Update objects
        _hud.setTime( _timer.getElapsedTime().asSeconds() );
        _map.update( elapsed_time );
      }
    }

    // Save last update time
    last_update = _timer.getElapsedTime();

    // Draw everything
    draw();
  }
}

void Game::startGame()
{
  _timer.restart();
  _state = State::Running;
  //_keyboard_event_handler = &_map;
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

bool Game::isInStartAnimation() const
{
  return _state == State::StartAnimation;
}

void Game::toggleMenu()
{
  if( isRunning() || isInStartAnimation() )
  {
    _state = State::Menu;
    _timer.pause();
    //_keyboard_event_handler = &_menu;
  }
  else
  {
    _state = (_hud.isInStartAnimation()) ? State::StartAnimation : State::Running;
    _timer.start();
    //_keyboard_event_handler = &_map;
  }
}

}
