#ifndef CONFIGURATION_COMPONENT_H_
#define CONFIGURATION_COMPONENT_H_

#include <QObject>

#include <string>

class PlayerContext;
class ConfigurationLoader;
class ConfigurationManager;

class QString;

class ConfigurationComponent : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponent(
    ConfigurationManager* configurationManager, ConfigurationLoader* configurationLoader);
  ~ConfigurationComponent();

 public slots:
  void handleExit(int);
  void configurationRequest(quint8 playerId);
  void setOwnPlayerId(quint8 playerId);
  void setPlayerName(quint8 playerId, QString playerName);

 signals:
  void configurationResponse(quint8 playerId, const QString playerName);

 private:
  ConfigurationComponent(const ConfigurationComponent&);
  ConfigurationComponent& operator=(ConfigurationComponent&);

  ConfigurationManager* configurationManager;
  ConfigurationLoader* configurationLoader;
};

#endif // CONFIGURATION_COMPONENT_H_
