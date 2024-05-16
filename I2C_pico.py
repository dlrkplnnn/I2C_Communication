import machine
from machine import Pin
import time

# Define the I2C bus
in1=Pin(16,Pin.OUT)
in2=Pin(17,Pin.OUT)
i2c = machine.I2C(0)

# Address of the Arduino Uno

arduino_address = 8
while True:
# Data to be sent
    data_to_send = b'K'

    try:
    # Send data to Arduino Uno
        i2c.writeto(arduino_address, data_to_send)
        print("Data sent to Arduino Uno successfully.")

        time.sleep(1)

    # Read data from Arduino Uno
        response = i2c.readfrom(arduino_address, 2)  # Reading 2 bytes of response
        print("Response from Arduino Uno:", response)
        
        if response==b'Pi':
            in1.value(0)
            in2.value(1)
            time.sleep(1)
        else:
            in1.value(1)
            in2.value(1)
            time.sleep(1)
            
            
    except Exception as e:
        print("Error:", e)

