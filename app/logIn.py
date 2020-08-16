from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout
from PyQt5.QtWidgets import QLineEdit, QPushButton, QHBoxLayout, QMessageBox
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import menu

class LogIn(QWidget):
    def __init__(self,parent=None):
        super().__init__(parent)

        self.interfejs()

    def interfejs(self):

        label1 = QLabel("Login: ", self)
        label2 = QLabel("Password: ", self)

        self.login = QLineEdit()
        self.password = QLineEdit()

        ok = QPushButton("&OK ", self)

        t1 = QGridLayout()
        t1.addWidget(label1,0,0)
        t1.addWidget(self.login,0,1)
        t1.addWidget(label2, 1, 0)
        t1.addWidget(self.password, 1, 1)
        t1.addWidget(ok,2,2)
        self.setLayout(t1)

        #wcisniecie ok - weryfikacja
        ok.clicked.connect(self.verification)

        self.setGeometry(50, 50, 300, 90)
        #self.setWindowIcon(QIcon("photo.png")) #ikonka trzeba dodać
        self.setWindowTitle("Drink Master Servis")
        self.show()

    def verification(self):
        good_login = ["Mateusz", "Tymon", "Kamil",""]
        good_password = ["Olejnik", "Jakubowski", "Mosek",""]
        l1 = str(self.login.text())
        p1 = str(self.password.text())

        i = 0
        for x in good_login:
            if x == l1:
                if p1 == good_password[i]:
                    self.openMainWindow()
                    i = 100
            i = i + 1

        if i < 100:
            QMessageBox.warning(self, "ERROR", "ERROR! The login or password is incorrect!", QMessageBox.Ok)

    def openMainWindow(self):
        print("Open Main Window")
        self.mw = menu.Menu()
        self.mw.show()
        self.close()
