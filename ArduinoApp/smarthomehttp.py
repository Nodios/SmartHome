import requests as http
import json
from time import gmtime, strftime

class SmartHomeHttpClient:
    ROOT_URL = "http://smart-home-tkr.azurewebsites.net/"
    GAS_ENDPOINT = "api/Gas"
    MOVEMENT_ENDPOINT = "api/Movement"
    FLOOD_ENDPOINT = "api/Flood"
    TEMPERATURE_ENDPOINT = "api/Temperature"

    def __init__(self):
        print "HTTP client running"

    # GAS_ENDPOINT
    def get_gas(self):
        req = http.get(self.ROOT_URL + self.GAS_ENDPOINT)
        print json.dumps(req.json(), inden=4, sort_keys=True)

    def add_gas(self, co2, co, gas):
        data = {
            "Co": co,
            "Co2": co2,
            "Gas1": gas
        }

        # form a requests
        req = http.post(self.ROOT_URL + self.GAS_ENDPOINT, json=data)
        if req.status_code is 200:
            print str(req.status_code) + ": data sent"
        else:
            print "An error has occurred during POST to GasController"
        
    def add_temperature_and_humidity(self, temperature, humidity):
        data = {
            "MeasuredTemperature": temperature,
            "Humidity": humidity
        }

        req = http.post(self.ROOT_URL + self.TEMPERATURE_ENDPOINT, json=data)
        if req.status_code is 200:
            print str(req.status_code) + ": data sent"
        else:
            print "An error has occurred during POST to TemperatureController"

    def add_movement(self):
        data = {
            "MovementDetected": strftime("%Y-%m-%dT%H:%M:%S", gmtime())
        }
        req = http.post(self.ROOT_URL + self.MOVEMENT_ENDPOINT, json=data)
        if req.status_code is 200:
            print str(req.status_code) + ": data sent"
        else:
            print "An error has occurred during POST to MovementController"

    def add_water_level(self, water_level):
        data = {
            "MeasuredWaterLevel": water_level
        }
        req = http.post(self.ROOT_URL + self.FLOOD_ENDPOINT, json=data)
        if req.status_code is 200:
            print str(req.status_code) + ": data sent"
        else:
            print "An error has occurred during POST to WaterLevelController"

