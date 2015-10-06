#ifndef ZOOMTEXTANIMATION_HPP
#define ZOOMTEXTANIMATION_HPP

#include <chrono>

#include "game/animations/text_animation.hpp"
#include "game/text_property.hpp"

namespace animation {

class ZoomTextAnimation final : public TextAnimation
{
  public:

    ZoomTextAnimation(const std::shared_ptr<sf::Text>& target, std::chrono::milliseconds duration, unsigned int to_size);

    virtual void update(const sf::Time& elapsed_time) override;

  private:

    unsigned int _to_size;
};

}

#endif // ZOOMTEXTANIMATION_HPP
