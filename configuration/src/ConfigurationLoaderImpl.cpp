#include "ConfigurationLoaderImpl.h"

#include "ConfigurationManager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

using boost::property_tree::ptree;

using std::cerr;
using std::endl;
using std::string;

static const char* PLAYER_NAME_PATH = "configuration.player.name";

ConfigurationLoaderImpl::ConfigurationLoaderImpl(
  const string& filename, ConfigurationManager& configurationManager) :
  filename(filename), configurationManager(configurationManager) {}

ConfigurationLoaderImpl::~ConfigurationLoaderImpl() {}

void ConfigurationLoaderImpl::load() {
  ptree pt;
  std::string playerName("No name");

  try {
    read_xml(filename, pt);

    playerName = pt.get<std::string>(PLAYER_NAME_PATH, "");
    if (playerName.length() > 0)
      configurationManager.setPlayerName(playerName);
  } catch (boost::property_tree::xml_parser::xml_parser_error& e) {
    cerr << "ERROR: Got an error from xml_parser: " << e.what() << " with file: " << filename << endl;
  }
}

void ConfigurationLoaderImpl::save() const {
  ptree pt;
  
  pt.put(PLAYER_NAME_PATH, configurationManager.getPlayerName());
  
  write_xml(filename, pt);
}
