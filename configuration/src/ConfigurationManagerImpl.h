#ifndef CONFIGURATION_MANAGER_IMPL_H_
#define CONFIGURATION_MANAGER_IMPL_H_

#include "ConfigurationManager.h"

class ConfigurationManagerImpl : public ConfigurationManager {
 public:
  ConfigurationManagerImpl();
  virtual ~ConfigurationManagerImpl();

  virtual const std::string& getPlayerName() const;
  virtual void setPlayerName(const std::string& playerName);
 private:
  ConfigurationManagerImpl(const ConfigurationManager&);
  ConfigurationManagerImpl& operator=(ConfigurationManager&);

  std::string playerName;
};

#endif // CONFIGURATION_MANAGER_IMPL_H_
