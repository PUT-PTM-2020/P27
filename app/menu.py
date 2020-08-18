from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout
from PyQt5.QtWidgets import QLineEdit, QPushButton, QHBoxLayout, QMessageBox
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import distanceSensor
import servomechanism
import membranePump

data0 = "1"
data1 = "2"
data2 = "3"
data3 = "4"


class Menu(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.interfejs()

    def interfejs(self):
        print("Main wind")
        label1 = QLabel("              Hello in Drink Master Servis!", self)
        font = QtGui.QFont()
        font.setPointSize(16)
        label1.setFont(font)

        distanceSensor = QPushButton("&DISTANCE SENSOR",self)
        servomechanism = QPushButton("&SERVOMECHANISM", self)
        membranePumps = QPushButton("&MEMBRANE PUMPS", self)

        distanceSensor.clicked.connect(self.showDistanceSensor)
        servomechanism.clicked.connect(self.showServomechanism)
        membranePumps.clicked.connect(self.showMembranePumps)

        font = QtGui.QFont()
        font.setPointSize(12)

        distanceSensor.setFont(font)
        servomechanism.setFont(font)
        membranePumps.setFont(font)

        ukladT = QGridLayout()
        ukladT.addWidget(label1,0, 0,1,3)
        ukladT.addWidget(distanceSensor)
        ukladT.addWidget(servomechanism)
        ukladT.addWidget(membranePumps)

        self.setLayout(ukladT)
        self.setGeometry(50, 50, 300, 100)
        # self.setWindowIcon(QIcon("photo.png")) #ikonka trzeba dodać
        self.setWindowTitle("Drink Master Servis")
        self.show()



    def showDistanceSensor(self):
        print("Open Window DistanceSensor")
        self.ds = distanceSensor.DistanceSensor()
        self.ds.show()
        self.close()

    def showServomechanism(self):
        print("Open Window Servomechanism")
        self.s = servomechanism.Servomechanism()
        self.s.show()
        self.close()

    def showMembranePumps(self):
        print("Open Window MembranePumps-XD")
        self.mp = membranePump.MembranePump()
        self.mp.show()
        self.close()