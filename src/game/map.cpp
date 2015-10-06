#include "map.hpp"

#include <exception>
#include <iostream>

#include "utils/filesystem/directory.hpp"
#include "utils/utils.hpp"
#include "managers/texture_manager.hpp"
#include "game/sprite.hpp"
#include "game/key_bindings.hpp"

namespace game {

const std::map<MapObjectType, std::string> Map::_typeToFilepath = {
  { MapObjectType::Block, "block.png" }
};

Map::Map(const sf::Vector2u& resolution, std::string folder)
  : _map_info { utils::ensureDirectoryEnd(folder) + "info" }
  , _object_size { (float)resolution.x / _nbr_tiles_x, (float)resolution.y / _nbr_tiles_y }
  , _view { mapPosToPixelPos( getPlayerStartingPosition() ), {static_cast<float>(resolution.x), static_cast<float>(resolution.y)} }
  , _player { _object_size, _view.getCenter() }
{
  createField(folder);

  // Map limits
  _map_left_limit = 0;
  _map_right_limit = _objects.front().size() * _object_size.x;

  // Set view limits
  _view_left_limit  = (_nbr_tiles_x / 2) * _object_size.x;
  _view_right_limit = _map_right_limit - _view_left_limit;
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
  for( int y = 0; y < field_image_size.y; ++y )
  {
    // Reserve memory
    std::vector<MapObjectPtr>& x_line = _objects[y];
    x_line.resize( field_image_size.x );

    // For each x
    for( int x = 0; x < field_image_size.x; ++x )
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
  target.setView( _view );

  // Find objects to draw depending on camera position (draw only visibled objects)
  const sf::Vector2i camera_pos = pixelPosToMapPos(_view.getCenter());

  const unsigned int start_x = utils::maths::safeSubstraction(camera_pos.x, _nbr_tiles_x / 2);
  const unsigned int end_x   = std::min(start_x + _nbr_tiles_x, static_cast<unsigned int>(_objects.front().size() - 1));

  const unsigned int start_y = utils::maths::safeSubstraction(camera_pos.y, _nbr_tiles_y / 2);
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
  target.draw(_player, states);

  target.setView( target.getDefaultView() );
}

MapObjectType Map::colorToMapObjectType(sf::Color color)
{
  if( color.r == 128 && color.g == 64  && color.b == 0 )
    return MapObjectType::Block;

  return MapObjectType::None;
}

sf::Vector2i Map::getPlayerStartingPosition() const
{
  return { _nbr_tiles_x / 2,
           _map_info.get<int>("player_start_y") };
}

sf::Vector2i Map::pixelPosToMapPos( const sf::Vector2f& pixel_pos ) const
{
  return { static_cast<int>(pixel_pos.x) / static_cast<int>(_object_size.x),
           static_cast<int>(pixel_pos.y) / static_cast<int>(_object_size.y) };
}

sf::Vector2f Map::mapPosToPixelPos(const sf::Vector2i& map_pos) const
{
  return { map_pos.x * _object_size.x,
           map_pos.y * _object_size.y };
}

void Map::update(const sf::Time& elapsed_time)
{
  _player.update(elapsed_time);

  // Update player position
  if( _player.hasSpeed() )
  {
    // Calculate destination
    float x_move = _player.getHorizontalSpeed() * elapsed_time.asMilliseconds();
    float x_destination = _player.getPosition().x + x_move;
    float y_destination = _player.getPosition().y;

    // Check movement doesn't reach limits
    if( x_destination < _map_left_limit )
    {
      x_destination = _map_left_limit;
      _player.resetMovement(); // player's reach limit, reset movement inertia
    }
    else if( x_destination + _player.getWidth() > _map_right_limit )
    {
      x_destination = _map_right_limit - _player.getWidth();
      _player.resetMovement(); // player's reach limit, reset movement inertia
    }

    // Update player and view positions
    _player.setPosition( {x_destination, y_destination} );
    _view.setCenter( _player.getCenter() );

    // Check view's limits not reached
    const sf::Vector2f& view_center = _view.getCenter();
    if( view_center.x < _view_left_limit )
      _view.setCenter( _view_left_limit, view_center.y );
    else if( view_center.x > _view_right_limit )
      _view.setCenter( _view_right_limit, view_center.y );
  }

  keyboardActions();
}

void Map::keyboardActions()
{
  if(sf::Keyboard::isKeyPressed( KeyBindings::get(Action::MoveRight) ))
    _player.setMovingTo(Direction::Right);
  else if(sf::Keyboard::isKeyPressed( KeyBindings::get(Action::MoveLeft) ))
    _player.setMovingTo(Direction::Left);
  else
    _player.stopMoving();
}

} // namespace game
