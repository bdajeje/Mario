#ifndef MENU_HPP
#define MENU_HPP

#include "game/drawable.hpp"
#include "events/keyword_event_handler.hpp"

namespace game {

class Menu final : public Drawable,
                   public event::KeywordEventHandler
{
  public:

    Menu(const sf::Vector2u& size, const sf::Vector2f& position);

    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);

    const sf::Vector2f& getPosition() const { return _position; }

    void handleKeyboardEvent( const sf::Event& event );

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Text _text_continue;
    sf::Vector2u _size;
    sf::Vector2f _position;
};

} // game

#endif // MENU_HPP
