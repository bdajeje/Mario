#include "animation.hpp"

#include <iostream>

#include "utils/filesystem/directory.hpp"

namespace game {

Animation::Animation(std::string textures_folder)
{
  // Load textures
  std::vector<std::string> texture_files = utils::listFiles("resources/textures/" + textures_folder, ".*\\.png");
  if( texture_files.empty() )
    throw "Empty animation: " + textures_folder;

  utils::ensureDirectoryEnd(textures_folder);

  for( const auto& texture_file : texture_files)
    _sprites.emplace_back( textures_folder + texture_file );
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( currentSprite(), states );
}

void Animation::next()
{
  _current_sprite_offset++;
  if(_current_sprite_offset >= _sprites.size())
    _current_sprite_offset = 0;
}

void Animation::setPosition(const sf::Vector2f& position)
{
  for( auto& sprite : _sprites )
    sprite.setPosition(position);
}

void Animation::setSize(float x, float y)
{
  for( auto& sprite : _sprites )
    sprite.setSize(x, y);
}

}
