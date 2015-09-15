#ifndef MAPOBJECT_HPP
#define MAPOBJECT_HPP

#include <memory>

#include "game/sprite.hpp"

namespace game {

class MapObject final : public Sprite
{
  public:

    MapObject( const std::string& texture_filepath );

    bool isBlocking() const { return _blocking; }

  private:

    /*! Is this object physically blocking */
    bool _blocking {true};
};

typedef std::shared_ptr<MapObject> MapObjectPtr;

}

#endif // MAPOBJECT_HPP
