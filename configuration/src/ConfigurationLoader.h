#ifndef CONFIGURATION_LOADER_H_
#define CONFIGURATION_LOADER_H_

#include "QStringStreams.h"

#include <string>

class QString;

class ConfigurationLoader {
 public:
  virtual ~ConfigurationLoader() {}

  virtual void load() = 0;
  virtual void save() const = 0;
};

#endif // CONFIGURATION_LOADER_H_
