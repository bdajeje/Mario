#ifndef TEXT_ANIMATION_HPP
#define TEXT_ANIMATION_HPP

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "game/animations/animation.hpp"

namespace animation {

class TextAnimation : public Animation
{
  public:

    TextAnimation( std::chrono::milliseconds duration, const std::shared_ptr<sf::Text>& target );

    virtual ~TextAnimation() = default;

  protected:

    std::shared_ptr<sf::Text> _text;
};

}

#endif // TEXT_ANIMATION_HPP
