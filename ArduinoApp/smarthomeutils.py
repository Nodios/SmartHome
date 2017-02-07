import glob

import socket
import fcntl
import struct

class Utils:      
    def get_rpi_ip(self, ifname):
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        return socket.inet_ntoa(fcntl.ioctl(
            s.fileno(),
            0x8915,  # SIOCGIFADDR
            struct.pack('256s', ifname[:15])
        )[20:24])

    def get_arduino_port(self):
        return glob.glob("/dev/ttyACM*")[0]
