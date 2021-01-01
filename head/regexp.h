#ifndef REGEXP_H
#define REGEXP_H

#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>

class RegExp
{
public:
  RegExp(){}
  QRegularExpressionValidator* IP()
  {
    QRegularExpression re(_IP_);
    return new QRegularExpressionValidator(re);
  }
  QRegularExpressionValidator* PORT()
  {
    QRegularExpression re(_PORT_);
    return new QRegularExpressionValidator(re);
  }
private:
  QString _IP_="\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b";
  QString _PORT_="[1-9]\\d{4}|[0]";
};

#endif // REGEXP_H
