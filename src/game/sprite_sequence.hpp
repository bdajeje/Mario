#ifndef SPRITESEQUENCE_HPP
#define SPRITESEQUENCE_HPP

#include <vector>

#include "game/sprite.hpp"
#include "utils/utils.hpp"

namespace game {

class SpriteSequence final : public Drawable
{
  public:

    SpriteSequence(std::string sprite_folder, const sf::Vector2f& size, const sf::Vector2f& position);

    /*! Set all sequence sprites to given size */
    void setSize(float x, float y) override;

    /*! Set all sequence sprites to given position */
    void setPosition(const sf::Vector2f& position) override;

    const Sprite& currentSprite() const;

    sf::Vector2f getSize() const { return currentSprite().getSize(); }

    virtual const sf::Vector2f& getPosition() const override { return currentSprite().getPosition(); }

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    std::vector<Sprite> _sprites;
    size_t _current_sprite {0};
};

}

#endif // SPRITESEQUENCE_HPP
