import smarthomemqtt as mqtt
import smarthomeutils as utils

class Main:
    def __init__(self):
	self.helper = utils.Utils()
        self.mqtt_service = mqtt.SmartHomeMqttClient(self.helper.get_rpi_ip('eth0'), self.helper)
