#!/usr/bin/env python3

from flask import Flask, render_template
import serial

app = Flask(__name__)
 
# Define the serial port and baud rate
ser = serial.Serial('/dev/ttyACM0', 9600)

# Function to send command to Arduino
def send_command(command):
    ser.write(command.encode())

@app.route('/')
def index():
    return render_template('index.html')

# Define route to handle commands
@app.route('/send_command/<command>')
def handle_command(command):
    send_command(command)
    return f"Command '{command}' sent to Arduino."

if __name__ == '__main__':
    app.run(debug=True, host='192.168.86.23', port=5001)
