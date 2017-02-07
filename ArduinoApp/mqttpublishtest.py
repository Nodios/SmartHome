import paho.mqtt.client as paho
import smarthomeutils as utils

def on_publish(client, userdata, mid):
	print "mid: " + str(mid)

# helper
helper = utils.Utils()

client = paho.Client()
client.on_publish = on_publish
client.connect(helper.get_rpi_ip('eth0'), 1883, 60)
client.loop_start()

# THE REAL DEAL
def send_mqtt_msg(message):
	client.publish("android/control", str(message))

