from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QGridLayout
from PyQt5.QtWidgets import QLineEdit, QPushButton, QHBoxLayout, QMessageBox
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import logIn

if __name__ == '__main__':
    app=QApplication(sys.argv)
    window = logIn.LogIn()
    sys.exit(app.exec_())