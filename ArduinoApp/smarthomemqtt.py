import paho.mqtt.client as mqtt

import smarthomeserial as serial
import smarthomehttp as http
import smarthomeutils as utils

class SmartHomeMqttClient:
    def __init__(self, rpi_ip, helper):
        """
        This is main method!

        Input: RaspberryPI IP address on local network
        Input: Instance of SmartHomeSerialReader class

        This class exposes core functionalities of Paho.MQTT library

        Each message received via MQTT is sent to serial port
        """

        self.serial_service = serial.SerialPortClient(helper.get_arduino_port())
        self.http_service = http.SmartHomeHttpClient()

        print "MQTT client initialized"
        self.client = mqtt.Client()
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.on_publish = self.on_publish
        self.client.on_subscribe = self.on_subscribe

        self.client.connect(str(rpi_ip))
        self.client.subscribe("android/control")
        self.client.loop_forever()
        #self.run(str(rpi_ip))
        #print "MQTT client running"
    
    def on_connect(self, client, obj, flags, rc):
        # rc = 0 is OK
        print "MQTT connected with result code " + str(rc)

    def on_message(self, client, obj, msg):
        # incoming message
        print msg.topic + " " + str(msg.qos) + " " + str(msg.payload)

        # TODO: do something with the message
        self.analize_message(str(msg.payload))
    
    def on_publish(self, client, obj, mid):
        # used for publishing
        print str(mid)

    def on_subscribe(self, client, obj, mid, granted_qos):
        # used for subscribing
        print "Subscribed: " + str(mid) + " " + str(granted_qos)

    def on_log(self, client, obj, level, string):
        # logging
        print string

    def analize_message(self, msg):
        temp = self.serial_service.read_data()
        if temp == "movement":
            print "Movement detected"
            self.http_service.add_movement()
            temp = ''

        if str(msg) == "s1":
            # Temperature,Humidity
            print "Requesting temperature & humidity"
            self.serial_service.write_data("s1")
            temp_humid = self.serial_service.read_data()
            print "Data received: " + str(temp_humid)
            print "Sending to server"
            self.http_service.add_temperature_and_humidity(temp_humid[0], temp_humid[1])
        elif str(msg) == "s2":
            # Gas, Co, Co2
            print "Requesting Gas, Co, Co2"
            self.serial_service.write_data("s2")
            gas_co = self.serial_service.read_data()
            print "Data received: " + str(gas_co)
            print "Sending to server"
            self.http_service.add_gas(0, gas_co[0], gas_co[1])
        elif str(msg) == "s3":
            print "Requesting flood level"
            self.serial_service.write_data("s4")
            flood = self.serial_service.read_data()
            print "Data received: " + str(flood)
            print "Sending to server"
            self.http_service.add_water_level(flood)
        elif str(msg) == "s4":
            # dust
            print "Requesting dust sensor reading"
            self.serial_service.write_data("s4")
            dust = self.serial_service.read_data()
            print "Data received: " + str(dust)
            print "Sending to server"
            print "Cannot send to server - not implemented"
        else:
	        print str(msg)
            self.serial_service.write_data(str(msg))
