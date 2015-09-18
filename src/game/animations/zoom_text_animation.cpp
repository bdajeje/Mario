#include "zoom_text_animation.hpp"

namespace animation {

ZoomTextAnimation::ZoomTextAnimation(const game::TextProperty& properties, std::chrono::milliseconds duration, unsigned int to_size)
  : TextAnimation { properties }
  , _duration { duration.count() }
  , _to_size {to_size}
{}

void ZoomTextAnimation::update(const sf::Time& elapsed_time)
{
  _elapsed_time += elapsed_time;
  const unsigned int new_size = _elapsed_time.asMilliseconds() * _to_size / _duration;
  _text.setCharacterSize(new_size);
}

bool ZoomTextAnimation::finished() const
{
  return _elapsed_time.asMilliseconds() >= _duration;
}

}
