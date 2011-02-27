#include <QObject>

class StateMachineComponentStub : public QObject {
  Q_OBJECT

 public:
  StateMachineComponentStub();
  virtual ~StateMachineComponentStub();

 signals:
  void stateChanged();

 private:
  Q_PROPERTY(QString activeState READ getActiveState WRITE setActiveState);

  const QString getActiveState() const;
  void setActiveState(QString newState);

  QString activeState;
};
