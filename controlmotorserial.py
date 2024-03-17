#!/usr/bin/env python3

from flask import Flask, render_template
import smbus
import time

app = Flask(__name__)
 
# Raspberry Pi Zero W's I2C bus number
bus = smbus.SMBus(1)

# Arduino Mega's I2C address
ARDUINO_ADDRESS = 0x08

# Function to send command to Arduino
def send_data(data):
    bus.write_i2c_block_data(ARDUINO_ADDRESS, 0, [ord(c) for c in data])

@app.route('/')
def index():
    return render_template('index.html')

# Define route to handle commands
@app.route('/send_command/<command>')
def handle_command(command):
    send_data(command)  # Corrected function name
    return f"Command '{command}' sent to Arduino."

if __name__ == '__main__':
    app.run(debug=True, host='192.168.86.23', port=5001)