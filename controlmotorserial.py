#!/usr/bin/env python3

import smbus
import time
import bluetooth

# Raspberry Pi Zero W's I2C bus number
bus = smbus.SMBus(1)

# Arduino Mega's I2C address
ARDUINO_ADDRESS = 0x08

# Bluetooth server function to handle incoming connections and commands
def bluetooth_server():
    server_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    server_socket.bind(("", bluetooth.PORT_ANY))
    server_socket.listen(1)

    port = server_socket.getsockname()[1]

    bluetooth.advertise_service(server_socket, "BluetoothServer",
                                service_id=bluetooth.SERIAL_PORT_CLASS,
                                profiles=[bluetooth.SERIAL_PORT_PROFILE])

    print("Waiting for connection on RFCOMM channel", port)

    client_socket, client_info = server_socket.accept()
    print("Accepted connection from", client_info)

    while True:
        try:
            data = client_socket.recv(1024).decode().strip()
            if not data:
                break
            print("Received from Bluetooth:", data)
            send_data_to_arduino(data)
        except Exception as e:
            print("Error:", e)
            break

    print("Closing connection")
    client_socket.close()
    server_socket.close()

# Function to send command to Arduino over I2C
def send_data_to_arduino(data):
    bus.write_i2c_block_data(ARDUINO_ADDRESS, 0, [ord(c) for c in data])

if __name__ == '__main__':
    bluetooth_server()
