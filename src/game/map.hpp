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

    Map(const sf::Vector2u& resolution, std::string folder);

    /*! Update map relative to last update */
    void update(const sf::Time& elapsed_time);

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    void keyboardActions();
    void createField(const std::string& folder);
    sf::Vector2i getPlayerStartingPosition() const;
    sf::Vector2i pixelPosToMapPos( const sf::Vector2f& pixel_pos ) const;
    sf::Vector2f mapPosToPixelPos(const sf::Vector2i& map_pos ) const;
    //sf::Vector2i playerMapPos();

    static MapObjectType colorToMapObjectType(sf::Color color);

  private:

    /*! Objects of the map */
    std::vector<std::vector<MapObjectPtr>> _objects;

    /*! Map information */
    utils::Configuration _map_info;

    /*! Size of a map object
     *  \note calculated from given resolution and number of objects to draw per line
     */
    const sf::Vector2f _object_size;

    /*! Map view */
    sf::View _view;

    /*! Player object, the Mario */
    game::Player _player;

    /*! Player can't go out of those limits (in pixels) */
    float _map_left_limit;
    float _map_right_limit;

    /*! View can't go out of those limits (in pixels) */
    float _view_left_limit;
    float _view_right_limit;

    /*! Number of tiles to display for each axis
     * \warning MUST BE AN ODD NUMBER, so there are as many blocks
     *          on the left side and the right side
     */
    static const unsigned int _nbr_tiles_x {29};
    static const unsigned int _nbr_tiles_y {29};

    static const std::map<MapObjectType, std::string> _typeToFilepath;
};

} // namespace game

#endif // GAME_MAP_HPP
