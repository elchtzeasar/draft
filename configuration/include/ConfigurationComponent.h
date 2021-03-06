#ifndef CONFIGURATION_COMPONENT_H_
#define CONFIGURATION_COMPONENT_H_

#include <QObject>

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
  void handleConfigurationRequest(const PlayerId& playerId);
  void handleSetOwnPlayerId(const PlayerId& playerId);
  void handleUpdatePlayerConfiguration(const PlayerId& playerId, const QString& playerName);
  void handleCreatePlayerConfiguration(const PlayerId& playerId, const QString& playerName);

 signals:
  void configurationResponse(const PlayerId& playerId, const QString& playerName);

 private:
  ConfigurationComponent(const ConfigurationComponent&);
  ConfigurationComponent& operator=(ConfigurationComponent&);

  ConfigurationManager* configurationManager;
  ConfigurationLoader* configurationLoader;
};

#endif // CONFIGURATION_COMPONENT_H_
