#include "player.hpp"

#include "managers/texture_manager.hpp"

namespace game {

Player::Player()
  : _animation_move_right { "player/animations/move_right" }
  , _animation_move_left { "player/animations/move_left" }
  , _animations { &_animation_move_left, &_animation_move_right }
{
  _current_animation = &_animation_move_right;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( *_current_animation, states );
}

void Player::setPosition(const sf::Vector2f& position)
{
  for( auto* animation : _animations )
    animation->setPosition(position);
}

void Player::setSize(float x, float y)
{
  for( auto* animation : _animations )
    animation->setSize(x, y);
}

} // namespace game
