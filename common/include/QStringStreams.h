#ifndef QSTRING_STREAM_H_
#define QSTRING_STREAM_H_

#include <QString>
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const QString& string);
std::istream& operator>>(std::istream& stream, QString& string);

#endif
