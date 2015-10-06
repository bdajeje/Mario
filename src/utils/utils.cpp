#include "utils.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace utils {

namespace maths {

unsigned int safeSubstraction(unsigned int a, unsigned int b)
{
  return (a > b) ? a - b : 0;
}

sf::Vector2f abs(const sf::Vector2f& value)
{
  sf::Vector2f result = value;

  if( result.x < 0 )
    result.x = -result.x;

  if( result.y < 0 )
    result.y = -result.y;

  return result;
}

} // maths

namespace position {

sf::Vector2f centerToBottomLeft(const sf::Vector2f& center, const sf::Vector2f& size)
{
  return { center.x - size.x / 2,
           center.y - size.y / 2 };
}

} // position

namespace string {

std::string convert(float number, int precision)
{
  std::stringstream stream;
  stream << std::fixed << std::setprecision(precision) << number;
  return stream.str();
}

} // string

} // utils
