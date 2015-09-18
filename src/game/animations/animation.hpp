#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

namespace animation {

/*! Animation abstract class */
class Animation
{
  public:

    Animation() = default;

    virtual ~Animation() = default;

    virtual void update(const sf::Time& elapsed_time) = 0;

    virtual bool finished() const = 0;

    virtual const sf::Drawable& drawable() const = 0;
};

}

#endif // ANIMATION_HPP
