from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout
from PyQt5.QtWidgets import QLineEdit, QPushButton, QHBoxLayout, QMessageBox
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import servomechanism
import membranePump
import send
import menu

global data0
global data1
global data2
global data3


class DistanceSensor(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        pom = send.Send()
        self.send(pom.send('a'))
        self.interfejs()

    def interfejs(self):
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

        label2 = QLabel("Distance Sensor:")
        font = QtGui.QFont()
        font.setPointSize(14)
        label2.setFont(font)

        if data0 != "E":
            label3 = QLabel("ON")
            label4 = QLabel(data2 + "[MM]")
        else:
            label3 = QLabel("OFF")
            label4 = QLabel(" ")




        font = QtGui.QFont()
        font.setPointSize(11)
        label3.setFont(font)
        label4.setFont(font)

        ukladT = QGridLayout()
        ukladT.addWidget(label1,0, 0,1,3)
        ukladT.addWidget(distanceSensor)
        ukladT.addWidget(servomechanism)
        ukladT.addWidget(membranePumps)
        ukladT.addWidget(label2,3,0,1,1)
        ukladT.addWidget(label3,4,0,1,1)
        ukladT.addWidget(label4,4,1,1,1)

        self.setLayout(ukladT)
        self.setGeometry(50, 50, 300, 100)
        # self.setWindowIcon(QIcon("photo.png")) #ikonka trzeba dodać
        self.setWindowTitle("Drink Master Servis")
        self.show()

    def showDistanceSensor(self):
        print("Open Window DistanceSensor")
        self.ds = DistanceSensor()
        self.ds.show()
        self.close()

    def showServomechanism(self):
        print("Open Window Servomechanism")
        self.s = servomechanism.Servomechanism()
        self.s.show()
        self.close()

    def showMembranePumps(self):
        print("Open Window MembranePumps")
        self.mp = membranePump.MembranePump()
        self.mp.show()
        self.close()

    def send(self, i):
        global data0
        global data1
        global data2
        global data3
        data0 = i
        if data0:
            if data0[1] == ';':
                data1 = data0[0]
                if data1 == '0':
                    data2 = data0[2]
                    data2 += data0[3]
                    data2 += data0[4]
                    data2 += data0[5]

                    data3 = data0[7]
                    data3 += data0[8]
                    data3 += data0[9]
                    data3 += data0[10]

                elif data1 == '1':
                    data2 = data0[2]
                    data2 += data0[3]
                    data2 += data0[4]
                    data2 += data0[5]
                    data3 = "0"
                elif data1 == '2':
                    data2 = data0[2]
                    data2 += data0[3]
                    data2 += data0[4]
                    data2 += data0[5]
                    data3 = "0"
            else:
                data2 = data0[0]
                data2 += data0[1]
                data2 += data0[2]
                data2 += data0[3]
                data3 = "0"