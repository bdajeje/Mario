#include "text_animation.hpp"

namespace animation {

TextAnimation::TextAnimation(std::chrono::milliseconds duration, const std::shared_ptr<sf::Text>& target )
  : Animation {duration}
  , _text { target }
{}

}
