#include "map.hpp"

#include <exception>
#include <iostream>

#include "utils/filesystem/directory.hpp"
#include "utils/utils.hpp"
#include "managers/texture_manager.hpp"
#include "game/sprite.hpp"

namespace game {

const std::map<MapObjectType, std::string> Map::_typeToFilepath = {
  { MapObjectType::Block, "block.png" }
};

Map::Map(const sf::Vector2u& resolution, std::string folder, const game::PlayerPtr& player)
  : _map_info { utils::ensureDirectoryEnd(folder) + "info" }
  , _player {player}
  , _object_size { (float)resolution.x / _nbr_tiles_x, (float)resolution.y / _nbr_tiles_y }
{
  createField(folder);

  _player->setPosition( mapPosToPixelPos( getPlayerStartingPosition() ) );
}

void Map::createField(const std::string& folder)
{
  // Read field image file to create map objects
  sf::Image field_image;
  if( !field_image.loadFromFile( folder + "field.png" ) )
    throw std::invalid_argument {"Can't read map field file"};

  // Get field image size then reserve memory
  const sf::Vector2u field_image_size = field_image.getSize();
  _objects.resize( field_image_size.y );

  // For each y
  for( unsigned int y = 0; y < field_image_size.y; ++y )
  {
    // Reserve memory
    std::vector<MapObjectPtr>& x_line = _objects[y];
    x_line.resize( field_image_size.x );

    // For each x
    for( unsigned int x = 0; x < field_image_size.x; ++x )
    {
      MapObjectType type = colorToMapObjectType( field_image.getPixel(x, y) );
      if( type == MapObjectType::None )
        continue;

      MapObject* map_object = new MapObject( _typeToFilepath.find(type)->second );
      map_object->setSize( _object_size.x, _object_size.y );
      map_object->setPosition( mapPosToPixelPos({x,y}) );
      x_line[x].reset( map_object );
    }
  }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  // Find objects to draw from from player position (camera's centered on player)
  const sf::Vector2u player_pos = pixelPosToMapPos(_player->getPosition());

  const unsigned int start_x = utils::maths::safeSubstraction(player_pos.x, _nbr_tiles_x / 2);
  const unsigned int end_x   = std::min(start_x + _nbr_tiles_x, static_cast<unsigned int>(_objects.front().size() - 1));

  const unsigned int start_y = utils::maths::safeSubstraction(player_pos.y, _nbr_tiles_y / 2);
  const unsigned int end_y   = std::min(start_y + _nbr_tiles_y, static_cast<unsigned int>(_objects.size() - 1));

  // Draw map object
  for( unsigned int y = start_y; y < end_y; ++y )
  {
    for( unsigned int x = start_x; x < end_x; ++x )
    {
      const auto& map_object = _objects[y][x];
      if( map_object )
        target.draw( *map_object.get(), states );
    }
  }

  // Draw player
  target.draw(*_player.get(), states);
}

MapObjectType Map::colorToMapObjectType(sf::Color color)
{
  if( color.r == 128 && color.g == 64  && color.b == 0 )
    return MapObjectType::Block;

  return MapObjectType::None;
}

sf::Vector2u Map::getPlayerStartingPosition() const
{
  return { _map_info.get<unsigned int>("player_start_x"),
           _map_info.get<unsigned int>("player_start_y") };
}

sf::Vector2u Map::pixelPosToMapPos( const sf::Vector2f& pixel_pos ) const
{
  return { static_cast<unsigned int>(pixel_pos.x) / static_cast<unsigned int>(_object_size.x),
           static_cast<unsigned int>(pixel_pos.y) / static_cast<unsigned int>(_object_size.y) };
}

sf::Vector2f Map::mapPosToPixelPos( const sf::Vector2u& map_pos ) const
{
  return { map_pos.x * _object_size.x,
           map_pos.y * _object_size.y };
}

} // namespace game
