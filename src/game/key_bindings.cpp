#include "key_bindings.hpp"

namespace game {

const std::map<Action, sf::Keyboard::Key> KeyBindings::_action_to_key = {
  { Action::MoveLeft, sf::Keyboard::Left },
  { Action::MoveRight, sf::Keyboard::Right },
  { Action::MoveUp, sf::Keyboard::Up },
  { Action::MoveDown, sf::Keyboard::Down }
};

sf::Keyboard::Key KeyBindings::get(Action action)
{
  return _action_to_key.find(action)->second;
}

}
