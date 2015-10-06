#include "sprite_sequence.hpp"

#include "utils/filesystem/directory.hpp"

#include <iostream>

namespace game {

SpriteSequence::SpriteSequence(std::string textures_folder, const sf::Vector2f& size, const sf::Vector2f& position)
{
  // Load textures
  std::vector<std::string> texture_files = utils::listFiles("resources/textures/" + textures_folder, ".*\\.png");
  if( texture_files.empty() )
    throw "Empty SpritesAnimation: " + textures_folder;

  utils::ensureDirectoryEnd(textures_folder);

  for( const auto& texture_file : texture_files)
  {
    _sprites.emplace_back( textures_folder + texture_file );
    _sprites.back().setSize(size.x, size.y);
    _sprites.back().setPosition(position);
  }
}

void SpriteSequence::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(currentSprite(), states);
}

const Sprite& SpriteSequence::currentSprite() const
{
  return _sprites[_current_sprite];
}

void SpriteSequence::setSize(float x, float y)
{
  for( Sprite& sprite : _sprites )
    sprite.setSize(x, y);
}

void SpriteSequence::setPosition(const sf::Vector2f& position)
{
  for( Sprite& sprite : _sprites )
    sprite.setPosition(position);
}

}
