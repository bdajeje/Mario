#ifndef GAME_MAP_HPP
#define GAME_MAP_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "game/player.hpp"
#include "game/map_object.hpp"
#include "utils/configuration/configuration.hpp"

namespace game {

enum class MapObjectType {
  None, Player, Block
};

class Map final : public sf::Drawable
{
  public:

    Map(const sf::Vector2u& resolution, std::string folder, const game::PlayerPtr& player);

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    void createField(const std::string& folder);
    sf::Vector2u getPlayerStartingPosition() const;
    sf::Vector2u pixelPosToMapPos( const sf::Vector2f& pixel_pos ) const;
    sf::Vector2f mapPosToPixelPos( const sf::Vector2u& map_pos ) const;

    static MapObjectType colorToMapObjectType(sf::Color color);

  private:

    std::vector<std::vector<MapObjectPtr>> _objects;
    utils::Configuration _map_info;
    const game::PlayerPtr _player;

    /*! Size of a map object
     *  \note calculated from given resolution and number of objects to draw per line
     */
    const sf::Vector2f _object_size;

    /*! Number of tiles to display for each axis
     * \warning MUST BE AN EVEN NUMBER
     */
    static const unsigned int _nbr_tiles_x {30};
    static const unsigned int _nbr_tiles_y {30};

    static const std::map<MapObjectType, std::string> _typeToFilepath;
};

} // namespace game

#endif // GAME_MAP_HPP
