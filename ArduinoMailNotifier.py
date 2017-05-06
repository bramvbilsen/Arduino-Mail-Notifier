import serial
import time
import random
import atexit
import GmailHandler as gm

def main():
    try:
        s = serial.Serial('COM3', 9600) #port is 11 (for COM12), and baud rate is 9600
        time.sleep(2)    #wait for the Serial to initialize
        counter = 0
        while True:
            if ord(s.read()) == 1:
                print("Permission granted")
                messages = gm.getInboxMessages()
                time.sleep(5)
                amountOfMessages = str(len(messages)) if len(messages) < 10 else "9+"
                currentMessage = messages[counter] if len(messages[counter]) < 16 else messages[counter][0:13] + "..."
                msg = "New messages: " + amountOfMessages + '\n' + currentMessage + '\n'
                print(msg)
                s.write(msg.encode())
                if (counter == len(messages) - 1):
                    counter = 0
                else:
                    counter += 1
            else:
                print("Waiting for permission")
            
    finally:
        print("Quitting script")
        quitSignal = "-1" + '\n'
        s.write(quitSignal.encode())

if __name__ == '__main__':
    main()
