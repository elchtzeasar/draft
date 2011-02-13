#ifndef CONFIGURATION_COMPONENT_STUB_H_
#define CONFIGURATION_COMPONENT_STUB_H_

#include "PlayerId.h"

#include <QObject>
#include <QString>

class ConfigurationComponentStub : public QObject {
  Q_OBJECT

 public:
  ConfigurationComponentStub();
  void sendConfigurationResponse(const PlayerId& playerId, const QString playerName);

 public slots:
  void handleExit(int);
  void handleConfigurationRequest(const PlayerId& playerId);
  void handleSetOwnPlayerId(const PlayerId& playerId);
  void handleSetPlayerName(const PlayerId& playerId, QString playerName);

 signals:
  void configurationResponse(const PlayerId& playerId, const QString playerName);

 private:
  PlayerId ownPlayerId;
};

#endif
