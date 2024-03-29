#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <QIcon>
#include <QObject>
#include <QTimer>

class WifiManager : public QObject
{
  Q_OBJECT
public:
  explicit WifiManager(QObject* parent = nullptr);
  QString essid() const;
  int signal() const;
  const QIcon& icon() const;
  QString iconString() const;

signals:
  void updated();

private slots:
  void refresh();

private:
  static int signalToCharCode(int signal);
  static QString signalToIconString(int signal);
  static QIcon signalToIcon(int signal);

  QTimer mRefreshTimer;
  QString mEssid;
  int mSignal;
  QIcon mIcon;
};

#endif // WIFIMANAGER_H
