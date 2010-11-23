#include "ConfigurationManager.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

using boost::property_tree::ptree;

using std::cerr;
using std::cout;
using std::endl;

static const char* PLAYER_NAME_PATH = "configuration.player.name";

ConfigurationManager::ConfigurationManager(const std::string& filename)
  : filename(filename), playerName("Unknown player") {}

ConfigurationManager::~ConfigurationManager() {
  save();
}

void ConfigurationManager::load() {
  ptree pt;

  try {
    read_xml(filename, pt);

    playerName = pt.get<std::string>(PLAYER_NAME_PATH, "Unknown player");
  } catch (boost::property_tree::xml_parser::xml_parser_error& e) {
    cerr << "ERROR: Got an error from xml_parser: " << e.what() << endl;
  }
}
void ConfigurationManager::save() const {
  ptree pt;
  
  pt.put(PLAYER_NAME_PATH, playerName);
  
  write_xml(filename, pt);

  cout << "Configuration saved" << endl;
}

const std::string& ConfigurationManager::getPlayerName() const {
  return playerName;
}

void ConfigurationManager::setPlayerName(const std::string& playerName) {
  this->playerName = playerName;
  // TODO: This save should not be needed! Saving should be done at cleanup...
  save();
}
