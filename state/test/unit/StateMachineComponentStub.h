#include <QObject>
#include <QString>

class StateMachineComponentStub : public QObject {
  Q_OBJECT

 public:
  StateMachineComponentStub();
  virtual ~StateMachineComponentStub();

 signals:
  void stateChanged(const QString& stateName);

 private:
  Q_PROPERTY(QString activeState READ getActiveState WRITE setActiveState);

  const QString getActiveState() const;
  void setActiveState(QString newState);

  QString activeState;
};
