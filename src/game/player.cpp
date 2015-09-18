#include "player.hpp"

#include "managers/texture_manager.hpp"

namespace game {

Player::Player( const sf::Vector2f& size )
  : _animation_move_right { "player/animations/move_right" }
  , _animation_move_left { "player/animations/move_left" }
  , _animations { &_animation_move_left, &_animation_move_right }
{
  _current_animation = &_animation_move_right;

  _view.setSize(size);
  _view.setCenter(0, 0);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.setView(_view);
  target.draw( _current_animation->drawable(), states );
  target.setView( target.getDefaultView() );
}

void Player::setPosition(const sf::Vector2f& position)
{
  // \todo
}

void Player::setSize(float x, float y)
{
  _view.setSize(x, y);
}

void Player::setMovingTo(Direction direction)
{
  _is_moving = true;
  _direction = direction;
}

void Player::stopMoving()
{
  _is_moving = false;
}

void Player::update(const sf::Time& elapsed_time)
{

}

const sf::Vector2f& Player::getPosition() const
{
  return _view.getCenter();
}

} // namespace game
