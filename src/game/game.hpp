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
  Running, Menu, StartAnimation
};

class Game final
{
  public:

    Game(sf::RenderWindow& window, std::string map_folder);

    void run();

    bool isRunning() const;
    bool isInStartAnimation() const;

  private:

    void draw();
    void toggleMenu();
    void startGame();

  private:

    State _state { State::StartAnimation };
    sf::RenderWindow& _window;
    Map _map;
    HUD _hud;
    Menu _menu;
    unsigned int _score {0};
    utils::time::Timer _timer;

    /*! How's responsible for handling keyboard events */
    //event::KeywordEventHandler* _keyboard_event_handler {nullptr};
};

}

#endif // GAME_HPP
