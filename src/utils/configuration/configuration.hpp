#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <exception>
#include <string>
#include <vector>
#include <map>

#include <boost/lexical_cast.hpp>

namespace utils {

class ConfigurationException final : public std::invalid_argument
{
  public:

    ConfigurationException(const std::string& what_arg);
};

class Configuration final
{
  public:

    Configuration( const std::string& conf_file_path );

    template <class T>
    T get(const std::string& key) const
    {
      auto found_it = _configs.find(key);
      if( found_it == _configs.end() )
        throw ConfigurationException {"no config: " + key};

      return boost::lexical_cast<T>( found_it->second );
    }

  private:

    std::map<std::string, std::string> _configs;
};

} // namespace utils

#endif // CONFIGURATION_HPP
