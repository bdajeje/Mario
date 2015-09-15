#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {

template <class T>
void setMinMax(T& output, T min, T max)
{
  if( output < min )
    output = min;

  if( output > max )
    output = max;
}

namespace maths {

/*! Makes a safe substraction of a and b
 *  If a > b : returns a - b
 *  If a <= b : returns 0
 */
unsigned int safeSubstraction(unsigned int a, unsigned int b);

}

}

#endif // UTILS_HPP

