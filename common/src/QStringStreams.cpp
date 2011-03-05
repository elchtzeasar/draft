#include "QStringStreams.h"

using std::istream;
using std::ostream;

ostream& operator<<(ostream& stream, const QString& string) {
  stream << string.toStdString();
  return stream;
}

istream& operator>>(istream& stream, QString& string) {
  std::string stdString;
  stream >> stdString;
  string = QString(stdString.c_str());

  return stream;
}
