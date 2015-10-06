#include "hud.hpp"

#include "managers/font_manager.hpp"
#include "managers/sound_manager.hpp"
#include "utils/utils.hpp"

namespace game {

HUD::HUD(const sf::Vector2u& size)
  : _size { size }
  , _text_countdown {new sf::Text}
{
  game::TextProperty text_properties { "", "consolas.ttf", sf::Color::White, 20 };
  text_properties.create( _text_elapsed_time, text_properties );
  text_properties.create( _text_score, text_properties );
  text_properties.create( *_text_countdown, text_properties );

  setScore(0);
  setTime(0.f);

  static const unsigned int padding {10};
  _text_elapsed_time.setPosition( _position.x + padding, _position.y + padding );
  _text_score.setPosition( _position.x + _size.x - _text_score.getGlobalBounds().width - padding,
                           _position.y + padding );

  _beep_sound.setBuffer( sound::SoundManager::get("beep.wav") );
  _beep_sound.play();

  setCountdownText( _secs_before_start );
  startCountdownAnimation();
}

void HUD::setCountdownText(short value)
{
  _text_countdown->setCharacterSize( 5 );
  _text_countdown->setString( std::to_string(value) );
  _text_countdown->setPosition( (_size.x - _text_countdown->getGlobalBounds().width) / 2,
                                (_size.y - _text_countdown->getGlobalBounds().height) / 2 );
}

void HUD::startCountdownAnimation()
{
  _countdown_animation.reset( new animation::ZoomTextAnimation( _text_countdown, std::chrono::milliseconds(1000), 100 ) );
}

void HUD::setScore(unsigned int score)
{
  _text_score.setString( "Score: " + std::to_string(score) );
}

void HUD::setTime(float time)
{
  _text_elapsed_time.setString( "Time: " + utils::string::convert(time, 1) );
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( _text_elapsed_time, states );
  target.draw( _text_score, states );

  if( _text_countdown )
    target.draw( *_text_countdown, states );
}

void HUD::update(const sf::Time& elapsed_time)
{
  if(_countdown_animation)
  {
    // Update countdown animation
    _countdown_animation->update( elapsed_time );

    // Current animation finished? Apply next one
    if( _countdown_animation->finished() )
    {
      const int countdown = std::stoi(_text_countdown->getString().toAnsiString()) - 1;
      if(countdown == 0)
      {
        _countdown_animation.reset();
        _text_countdown.reset();
        _beep_sound.setBuffer( sound::SoundManager::get("beep_start.wav") );
        _beep_sound.play();
      }
      else
      {
        setCountdownText( countdown );
        startCountdownAnimation();
        _beep_sound.play();
      }
    }
  }
}

}
