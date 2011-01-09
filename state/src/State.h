#ifndef STATE_H_
#define STATE_H_

#include <QState>

class QString;

class State : public QState {
 public:
  State(QObject* component, State* parent, const char* name, bool assignName = true);
  virtual ~State() {}

  const QString& getName() const;

 protected:
  QVariant findProperty(const char* name) const;
  bool findAndSetProperty(const char* name, const QVariant& value);

  State& parent;
  QString name;
  QString nameVariant;

 private:
  State(const State&);
  State& operator=(State&);
};

#endif // STATE_H_
