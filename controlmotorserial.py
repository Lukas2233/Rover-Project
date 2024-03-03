from flask import Flask, render_template, request
import serial
import threading

app = Flask(__name__)

# Define the serial ports and baud rate
ser1 = serial.Serial('/dev/ttyACM0', 9600)
ser2 = serial.Serial('/dev/ttyACM1', 9600)

# Function to send command to Arduino
def send_command(command, port):
    if port == 1:
        ser1.write(command.encode())
    elif port == 2:
        ser2.write(command.encode())

# Background thread to continuously check for commands
def command_checker():
    while True:
        # Check if there's a command in the request queue
        if 'command' in request.args:
            command = request.args['command']
            port = int(request.args.get('port', 1))  # Default to port 1 if not specified
            send_command(command, port)
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
    send_command(command, 1)  # Send command to port 1 by default
    return f"Command '{command}' sent to Arduino on port 1."

@app.route('/send_command/<command>/<int:port>')
def handle_command_with_port(command, port):
    send_command(command, port)
    return f"Command '{command}' sent to Arduino on port {port}."

if __name__ == '__main__':
    app.run(debug=True, host='192.168.86.23', port=5001)