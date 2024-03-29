import json
import os
import signal

from PyQt5.QtCore import QEvent, QObject
from PyQt5.QtWidgets import (
    QApplication,
    QHBoxLayout,
    QVBoxLayout,
    QSizePolicy,
    QSpacerItem,
    QWidget,
)

from managers import BluetoothManager, WifiManager
from widgets import BluePulsePiWidget, BulbWidget, WifiWidget, LockScreen

signal.signal(signal.SIGINT, signal.SIG_DFL)


class MainWidget(QWidget):
    def __init__(self):
        super(MainWidget, self).__init__()

        self.setGeometry(0, 0, 1920, 1080)

        self.setStyleSheet("QWidget { font-size: 42pt; padding: 50px; }")

        self.bluetoothManager = BluetoothManager()
        self.wifiManager = WifiManager()

        presets = json.load(open("presets.json", "r"))

        devices = json.load(open("tinytuya/devices.json", "r"))
        self.widgets = []
        for d in devices:
            if d["id"] in presets:
                p = presets[d["id"]]
            else:
                p = presets["default"]

            if d["category"] == "dj":  # light bulb
                self.widgets.append(BulbWidget(d, p))

        # set up layout
        l = QHBoxLayout()
        for w in self.widgets:
            l.addWidget(w)

        l2 = QVBoxLayout()
        l2.addLayout(l)
        l2.addSpacerItem(QSpacerItem(0, 0, vPolicy=QSizePolicy.Expanding))

        l2.addWidget(WifiWidget(self.wifiManager))

        # only for BluePulsePi
        if os.path.exists("/home/pi/BluePulsePi"):
            l2.addWidget(BluePulsePiWidget(self.bluetoothManager))

        self.setLayout(l2)

        # set up lockscreen
        self.lockScreen = LockScreen(self, self.bluetoothManager, self.wifiManager)

        self.installEventFilter(self)
        children = self.children()
        while children:
            c = children.pop(0)
            c.installEventFilter(self)
            children.extend(c.children())

        self.show()

    def eventFilter(self, obj: QObject, event: QEvent) -> bool:
        if event.type() == QEvent.MouseButtonPress:
            self.lockScreen.resetLockTimer()
            return False
        else:
            return super(MainWidget, self).eventFilter(obj, event)


if __name__ == "__main__":
    app = QApplication([])

    w = MainWidget()

    app.exec_()
