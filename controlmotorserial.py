from flask import Flask, render_template, request
import serial
import threading
import keyboard  # Install using: pip install keyboard

app = Flask(__name__)
 
# Define the serial port and baud rate
ser = serial.Serial('/dev/ttyACM0', 9600)

# Function to send command to Arduino
def send_command(command):
    ser.write(command.encode())

# Background thread to continuously check for commands
def command_checker():
    while True:
        # Read keyboard inputs continuously
        if keyboard.is_pressed('w'):
            send_command('w')
        elif keyboard.is_pressed('s'):
            send_command('s')
        elif keyboard.is_pressed('q'):
            send_command('q')
        elif keyboard.is_pressed('d'):
            send_command('d')
        elif keyboard.is_pressed('a'):
            send_command('a')
        elif keyboard.is_pressed('h'):
            send_command('h')

# Start the background thread
thread = threading.Thread(target=command_checker)
thread.daemon = True
thread.start()

@app.route('/')
def index():
    return render_template('index.html')

# Define routes to handle commands
@app.route('/send_command/<command>')
def handle_command(command):
    send_command(command)
    return f"Command '{command}' sent to Arduino."

if __name__ == '__main__':
    app.run(debug=True, host='192.168.86.23', port=5001)
