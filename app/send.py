#import serial
import time


#device = serial.Serial('COM5', 9600 , timeout = 0.01)
class Send:
    def __init__(self):
        print("")


#   def send(self, i):
#       while True:
#          device.write(i.encode())
#            time.sleep(1)

#        while True:
#            x = device.readline()

#       return x

    def send(self, i):
        if i == 'a':
            return "1;1.55"
        elif i == 'b':
            return "1;0.56"
        elif i == 'c':
            return "0;1.11;1.09"
        else:
            return "E"



