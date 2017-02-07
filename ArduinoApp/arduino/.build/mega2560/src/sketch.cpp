#include <Arduino.h>
#include <Servo.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <Servo.h>

#define light1 41
#define light2 6
#define light3 2 
#define light4 5
#define light5 3

Servo servo;
int pos=0;

int incomingByte = 0;
long randomNumber;

void setup() {
  	pinMode(light1,OUTPUT);
  	pinMode(light2,OUTPUT);
  	pinMode(light3,OUTPUT);
  	pinMode(light4,OUTPUT);
  	pinMode(light5,OUTPUT);

  	servo.attach(10);
  
  	Serial.begin(57600);

	randomSeed(40);
}

void loop() {
  	String input;

          // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                input = Serial.readString();
                String inputFlag=input.substring(0,1);
                if(input=="001"){
                    	digitalWrite(light1,!digitalRead(light1));
                }
                else if(input=="010"){
                    	digitalWrite(light2,!digitalRead(light2));
                }
                else if(input=="011"){
                    	digitalWrite(light3,!digitalRead(light3));
                }
                else if(input=="100"){
                    	digitalWrite(light4,!digitalRead(light4));
                }
                else if(input=="101"){
                    	digitalWrite(light5,!digitalRead(light5));
                }
		else if(inputFlag=="d")
		{
			input=input.substring(1);
                      	//servo.write(input.toInt());              // tell servo to go to position in variable 'pos'
                      	int door = map(input.toInt(), 0,180, 163, 60);
                      	Serial.println(door);
                      	servo.write(door);
                      	delay(15); 
		}
		else if(inputFlag=="s")
		{
			input=input.substring(1); //determine which sensor to read
			int sensor = input.toInt();
			switch(sensor)
			{
				case 1:
					// temperature/humidity sensor
					Serial.println(String(random(10,15)) + "," + String(random(3,7)) );
					break;
				case 2:
					// Gas, CO sensor
					Serial.println(String(random(2,6)) + "," + String(random(1,3)) );
					break;
				default:
					Serial.println("0xFFF");
			}
		}
  		delay(1000);
	}
}
