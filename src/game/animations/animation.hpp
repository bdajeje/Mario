#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <chrono>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Clock.hpp>

namespace animation {

class Animation
{
  public:

    Animation(std::chrono::milliseconds duration)
      : _duration { duration.count() }
    {}

    virtual ~Animation() = default;

    virtual void update(const sf::Time& elapsed_time) = 0;

    virtual bool finished() const { return _clock.getElapsedTime().asMilliseconds() >= _duration; }

  protected:

    long int _duration; // in milliseconds
    sf::Clock _clock;
};

}

#endif // ANIMATION_HPP
