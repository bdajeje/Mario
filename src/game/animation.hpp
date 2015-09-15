#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include "game/animation.hpp"
#include "game/sprite.hpp"

namespace game {

class Animation final : public Drawable
{
  public:

    Animation(std::string textures_folder);

    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);

    const Sprite& currentSprite() const { return _sprites[_current_sprite_offset]; }

    const sf::Vector2f& getPosition() const { return currentSprite().getPosition(); }

    /*! Set next sprite as active */
    void next();

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    std::vector<Sprite> _sprites;
    size_t _current_sprite_offset {0};
};

}

#endif // ANIMATION_HPP
