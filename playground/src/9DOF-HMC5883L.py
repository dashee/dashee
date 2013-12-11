import smbus
import time
bus = smbus.SMBus(1)
address = 0x1e

#bus.write_byte_data(address, 0x00, 0x00)
#bus.write_byte_data(address, 0x01, 0x00)
bus.write_byte_data(address, 0x02, 0x00)
time.sleep(0.01)

while True:
    print [
            (bus.read_byte_data(address, 0x03) << 8) | bus.read_byte_data(address, 0x04),
            (bus.read_byte_data(address, 0x05) << 8) | bus.read_byte_data(address, 0x06),
            (bus.read_byte_data(address, 0x07) << 8) | bus.read_byte_data(address, 0x08),
        ]
    
    time.sleep(0.01)
