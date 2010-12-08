#ifndef STATE_H_
#define STATE_H_

#include <QState>
#include <QVariant>

class State : public QState {
 public:
  State(QObject* component, State* parent, const char* name);

 private:
  QVariant name;
};

#endif // STATE_H_
