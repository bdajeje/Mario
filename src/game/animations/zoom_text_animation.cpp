#include "zoom_text_animation.hpp"

namespace animation {

ZoomTextAnimation::ZoomTextAnimation(const std::shared_ptr<sf::Text>& target, std::chrono::milliseconds duration, unsigned int to_size)
  : TextAnimation { duration, target }
  , _to_size {to_size}
{}

void ZoomTextAnimation::update(const sf::Time& /*elapsed_time*/)
{
  if( !_text )
    return;

  // Save bounds before resizing
  const sf::FloatRect old_bounds = _text->getGlobalBounds();

  // Update character size
  const unsigned int new_size = _clock.getElapsedTime().asMilliseconds() * _to_size / _duration;
  _text->setCharacterSize(new_size);

  // Get new bounds
  const sf::FloatRect new_bounds = _text->getGlobalBounds();

  // Replace text correctly because of resizing
  _text->move( (old_bounds.width - new_bounds.width) / 2,
               (old_bounds.height - new_bounds.height) );
}

}
