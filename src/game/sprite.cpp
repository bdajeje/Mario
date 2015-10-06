#include "sprite.hpp"

#include "managers/texture_manager.hpp"

namespace game {

Sprite::Sprite(const std::string& texture_filepath)
{
  _sprite.setTexture( texture::TextureManager::get(texture_filepath) );
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( _sprite, states );
}

void Sprite::setSize(float x, float y)
{
  _sprite.setScale( x / _sprite.getGlobalBounds().width,
                    y / _sprite.getGlobalBounds().height );
}

sf::Vector2f Sprite::getSize() const
{
  return {_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height};
}

}
