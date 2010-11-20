#ifndef CONFIGURATION_COMPONENT_H_
#define CONFIGURATION_COMPONENT_H_

#include <QObject>

#include <string>

class ConfigurationManager;

class QString;

class ConfigurationComponent : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponent(const ConfigurationManager* configurationManager);
  ~ConfigurationComponent();

 public slots:
  void configurationRequest();

 signals:
  void configurationResponse(const QString playerName);

 private:
  ConfigurationComponent(const ConfigurationComponent&);
  ConfigurationComponent& operator=(ConfigurationComponent&);

  const ConfigurationManager* configurationManager;
};

#endif // CONFIGURATION_COMPONENT_H_
