#ifndef KEYWORDEVENTHANDLER_HPP
#define KEYWORDEVENTHANDLER_HPP

#include <SFML/Window/Event.hpp>

namespace event {

class KeywordEventHandler
{
  public:

    KeywordEventHandler() = default;

    virtual ~KeywordEventHandler() = default;

    virtual void handleKeyboardEvent( const sf::Event& event ) = 0;
};

}

#endif // KEYWORDEVENTHANDLER_HPP
