#ifndef UTILS_HPP
#define UTILS_HPP

#include <SFML/Graphics.hpp>

namespace utils {

namespace maths {

template <class T>
void setMinMax(T& output, T min, T max)
{
  if( output < min )
    output = min;

  if( output > max )
    output = max;
}

/*! Makes a safe substraction of a and b
 *  If a > b : returns a - b
 *  If a <= b : returns 0
 */
unsigned int safeSubstraction(unsigned int a, unsigned int b);

/*! Returns absolute version of given value
 *  \note if value.x == -10 returns value.x == 10
 *  \note if value.y == -5 returns value.x == 5
 */
sf::Vector2f abs(const sf::Vector2f& value);

}

namespace position {

sf::Vector2f centerToBottomLeft(const sf::Vector2f& center, const sf::Vector2f& size);

} // position

namespace string {

std::string convert(float number, int precision);

} // string

} // utils

#endif // UTILS_HPP

