#ifndef KEYBINDINGS_HPP
#define KEYBINDINGS_HPP

#include <map>

#include <SFML/Window/Keyboard.hpp>

#include "game/actions.hpp"

namespace game {

class KeyBindings
{
  public:

    static sf::Keyboard::Key get(Action action);

  private:

    KeyBindings();

  private:

    static const std::map<Action, sf::Keyboard::Key> _action_to_key;
};

}

#endif // KEYBINDINGS_HPP
