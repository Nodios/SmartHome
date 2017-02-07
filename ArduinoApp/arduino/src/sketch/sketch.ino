#include <Servo.h>
#include "DHT.h"

// serial port setup
#define SERIAL_PORT_BAUD 57600

// LED pin numbers
#define LED1 41 // front door pin
#define LED2 6
#define LED3 2 
#define LED4 5
#define LED5 3

// Door servo pin
#define SERVO_OUTPUT_PIN 10

// Flood sensor
#define FLOOD_INPUT_PIN 52

// Temperature & humidity sensor
#define DHT_INPUT_PIN 53
#define DHT_TYPE DHT22

// Movement sensor
#define PIR_INPUT_PIN 49

// Dust sensor
#define DUST_INPUT_PIN 4
#define DUST_LED_PIN 46

#define MQ6_INPUT_PIN A1 // LPG, butane gas
#define MQ7_INPUT_PIN A2 // Carbon Monoxide

// Helper constants
#define NOMINAL_TEMPERATURE 24
#define DOOR_CLOSED 163
#define DOOR_OPENED 60

// Instantiate servo with position 0
Servo servo;
int pos=0;

// Flood sensor initial value
int floodSensorState = 0;

// PIR initial value
int readPirSensor = 0;

// Dust sensor initial value
int dustValue = 0;

// Temperature & humidity
DHT dht(DHT_INPUT_PIN, DHT_TYPE);

// Tester random number holder
long randomNumber;

void setup() {
	// LED pins
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
	pinMode(LED4,OUTPUT);
	pinMode(LED5,OUTPUT);

  // Serial communication
  Serial.begin(SERIAL_PORT_BAUD);

	// Flood sensor
	pinMode(FLOOD_INPUT_PIN, INPUT);

	// Dust sensor
	pinMode(DUST_LED_PIN, OUTPUT);

	// Door servo setup
	servo.attach(SERVO_OUTPUT_PIN);
	//serial.write(DOOR_CLOSED); // close the door

	// Movement sensor
	pinMode(PIR_INPUT_PIN, INPUT);

	// Temperature & humidity
	dht.begin();

	

	// RNG for testing purposes
	randomSeed(40);
}

void loop() {
  String input;

	// go in only when you receive data
	if (Serial.available() > 0) 
	{
		// read the incoming byte:
		input = Serial.readString();
		String inputFlag = input.substring(0,1);
		if(input=="001"){
				digitalWrite(LED1,!digitalRead(LED1));
		}
		else if(input=="010"){
				digitalWrite(LED2,!digitalRead(LED2));
		}
		else if(input=="011"){
				digitalWrite(LED3,!digitalRead(LED3));
		}
		else if(input=="100"){
				digitalWrite(LED4,!digitalRead(LED4));
		}
		else if(input=="101"){
				digitalWrite(LED5,!digitalRead(LED5));
		}
		else if(inputFlag=="l") // turns all LEDs off
		{
			LightsOff();
		}
		else if(inputFlag=="d")
		{
			input = input.substring(1);
			int door = map(input.toInt(), 0,180, DOOR_CLOSED, DOOR_OPENED);
			servo.write(door);
		}
		else if(inputFlag=="s")
		{
			input = input.substring(1); //determine which sensor to read
			int sensor = input.toInt();
			int data1;
			float temp[2], gas[2], data2;
			switch(sensor)
			{
				case 1: // temperature/humidity sensor
					ReadDhtSensor(temp);
					Serial.println(String(int(temp[0])) + ';' + String(int(temp[1])));
					break;
				case 2: // Gas, CO sensor
					ReadMqSensor(gas);
					Serial.println(String(int(gas[0])) + ';' + String(int(gas[1])));
					break;
				case 3: // flood sensor
					ReadFloodSensor(data1);
					Serial.println(String(data1));
					break;
				case 4: // dust sensor(if it works)
					ReadDustSensor(data2);
					Serial.println(String(int(data2)));
					break;
				default:
					Serial.println("0xFFF");
			}
		}
	}

	if(ReadPirSensor()){
		if(readPirSensor % 10 == 0)
		{
			Serial.println("movement");
		}
		readPirSensor++;
	}
}

void ReadDhtSensor(float data[2]){
	float temperature = dht.readTemperature(); // read temperature in Celsius
	float humidity = dht.readHumidity();

	if(isnan(temperature))
	{
		data[0] = 0;
	}else{
		data[0] = temperature;
	}

	if(isnan(humidity))
	{
		data[1] = 0;
	}else{
		data[1] = humidity;
	}
}

void ReadMqSensor(float data[2]){
	float gas = analogRead(MQ6_INPUT_PIN);
	float co = analogRead(MQ7_INPUT_PIN);

	if(isnan(gas))
	{
		data[0] = 0;
	}else{
		data[0] = gas;
	}

	if(isnan(co))
	{
		data[1] = 0;
	}else{
		data[1] = co;
	}
}

bool ReadPirSensor()
{
	int result = digitalRead(PIR_INPUT_PIN);

	if(result == LOW){
		return false;
	}

	return true;
}

// simulated flood sensor
void ReadFloodSensor(int data)
{
	floodSensorState = digitalRead(FLOOD_INPUT_PIN);

	if(floodSensorState == HIGH)
	{
		data = random(60, 100);
	}
	else{
		data = random(1, 40);
	}
}

// fire detector
void ReadDustSensor(float data)
{
	digitalWrite(DUST_LED_PIN, HIGH);
	delay(280); // LED ligts dust particles
	data = analogRead(DUST_INPUT_PIN);
	delay(40); // failsafe 
	digitalWrite(DUST_LED_PIN, LOW);
}

void LightsOn()
{
	digitalWrite(LED1, HIGH);
	digitalWrite(LED2, HIGH);
	digitalWrite(LED3, HIGH);
	digitalWrite(LED4, HIGH);
	digitalWrite(LED5, HIGH);
}

void LightsOff()
{
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, LOW);
	digitalWrite(LED4, LOW);
	digitalWrite(LED5, LOW);
}
