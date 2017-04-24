import serial
import sys
import os
#ser = serial.Serial("Com4",9600)

def linear_data_form(message):
    DataLow,DataHigh,Garbage = message.split(' ')
    a = int(DataLow,16)
    b = int(DataHigh,16)
    y = ((b & 7) << 8) + a; 
    n = b >> 3
    #print(y)
    if((n >> 4) == 1):
        n = n^31
        n += 1
        n = -n
    #print(n)
    return y*(2**n)


def main():
    filename = "Power Supply Log"
    count = 0
    option = raw_input("Enter 1 to get Current, Enter 2 to get Voltage, Enter 3 to get Power, Enter 4 to get tempreture\n")
    while True:
        if (count < 5):
            print("wait\n")
            count += 1
            continue
        message = ser.readline()
        #message = "A6 C8 Garbage"
        current = linear_data_form(message)
        print(current)
        #open(filename, 'a+').writelines(message)
        break
if __name__ == '__main__':
    main()
