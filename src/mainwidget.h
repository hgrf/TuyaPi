#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QLabel>
#include <QMenu>
#include <QSystemTrayIcon>
#include <tuyacpp/bindings/qt.hpp>

#include "bluetoothmanager.h"
#include "bulbwidget.h"
#include "lockscreen.h"
#include "wifimanager.h"

class MainWidget : public QLabel
{
  Q_OBJECT

public:
  MainWidget(bool isDesktop = false, QWidget* parent = nullptr);
  ~MainWidget();

  virtual bool eventFilter(QObject* watched, QEvent* event) override;

public slots:
  void deviceConnected(QString ip);
  void deviceDisconnected(QString ip);
  void deviceDiscovered(QString ip);
  void newDeviceData(QString ip, QJsonDocument data);

  void hideMouse();

private:
  QAction* mQuitAction;

  QSystemTrayIcon* mTrayIcon;
  QMenu* mTrayIconMenu;

  LockScreen* mLockScreen;
  QCursor mCursor;
  QTimer mMouseHideTimer;
  std::map<QString, BulbWidget*> mBulbWidgets;
  BluetoothManager mBluetoothManager;
  WifiManager mWifiManager;
  tuya::TuyaWorker mTuyaWorker;
};

#endif // MAINWIDGET_H
