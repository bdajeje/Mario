#ifndef SPRITESANIMATION_HPP
#define SPRITESANIMATION_HPP

#include "game/animations/animation.hpp"
#include "game/sprite.hpp"
#include "utils/filesystem/directory.hpp"

namespace animation {

class SpritesAnimation final : public Animation
{
  public:

    SpritesAnimation(std::string textures_folder);

//    void setPosition(const sf::Vector2f& position);
//    void setSize(float x, float y);

//    const sf::Vector2f& getPosition() const { return currentSprite().getPosition(); }

    void update(const sf::Time& elapsed_time) override;

    bool finished() const override { return false; }

    const sf::Drawable& drawable() const override { return _sprites[_current_sprite_offset]; }

  private:

    std::vector<game::Sprite> _sprites;
    size_t _current_sprite_offset {0};
};

}

#endif // SPRITESANIMATION_HPP
