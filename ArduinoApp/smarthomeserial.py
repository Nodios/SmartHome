import serial

class SerialPortClient:
    def __init__(self, port):
        print "Serial communication system initialized"
        self.serial_com = serial.Serial(str(port), 57600, timeout=3)
        print "Serial communication system running"

    def close_connection(self):
        return self.serial_com.close()

    def read_data(self):
        while(True):
            data = self.serial_com.readline()
            #Check incoming data
            print str(data)
            if "Read fail" in data:
                data = data[9:]
            a = data.replace("\r\n", "").split(';')

            if "exit" in str(data):
                self.close_connection()
                break
            return a
        
    def write_data(self, data):
        self.serial_com.write(str(data))
            
