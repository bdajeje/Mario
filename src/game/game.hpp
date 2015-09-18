#ifndef GAME_HPP
#define GAME_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "game/map.hpp"
#include "game/hud.hpp"
#include "game/menu.hpp"
#include "utils/time/timer.hpp"

namespace game {

enum class State {
  Running, Menu
};

class Game final
{
  public:

    Game(sf::RenderWindow& window, std::string map_folder);

    void run();

    bool isRunning() const;

  private:

    void draw();
    void toggleMenu();

  private:

    State _state { State::Running };
    sf::RenderWindow& _window;
    Map _map;
    HUD _hud;
    Menu _menu;
    unsigned int _score {0};
    utils::time::Timer _timer;

    /*! How's responsible for handling keyboard events */
    event::KeywordEventHandler* _keyboard_event_handler;
};

}

#endif // GAME_HPP
