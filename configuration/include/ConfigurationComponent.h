#ifndef CONFIGURATION_COMPONENT_H_
#define CONFIGURATION_COMPONENT_H_

#include <QObject>

#include <string>

class ConfigurationManager;

class QString;

class ConfigurationComponent : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponent(ConfigurationManager* configurationManager);
  ~ConfigurationComponent();

 public slots:
  void configurationRequest();
  void setPlayerName(QString playerName);

 signals:
  void configurationResponse(const QString playerName);

 private:
  ConfigurationComponent(const ConfigurationComponent&);
  ConfigurationComponent& operator=(ConfigurationComponent&);

  ConfigurationManager* configurationManager;
};

#endif // CONFIGURATION_COMPONENT_H_
