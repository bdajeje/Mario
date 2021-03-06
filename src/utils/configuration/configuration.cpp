#include "configuration.hpp"

#include <boost/algorithm/string.hpp>

#include "utils/filesystem/file.hpp"

namespace utils {

Configuration::Configuration(const std::string& conf_file_path)
{
  // Read conf file
  std::string content;
  if( !files::read(conf_file_path, content) )
    throw ConfigurationException {"Can't read file: " + conf_file_path};

  // Split by line
  std::vector<std::string> lines;
  boost::algorithm::split( lines, content, boost::is_any_of("\n") );

  // Read each line and save results
  std::vector<std::string> parts;
  parts.reserve(2);
  for( std::string& line : lines )
  {
    // Empty line or comment
    boost::algorithm::trim(line);
    if( line.empty() || line.front() == '#' )
      continue;

    // Split line by key/value
    boost::algorithm::split(parts, line, boost::is_any_of("="));
    if(parts.size() != 2)
      continue;

    // Remove possible useless whitespaces
    const std::string key   = boost::algorithm::trim_copy(parts.front());
    const std::string value = boost::algorithm::trim_copy(parts.back());

    // Adding conf to results
    _configs.emplace( key, value );
  }
}

ConfigurationException::ConfigurationException(const std::string& what_arg)
  : std::invalid_argument {"Configuration exception: " + what_arg}
{}

}
