#include "hud.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "managers/font_manager.hpp"

namespace game {

HUD::HUD(const sf::Vector2u& size)
  : _size { size }
{
  game::TextProperty text_properties { "", "consolas.ttf", sf::Color::Red, 20 };
  text_properties.create( _text_elapsed_time, text_properties );
  text_properties.create( _text_score, text_properties );

  setScore(0);
  setTime(0.f);

  updateTextPositions();

  const size_t countdown_time {3};
  _countdown_animations.reserve(countdown_time);
  text_properties.size = 5;
  for( size_t i = countdown_time; i > 0; --i )
  {
    text_properties.text = std::to_string(i);
    _countdown_animations.emplace_back( text_properties, std::chrono::milliseconds(1000), 30 );
  }
}

void HUD::updateTextPositions()
{
  static const unsigned int padding {10};
  _text_elapsed_time.setPosition( _position.x + padding, _position.y + padding );
  _text_score.setPosition( _position.x + _size.x - _text_score.getGlobalBounds().width - padding,
                           _position.y + padding );
}

void HUD::setPosition(const sf::Vector2f& position)
{
  _position = position;
  updateTextPositions();
}

void HUD::setSize(float x, float y)
{
  if( x == _size.x && y == _size.y )
    return;

  _size.x = x;
  _size.y = y;

  updateTextPositions();
}

void HUD::setScore(unsigned int score)
{
  _text_score.setString( "Score: " + std::to_string(score) );
}

void HUD::setTime(float time)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(1) << time;

  _text_elapsed_time.setString( "Time: " + stream.str() );
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( _text_elapsed_time, states );
  target.draw( _text_score, states );
  drawCountdown(target, states);
}

void HUD::drawCountdown(sf::RenderTarget& target, sf::RenderStates states) const
{
  if( _countdown_offset >= _countdown_animations.size() )
    return;

  target.draw( _countdown_animations[_countdown_offset].drawable(), states );
}

void HUD::update(const sf::Time& elapsed_time)
{
  updateCountdown( elapsed_time );
}

void HUD::updateCountdown(const sf::Time& elapsed_time)
{
  if( _countdown_offset >= _countdown_animations.size() )
    return;

  animation::ZoomTextAnimation& animation = _countdown_animations[_countdown_offset];
  animation.update(elapsed_time);
  if(animation.finished())
    _countdown_offset++;
}

}
