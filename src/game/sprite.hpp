#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "game/drawable.hpp"

namespace game {

class Sprite : public Drawable
{
  public:

    Sprite(const std::string& texture_filepath);

    /*! Set sprite size (in pixels) */
    void setSize(float x, float y) override;

    /*! Set sprite position (in pixels) */
    void setPosition(const sf::Vector2f& position) override { _sprite.setPosition(position); }
    void setPosition(float x, float y) { _sprite.setPosition({x, y}); }

    const sf::Vector2f& getPosition() const override { return _sprite.getPosition(); }
    sf::Vector2f getSize() const;

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Sprite _sprite;
};

}

#endif // SPRITE_HPP
