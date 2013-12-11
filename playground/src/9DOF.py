import smbus
import time
bus = smbus.SMBus(1)
address = 0x1e

#bus.write_byte(address, 0x3c)
#bus.write_byte(address, 0x00)
#bus.write_byte(address, 0x70)

#bus.write_byte(address, 0x3c)
#bus.write_byte(address, 0x01)
#bus.write_byte(address, 0xA0)

bus.write_byte_data(address, 0x02, 0x0)
#bus.write_byte(address, 0x00)
time.sleep(1)

while True:
    #bus.write_byte_data(address, 0x3c, 0x03)
    #bus.write_byte(address, 0x06)

    a = [
            bus.read_byte_data(address, 0x03),
            bus.read_byte_data(address, 0x04),
            bus.read_byte_data(address, 0x05),
            bus.read_byte_data(address, 0x06),
            bus.read_byte_data(address, 0x07),
            bus.read_byte_data(address, 0x08),
            bus.read_byte_data(address, 0x09)
        ]
    print a
    
    time.sleep(0.01)
