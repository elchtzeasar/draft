#ifndef CONFIGURATION_COMPONENT_STUB_H_
#define CONFIGURATION_COMPONENT_STUB_H_

#include "PlayerId.h"

#include <QObject>
#include <QString>
#include <string>

class ConfigurationComponentStub : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponentStub();
  virtual ~ConfigurationComponentStub();
  void sendConfigurationResponse(const PlayerId& playerId, const QString playerName);

  std::string getPlayerName(const PlayerId& playerId) const;

 public slots:
  void handleExit(int);
  void handleConfigurationRequest(const PlayerId& playerId);
  void handleSetOwnPlayerId(const PlayerId& playerId);
  void handleUpdatePlayerConfiguration(const PlayerId& playerId, QString playerName);
  void handleSetPlayerName(const PlayerId& playerId, QString playerName);

 signals:
  void configurationResponse(const PlayerId& playerId, const QString playerName);

 private:
  PlayerId ownPlayerId;
};

#endif
