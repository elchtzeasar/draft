#ifndef STATE_H_
#define STATE_H_

#include <QState>
#include <QString>
#include <QVariant>

class State : public QState {
 public:
  State(QObject* component, State* parent, const char* name, bool assignName = true);
  virtual ~State() {}

  const QString& getName() const;

 protected:
  QString name;
  QString nameVariant;

 private:
  State(const State&);
  State& operator=(State&);
};

#endif // STATE_H_
