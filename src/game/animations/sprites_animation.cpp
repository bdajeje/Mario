#include "sprites_animation.hpp"

namespace animation {

SpritesAnimation::SpritesAnimation(std::string textures_folder)
{
  // Load textures
  std::vector<std::string> texture_files = utils::listFiles("resources/textures/" + textures_folder, ".*\\.png");
  if( texture_files.empty() )
    throw "Empty SpritesAnimation: " + textures_folder;

  utils::ensureDirectoryEnd(textures_folder);

  for( const auto& texture_file : texture_files)
    _sprites.emplace_back( textures_folder + texture_file );
}

void SpritesAnimation::update(const sf::Time& elapsed_time)
{
  _current_sprite_offset++;
  if(_current_sprite_offset >= _sprites.size())
    _current_sprite_offset = 0;
}

//void SpritesAnimation::setPosition(const sf::Vector2f& position)
//{
//  for( auto& sprite : _sprites )
//    sprite.setPosition(position);
//}

//void SpritesAnimation::setSize(float x, float y)
//{
//  for( auto& sprite : _sprites )
//    sprite.setSize(x, y);
//}

}
