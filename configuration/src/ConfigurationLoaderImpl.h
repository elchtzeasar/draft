#ifndef CONFIGURATION_LOADER_IMPL_H_
#define CONFIGURATION_LOADER_IMPL_H_

#include "ConfigurationLoader.h"

class ConfigurationManager;

class ConfigurationLoaderImpl : public ConfigurationLoader {
 public:
  ConfigurationLoaderImpl(
    const std::string& filename, ConfigurationManager& configurationManager);
  virtual ~ConfigurationLoaderImpl();

  virtual void load();
  virtual void save() const;

 private:
  ConfigurationLoaderImpl(const ConfigurationLoaderImpl&);
  ConfigurationLoaderImpl& operator=(ConfigurationLoaderImpl&);

  const std::string filename;
  ConfigurationManager& configurationManager;
};

#endif // CONFIGURATION_LOADER_IMPL_H_
