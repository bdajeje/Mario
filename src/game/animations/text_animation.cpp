#include "text_animation.hpp"

#include "managers/font_manager.hpp"

namespace animation {

TextAnimation::TextAnimation(const game::TextProperty& properties)
{
  game::TextProperty::create(_text, properties);
}

}
