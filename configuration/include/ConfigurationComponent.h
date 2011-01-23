#ifndef CONFIGURATION_COMPONENT_H_
#define CONFIGURATION_COMPONENT_H_

#include <QObject>

#include <string>

class ConfigurationLoader;
class ConfigurationManager;
class PlayerContext;
class PlayerId;

class QString;

class ConfigurationComponent : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponent(
    ConfigurationManager* configurationManager, ConfigurationLoader* configurationLoader);
  ~ConfigurationComponent();

 public slots:
  void handleExit(int);
  void configurationRequest(const PlayerId& playerId);
  void setOwnPlayerId(const PlayerId& playerId);
  void setPlayerName(const PlayerId& playerId, QString playerName);

 signals:
  void configurationResponse(const PlayerId& playerId, const QString playerName);

 private:
  ConfigurationComponent(const ConfigurationComponent&);
  ConfigurationComponent& operator=(ConfigurationComponent&);

  ConfigurationManager* configurationManager;
  ConfigurationLoader* configurationLoader;
};

#endif // CONFIGURATION_COMPONENT_H_
