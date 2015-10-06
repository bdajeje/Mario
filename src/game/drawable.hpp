#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics.hpp>

namespace game {

class Drawable : public sf::Drawable
{
  public:

    Drawable() = default;

    virtual ~Drawable() = default;

    virtual void setPosition(const sf::Vector2f& position) {}
    virtual void setSize(float /*x*/, float /*y*/) {}

    virtual const sf::Vector2f& getPosition() const = 0;
};

}

#endif // DRAWABLE_HPP
