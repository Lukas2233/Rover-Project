from flask import Flask, render_template, request
import serial
import threading
import glob

app = Flask(__name__)

# Find all available serial ports
ports = glob.glob('/dev/ttyACM*')

# Iterate through each port and try to connect
for port in ports:
    try:
        ser = serial.Serial(port, 9600)
        break
    except serial.SerialException:
        pass
else:
    raise Exception("No Arduino found on any serial port")


# Function to send command to Arduino
def send_command(command):
    ser.write(command.encode())

# Background thread to continuously check for commands
def command_checker():
    while True:
        # Check if there's a command in the request queue
        if 'command' in request.args:
            command = request.args['command']
            send_command(command)
        # Sleep for a short interval before checking again
        time.sleep(0.1)

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