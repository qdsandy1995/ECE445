import serial
import sys
import os


def main():
    ser = serial.Serial("Com9",9600)  #Replace with the number of Com port connected to the chip 
    message = ser.readline()
    while True:
        option = raw_input("Enter 1 to get Current, Enter 2 to get Voltage, Enter 3 to get Power, Enter 4 to get temperature, Enter 5 to quit\n")
        if option == "1":
            current = message.split('/')[0]
            print(current + "A");
        elif option == "2":
            voltage = message.split('/')[1]
            print(voltage + "V")
        elif option == "3":
            power = message.split('/')[2]
            print(power + "W")
        elif option == "4":
            temperature = message.split('/')[3]
            print(temperature + " C")
        else:
            break
    ser.close()

if __name__ == '__main__':
    main()
