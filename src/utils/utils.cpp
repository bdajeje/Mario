#include "utils.hpp"

namespace utils {

namespace maths {

unsigned int safeSubstraction(unsigned int a, unsigned int b)
{
  return (a > b) ? a - b : 0;
}

}

}
