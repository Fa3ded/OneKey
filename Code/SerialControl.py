import serial
import pyautogui
import subprocess

# This will not work on Colab because Colab cannot access local serial ports
# Replace '/dev/tty.usbmodem1101' with the actual port your Arduino is connected to
ser = serial.Serial('/dev/tty.usbmodem11301', 9600)

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        if line == "ONE":
            subprocess.call(
    ["/usr/bin/open", "-W", "-n", "-a", "/Applications/CapCut.app"]
    )
        if line == "TWO":
                subprocess.call(
    ["/usr/bin/open", "-W", "-n", "-a", "/Applications/UltiMaker Cura.app"]
    )
        if line == "HOLD":
                subprocess.call(
    ["/usr/bin/open", "-W", "-n", "-a", "/Users/2027.joelbraddy/Library/Application Support/Autodesk/webdeploy/production/6997599ab67b7e881f25c2311930a09bc5ac662f/Autodesk Fusion 360.app"]
    )

