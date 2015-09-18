#include "menu.hpp"

#include <iostream>

#include "managers/font_manager.hpp"
#include "game/text_property.hpp"

namespace game {

Menu::Menu(const sf::Vector2u& size, const sf::Vector2f& position)
  : _size {size}
  , _position {position}
{
  TextProperty text_properties { "continue", "consolas.ttf", sf::Color::Blue, 20 };
  text_properties.create( _text_continue, text_properties );
  _text_continue.setPosition( position );
}

void Menu::setPosition(const sf::Vector2f& position)
{
  _position = position;
}

void Menu::setSize(float x, float y)
{
  _size.x = x;
  _size.y = y;
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw( _text_continue, states );
}

void Menu::handleKeyboardEvent( const sf::Event& /*event*/ )
{
  std::cout << "menu keyboard event!" << std::endl;
}

} // game
