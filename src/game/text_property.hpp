#ifndef TEXT_PROPERTY_HPP
#define TEXT_PROPERTY_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "managers/font_manager.hpp"

namespace game {

struct TextProperty
{
  TextProperty( std::string text, std::string font_str, sf::Color color, unsigned int size )
    : text { std::move(text) }
    , font_str { std::move(font_str) }
    , color { std::move(color) }
    , size { size }
  {}

  static void create(sf::Text& text, const TextProperty& properties)
  {
    text.setString(properties.text);
    text.setColor(properties.color);
    text.setCharacterSize(properties.size);
    text.setFont(font::FontManager::get(properties.font_str));
  }

  std::string text;
  std::string font_str;
  sf::Color color;
  unsigned int size;
};

}

#endif // TEXT_PROPERTY_HPP

