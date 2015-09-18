#ifndef ZOOMTEXTANIMATION_HPP
#define ZOOMTEXTANIMATION_HPP

#include <chrono>

#include "game/animations/text_animation.hpp"

namespace animation {

class ZoomTextAnimation final : public TextAnimation
{
  public:

    ZoomTextAnimation(const game::TextProperty& properties, std::chrono::milliseconds duration, unsigned int to_size);

    void update(const sf::Time& elapsed_time) override;

    bool finished() const override;

  private:

    /*! Duration in milliseconds */
    long int _duration;
    unsigned int _to_size;
    sf::Time _elapsed_time {sf::Time::Zero};
};

}

#endif // ZOOMTEXTANIMATION_HPP
