#include "ConfigurationLoaderImpl.h"

#include "PlayerContext.h"

#include <QString>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <glog/logging.h>

using boost::property_tree::ptree;

using std::string;

static const char* PLAYER_NAME_PATH = "configuration.player.name";

ConfigurationLoaderImpl::ConfigurationLoaderImpl(
  const string& filename, PlayerContext& playerContext) :
  filename(filename), playerContext(playerContext) {}

ConfigurationLoaderImpl::~ConfigurationLoaderImpl() {}

void ConfigurationLoaderImpl::load() {
  ptree pt;
  QString playerName("No name");

  try {
    read_xml(filename, pt);

    playerName = pt.get<QString>(PLAYER_NAME_PATH, "");
    if (playerName.length() > 0) {
      playerContext.setPlayerName(playerName);
    }
  } catch (boost::property_tree::xml_parser::xml_parser_error& e) {
    LOG(ERROR) << "Got an error from xml_parser: " << e.what() << " with filename: " << filename;
  }
}

void ConfigurationLoaderImpl::save() const {
  ptree pt;
  
  pt.put(PLAYER_NAME_PATH, playerContext.getPlayerName());
  
  write_xml(filename, pt);
}

