#ifndef TEXTANIMATION_HPP
#define TEXTANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "game/animations/animation.hpp"
#include "game/text_property.hpp"

namespace animation {

class TextAnimation : public Animation
{
  public:

    TextAnimation(const game::TextProperty& properties);

    virtual const sf::Drawable& drawable() const override { return _text; }

  protected:

    sf::Text _text;
};

}

#endif // TEXTANIMATION_HPP
