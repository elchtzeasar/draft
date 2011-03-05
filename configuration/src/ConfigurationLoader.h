#ifndef CONFIGURATION_LOADER_H_
#define CONFIGURATION_LOADER_H_

#include <string>

class QString;

class ConfigurationLoader {
 public:
  virtual ~ConfigurationLoader() {}

  virtual void load() = 0;
  virtual void save() const = 0;
};

std::ostream& operator<<(std::ostream& stream, const QString& string);
std::istream& operator>>(std::istream& stream, QString& string);

#endif // CONFIGURATION_LOADER_H_
