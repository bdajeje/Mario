#include "player.hpp"

#include "managers/texture_manager.hpp"

#include <iostream>

namespace game {

Player::Player( const sf::Vector2f& size, const sf::Vector2f& position )
  : _sprites_move_right { "player/animations/move_right", size, position }
  , _sprites_move_left { "player/animations/move_left", size, position }
{
  _current_sprite_sequence = &_sprites_move_right;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( _current_sprite_sequence->currentSprite(), states );
}

void Player::setMovingTo(Direction direction)
{
  _moving_to_direction = direction;
  _body_direction = direction;
}

void Player::stopMoving()
{
  _moving_to_direction = Direction::None;
}

void Player::update(const sf::Time& elapsed_time)
{
  updateSpeed(elapsed_time);
}

bool Player::isMaxSpeedReached() const
{
  return std::abs(_horizontal_speed) > _max_speed;
}

void Player::updateSpeed(const sf::Time& elapsed_time)
{
  // Update speed
  if( isMoving() )
  {
    if(isMaxSpeedReached())
      return;

    // Speed gain depending on elapsed time
    float speed_gain = elapsed_time.asMilliseconds() * _acceleration;

    // Moving to left means minus speed
    if( _moving_to_direction == Direction::Left )
      speed_gain = -speed_gain;

    // Update speed
    _horizontal_speed += speed_gain;

    // Respect max speed
    if( std::abs(_horizontal_speed) > _max_speed )
      _horizontal_speed = ( _moving_to_direction == Direction::Left ) ? -_max_speed : _max_speed;
  }
  // Not moving, but remaining inertia
  else if( _horizontal_speed != 0.f )
  {
    // Speed loss depending on elapsed time
    float speed_loss = elapsed_time.asMilliseconds() * _deceleration;

    if( _horizontal_speed > 0.f )
    {
      _horizontal_speed -= speed_loss;
      if(_horizontal_speed < 0.f)
        _horizontal_speed = 0.f;
    }
    else if( _horizontal_speed < 0.f )
    {
      _horizontal_speed += speed_loss;
      if(_horizontal_speed > 0.f)
        _horizontal_speed = 0.f;
    }
  }
}

const sf::Vector2f& Player::getPosition() const
{
  return _current_sprite_sequence->getPosition();
}

void Player::setPosition(const sf::Vector2f& position)
{
  _sprites_move_left.setPosition(position);
  _sprites_move_right.setPosition(position);
}

void Player::setSize(float x, float y)
{
  _sprites_move_left.setSize(x, y);
  _sprites_move_right.setSize(x, y);
}

void Player::move(float x, float y)
{
  sf::Vector2f position = getPosition();
  position.x += x;
  position.y += y;
  setPosition( position );
}

sf::Vector2f Player::getSize() const
{
  _current_sprite_sequence->getSize();
}

sf::Vector2f Player::getCenter() const
{
  sf::Vector2f size = getSize();
  size.x /= 2;
  size.y /= 2;
  return getPosition() + size;
}

void Player::resetMovement()
{
  stopMoving();
  _horizontal_speed = 0.f;
}

} // namespace game
