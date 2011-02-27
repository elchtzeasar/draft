#ifndef STATE_H_
#define STATE_H_

#include <QState>

class QString;

class State : public QState {
 public:
  State(QObject* stateMachineComponent, State* parent, const char* name, bool assignName = true);
  virtual ~State() {}

  const QString& getName() const;

  QVariant findProperty(const char* name) const;
  bool findAndSetProperty(const char* name, const QVariant& value);

 private:
  State(const State&);
  State& operator=(State&);

  State& parent;
  QString name;
  QString nameVariant;
};

#endif // STATE_H_
