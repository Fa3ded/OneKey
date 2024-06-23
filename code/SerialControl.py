import serial
import pyautogui

# This will not work on Colab because Colab cannot access local serial ports
# Replace '/dev/tty.usbmodem1101' with the actual port your Arduino is connected to
ser = serial.Serial('/dev/tty.usbmodem1101', 9600)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line == "CLICK":
            pyautogui.click()