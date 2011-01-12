#ifndef CONFIGURATION_LOADER_MOCK_H_
#define CONFIGURATION_LOADER_MOCK_H_

#include "ConfigurationLoader.h"

#include <gmock/gmock.h>

class ConfigurationLoaderMock : public ConfigurationLoader {
 public:
  virtual ~ConfigurationLoaderMock() {}

  MOCK_METHOD0(load, void());
  MOCK_CONST_METHOD0(save, void());
};

#endif // CONFIGURATION_LOADER_MOCK_H_
