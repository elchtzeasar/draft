#include "ConfigurationManagerImpl.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

using boost::property_tree::ptree;

using std::cerr;
using std::cout;
using std::endl;

static const char* PLAYER_NAME_PATH = "configuration.player.name";

ConfigurationManagerImpl::ConfigurationManagerImpl(const std::string& filename)
  : filename(filename), playerName("Unknown player") {}

ConfigurationManagerImpl::~ConfigurationManagerImpl() {
  save();
}

void ConfigurationManagerImpl::load() {
  ptree pt;

  try {
    read_xml(filename, pt);

    playerName = pt.get<std::string>(PLAYER_NAME_PATH, playerName);
  } catch (boost::property_tree::xml_parser::xml_parser_error& e) {
    cerr << "ERROR: Got an error from xml_parser: " << e.what() << endl;
  }
}
void ConfigurationManagerImpl::save() const {
  ptree pt;
  
  pt.put(PLAYER_NAME_PATH, playerName);
  
  write_xml(filename, pt);

  cout << "Configuration saved" << endl;
}

const std::string& ConfigurationManagerImpl::getPlayerName() const {
  return playerName;
}

void ConfigurationManagerImpl::setPlayerName(const std::string& playerName) {
  this->playerName = playerName;
  // TODO: This save should not be needed! Saving should be done at cleanup...
  save();
}
