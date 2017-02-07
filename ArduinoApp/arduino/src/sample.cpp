#include <AFMotor.h>
#include <MenuBackend.h>
#include <LiquidCrystal.h>
#include "DHT.h"
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>
#define DHTPIN 53
#define DHTTYPE DHT22
#define CLAP_THRESHOLD 600
#define CLAP_GAP_IN_MS 300
#define CLAP_GAP_TOLERANCE 65
#define CLAP_GAP_MIN (CLAP_GAP_IN_MS - CLAP_GAP_TOLERANCE)
#define CLAP_GAP_MAX (CLAP_GAP_IN_MS + CLAP_GAP_TOLERANCE)
unsigned long mLastClap;
boolean led3Status = false;
const int floodSensors = 52; //  the number of the Flood Sensor pin
int floodSensorState = 0;    // variable for reading the floodSensors status
int dustPin = 4;             //dust sensor
int dustVal = 0;             //dust sensor
int ledPower = 46;           //dust sensor
int delayTime = 280;         //dust sensor
int delayTime2 = 40;         //dust sensor
float offTime = 9680;        //dust sensor
int buttonStatestop1 = 0;
int buttonStatestop2 = 0;
const int buttonPin = 50;
int buttonState = 0;
const int buttonPinLeft = 35;  // pin for the Up button
const int buttonPinRight = 33; // pin for the Down button
const int buttonPinEsc = 34;   // pin for the Esc button
const int buttonPinEnter = 36; // pin for the Enter button
const int buttonPinBrig1 = 31;
const int buttonPinBrig2 = 32;
const int analogInPin1 = A1;
const int analogInPin2 = A2;
const int buttonPinstop1 = 51; //up
const int buttonPinstop2 = 47; //down
const int motorPin1 = 42;
const int motorPin2 = 44;
const int motorPin3 = 43;
const int motorPin4 = 45;
const int motorDelay = 2;
Servo myservo;
int pos = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue = 0;
int pinSpeaker = 50;
int vel = 210;
AF_DCMotor motor(1, MOTOR12_64KHZ);
int centreButtonState1 = 0;
int centreButtonState2 = 0;
int centreButtonState3 = 0;
int centreButtonState4 = 0;
int centreButtonState5 = 0;
int centreButtonState6 = 0;
int centreButtonState7 = 0;
int centreButtonState8 = 0;
int centreButtonState9 = 0;  // for window UP
int centreButtonState10 = 0; // WINDOW DOWN
int centreButtonState11 = 0; // WINDOW STOP MODE
int centreButtonState12 = 0;
int centreButtonState13 = 0;
int brightness1 = 100; // stores brightness level
int brightness2 = 100;
int brightness3 = 100;
int brightness4 = 100;
int mode = 0;
int lastButtonPushed = 0;
int RECV_PIN = 30;
int led1 = 5; //5mm White LED
int led2 = 3;
int led3 = 6; //clap-clap_led
int led4 = 2; //led hodnik
int temp = 24;
int photocellPin = 3; // the cell and 10K pulldown are connected to a0
int photocellReading;
int PIRpin = 49;    // (for PIR sensor)
int pirState = LOW; //PIR
int pirval = 0;     //PIR
int photocelled = 41;
int lastButtonBrig1State = LOW;
int lastButtonBrig2State = LOW;
int lastButtonEnterState = LOW; // the previous reading from the Enter input pin
int lastButtonEscState = LOW;   // the previous reading from the Esc input pin
int lastButtonLeftState = LOW;  // the previous reading from the Left input pin
int lastButtonRightState = LOW; // the previous reading from the Right input pin
int ledalarm = 39;              // alarm led
int ledalarmState = LOW;
long lastBrig1DebounceTime = 0;
long lastBrig2DebounceTime = 0;
long lastEnterDebounceTime = 0; // the last time the output pin was toggled
long lastEscDebounceTime = 0;   // the last time the output pin was toggled
long lastLeftDebounceTime = 0;  // the last time the output pin was toggled
long lastRightDebounceTime = 0; // the last time the output pin was toggled
long interval = 500;
long previousMillis = 0;
long debounceDelay = 500; // the debounce time
byte newChardown[8] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B10101,
    B01110,
    B00100,
    B00000};
byte newCharup[8] = { // arrow up
    B00100,
    B01110,
    B10101,
    B00100,
    B00100,
    B00100,
    B00100,
    B00000};
byte newCharright[8] = { // arrow right
    B00000,
    B00100,
    B00010,
    B11111,
    B00010,
    B00100,
    B00000,
    B00000};
byte newCharleft[8] = { // arrow left
    B00000,
    B00100,
    B01000,
    B11111,
    B01000,
    B00100,
    B00000,
    B00000};
LiquidCrystal lcd(22, 23, 24, 25, 26, 27, 28);
DHT dht(DHTPIN, DHT22);
IRrecv irrecv(RECV_PIN);
decode_results results;
//Menu variables
MenuBackend menu = MenuBackend(menuUsed, menuChanged);
//initialize menuitems
MenuItem menu1Item1 = MenuItem("Item1");
MenuItem menuItem1SubItem1 = MenuItem("Item1SubItem1");
MenuItem menuItem1SubItem2 = MenuItem("Item1SubItem2");
MenuItem menuItem1SubItem3 = MenuItem("Item1SubItem3");
MenuItem menuItem1SubItem4 = MenuItem("Item1SubItem4");
MenuItem menuItem1SubItem5 = MenuItem("Item1SubItem5");
MenuItem menu1Item2 = MenuItem("Item2");
MenuItem menuItem2SubItem1 = MenuItem("Item2SubItem1");
MenuItem menuItem2SubItem2 = MenuItem("Item2SubItem2");
MenuItem menuItem2SubItem3 = MenuItem("Item2SubItem3");
MenuItem menu1Item3 = MenuItem("Item3");
MenuItem menuItem3SubItem1 = MenuItem("Item3SubItem1");
MenuItem menuItem3SubItem2 = MenuItem("Item3SubItem2");
MenuItem menuItem3SubItem3 = MenuItem("Item3SubItem3");
MenuItem menu1Item4 = MenuItem("Item4");
MenuItem menuItem4SubItem1 = MenuItem("Item4SubItem1");
MenuItem menuItem4SubItem2 = MenuItem("Item4SubItem2");
MenuItem menuItem4SubItem3 = MenuItem("Item4SubItem3");
MenuItem menu1Item5 = MenuItem("Item5");
MenuItem menuItem5SubItem1 = MenuItem("Item5SubItem1");
MenuItem menuItem5SubItem2 = MenuItem("Item5SubItem2");
MenuItem menuItem5SubItem3 = MenuItem("Item5SubItem3");
MenuItem menu1Item6 = MenuItem("Item6");
MenuItem menuItem6SubItem1 = MenuItem("Item6SubItem1");
MenuItem menuItem6SubItem2 = MenuItem("Item6SubItem2");
MenuItem menu1Item7 = MenuItem("Item7");
MenuItem menuItem7SubItem1 = MenuItem("Item7SubItem1");
MenuItem menuItem7SubItem2 = MenuItem("Item7SubItem2");
MenuItem menu1Item8 = MenuItem("Item8");
MenuItem menuItem8SubItem1 = MenuItem("Item8SubItem1");
MenuItem menuItem8SubItem2 = MenuItem("Item8SubItem2");

void setup()
{
    lcd.createChar(1, newChardown);
    lcd.createChar(2, newCharup);
    lcd.createChar(3, newCharleft);
    lcd.createChar(4, newCharright);
    pinMode(floodSensors, INPUT);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(buttonPin, INPUT);
    pinMode(ledPower, OUTPUT); //dust sensor
    pinMode(buttonPinstop1, INPUT);
    pinMode(buttonPinstop2, INPUT);
    irrecv.enableIRIn();
    motor.setSpeed(vel);
    analogWrite(led1, brightness1); // LED PWM's at brightness value
    analogWrite(led2, brightness2);
    analogWrite(led3, brightness3);
    analogWrite(led4, brightness4);
    pinMode(pinSpeaker, OUTPUT);
    pinMode(ledalarm, OUTPUT);
    pinMode(photocelled, OUTPUT);
    pinMode(buttonPinLeft, INPUT);
    pinMode(buttonPinRight, INPUT);
    pinMode(buttonPinEnter, INPUT);
    pinMode(buttonPinEsc, INPUT);
    pinMode(PIRpin, INPUT);
    pinMode(buttonPinBrig1, INPUT);
    pinMode(buttonPinBrig2, INPUT);
    myservo.attach(10);
    myservo.write(175);
    lcd.begin(16, 2);
    //configure menu
    menu.getRoot().add(menu1Item1);
    menu1Item1.addRight(menu1Item2).addRight(menu1Item3).addRight(menu1Item4).addRight(menu1Item5).addRight(menu1Item6).addRight(menu1Item7).addRight(menu1Item8);
    menu1Item1.add(menuItem1SubItem1).addRight(menuItem1SubItem2).addRight(menuItem1SubItem3).addRight(menuItem1SubItem4).addRight(menuItem1SubItem5);
    menu1Item2.add(menuItem2SubItem1).addRight(menuItem2SubItem2).addRight(menuItem2SubItem3);
    menu1Item3.add(menuItem3SubItem1).addRight(menuItem3SubItem2).addRight(menuItem3SubItem3);
    menu1Item4.add(menuItem4SubItem1).addRight(menuItem4SubItem2).addRight(menuItem4SubItem3);
    menu1Item5.add(menuItem5SubItem1).addRight(menuItem5SubItem2).addRight(menuItem5SubItem3);
    menu1Item6.add(menuItem6SubItem1).addRight(menuItem6SubItem2);
    menu1Item7.add(menuItem7SubItem1).addRight(menuItem7SubItem2);
    menu1Item8.add(menuItem8SubItem1).addRight(menuItem8SubItem2);
    menu.toRoot();
}

void ledCLEAR()
{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
}

/// M O D E S ///
void lednext1()
{
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        // When '+' volume button pressed
        if (results.value == 0xFD807F && brightness1 < 240)
        {                                   // if '+' volume button pressed
            brightness1 = brightness1 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness1:");
            lcd.setCursor(7, 1);
            lcd.print(brightness1);
        }
        // When '-' volume button pressed
        if (results.value == 0xFD906F && brightness1 > 0)
        {                                   // if '-' volume button pressed and brightness isn't less than 0
            brightness1 = brightness1 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness1:");
            lcd.setCursor(7, 1);
            lcd.print(brightness1);
        }
    }
}

void lednext2()
{
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        // When '+' volume button pressed
        if (results.value == 0xFD807F && brightness2 < 240)
        {                                   // if '+' volume button pressed
            brightness2 = brightness2 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness2:");
            lcd.setCursor(7, 1);
            lcd.print(brightness2);
        }
        // When '-' volume button pressed
        if (results.value == 0xFD906F && brightness2 > 0)
        {                                   // if '-' volume button pressed and brightness isn't less than 0
            brightness2 = brightness2 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness2:");
            lcd.setCursor(7, 1);
            lcd.print(brightness2);
        }
    }
}

void lednext3()
{
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        // When '+' volume button pressed
        if (results.value == 0xFD807F && brightness3 < 240)
        {                                   // if '+' volume button pressed
            brightness3 = brightness3 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness3:");
            lcd.setCursor(7, 1);
            lcd.print(brightness3);
        }
        // When '-' volume button pressed
        if (results.value == 0xFD906F && brightness3 > 0)
        {                                   // if '-' volume button pressed and brightness isn't less than 0
            brightness3 = brightness3 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness3:");
            lcd.setCursor(7, 1);
            lcd.print(brightness3);
        }
    }
}

void lednext4()
{
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        // When '+' volume button pressed
        if (results.value == 0xFD807F && brightness4 < 240)
        {                                   // if '+' volume button pressed
            brightness4 = brightness4 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness4:");
            lcd.setCursor(7, 1);
            lcd.print(brightness4);
        }
        // When '-' volume button pressed
        if (results.value == 0xFD906F && brightness4 > 0)
        {                                   // if '-' volume button pressed and brightness isn't less than 0
            brightness4 = brightness4 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Brightness4:");
            lcd.setCursor(7, 1);
            lcd.print(brightness4);
        }
    }
}

void nexttemp()
{
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        if (results.value == 0xFD00FF)
        {
            lcd.clear();
            menu.toRoot();
        }
        // When '+' volume button pressed
        if (results.value == 0xFD807F && temp < 32)
        {                    // if '+' volume button pressed
            temp = temp + 1; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("temp reg:");
            lcd.setCursor(1, 1);
            lcd.print("temp:");
            lcd.setCursor(7, 1);
            lcd.print(t);
            lcd.setCursor(13, 1);
            lcd.print((char)223);
            lcd.print("C");
            delay(500);
            lcd.setCursor(10, 0);
            lcd.print(temp);
            lcd.setCursor(13, 0);
            lcd.print((char)223);
            lcd.print("C");
        }
        // When '-' volume button pressed
        if (results.value == 0xFD906F && temp > 20)
        {                    // if '-' volume button pressed and brightness isn't less than 0
            temp = temp - 1; // subtract -20 from brightness val
            lcd.clear();
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("temp reg:");
            lcd.setCursor(1, 1);
            lcd.print("temp:");
            lcd.setCursor(7, 1);
            lcd.print(t);
            lcd.setCursor(13, 1);
            lcd.print((char)223);
            lcd.print("C");
            delay(500);
            lcd.setCursor(10, 0);
            lcd.print(temp);
            lcd.setCursor(13, 0);
            lcd.print((char)223);
            lcd.print("C");
        }
        // When '+' volume button pressed
        if (results.value == 0xFD50AF && vel < 255)
        {                   // if '+' volume button pressed
            vel = vel + 15; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Speed increased");
            lcd.setCursor(4, 1);
            lcd.print("to: ");
            lcd.print(vel);
        }
        // When '-' volume button pressed
        if (results.value == 0xFD10EF && vel > 0)
        {                   // if '-' volume button pressed and brightness isn't less than 0
            vel = vel - 15; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Speed decreased");
            lcd.setCursor(4, 1);
            lcd.print("to: ");
            lcd.print(vel);
        }
        if (t > temp)
        {
            motor.setSpeed(vel);
            motor.run(FORWARD);
        }
        if (t <= temp)
        {
            motor.setSpeed(0);
            motor.run(RELEASE);
        }
    }
}

void nextdoor()
{
    sensorValue1 = 0;
    sensorValue2 = 0;
    float t = dht.readTemperature();
    if (irrecv.decode(&results))
    {
        if (results.value == 0xFD00FF)
        {
            lcd.clear();
            menu.toRoot();
        }
        // When '+' volume button pressed
        if (results.value == 0xFD50AF)
        { // if '+' volume button pressed
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print("open door");
            delay(1000);
            lcd.clear();
            menu.toRoot();
            for (pos = 180; pos >= 45; pos -= 10)
            {
                myservo.write(pos); // tell servo to go to position in variable 'pos'
                delay(20);
            }
        }
        // When '-' volume button pressed
        if (results.value == 0xFD10EF)
        { // if '-' volume button pressed and brightness isn't less than 0
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("closed door");
            delay(1000);
            lcd.clear();
            menu.toRoot();
            for (pos = 45; pos < 180; pos += 3)
            {
                myservo.write(pos); // tell servo to go to position in variable 'pos'
                delay(20);
            }
        }
    }
}

void nextwindow()
{
    if (irrecv.decode(&results))
    {
        if (results.value == 0xFD00FF)
        {
            lcd.clear();
            menu.toRoot();
        }
        // When '+' volume button pressed
        if (results.value == 0xFD50AF)
        { // if '+' volume button pressed
            lcd.clear();
            lcd.setCursor(3, 0);
            lcd.print("Shutters (up)");
            delay(1000);
            lcd.clear();
            menu.toRoot();
            centreButtonState9 = HIGH;
            centreButtonState11 = LOW;
        }
        if (results.value == 0xFDA05F)
        { // if '-' volume button pressed and brightness isn't less than 0
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("stop mode");
            delay(1000);
            lcd.clear();
            menu.toRoot();
            centreButtonState11 = HIGH;
        }
        // When '-' volume button pressed
        if (results.value == 0xFD10EF)
        { // if '-' volume button pressed and brightness isn't less than 0
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("Shutters (down)");
            delay(1000);
            lcd.clear();
            menu.toRoot();
            centreButtonState10 = HIGH;
            centreButtonState11 = LOW;
        }
    }
}

void nextclapclapled()
{
    int sensorValue = analogRead(0);
    if (sensorValue > CLAP_THRESHOLD)
    {
        unsigned long vNow = 0;
        vNow = millis();
        unsigned long vGap = vNow - mLastClap;
        delay(100);
        if (
            mLastClap != 0 && mLastClap < vNow && vGap >= CLAP_GAP_MIN && vGap <= CLAP_GAP_MAX)
        {
            //switch relay status
            led3Status = !led3Status;
            if (led3Status == HIGH)
            {
                centreButtonState3 = HIGH;
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("led3 on!");
                delay(700);
                menu.toRoot();
            }
            if (led3Status == LOW)
            {
                centreButtonState3 = LOW;
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("led3 off!");
                delay(700);
                menu.toRoot();
            }
            mLastClap = 0;
        }
        else
        {
            //store last time
            mLastClap = vNow;
        }
    }
}

void loop()
{
    pirval = digitalRead(PIRpin);
    photocellReading = analogRead(photocellPin);
    if (photocellReading < 70 && pirval == HIGH)
    {
        digitalWrite(photocelled, HIGH);
    }
    else if ((photocellReading < 800) && (pirval == HIGH || pirval == LOW))
    {
        digitalWrite(photocelled, LOW);
    }
    floodSensorState = digitalRead(floodSensors);
    if (floodSensorState == HIGH)
    {
        digitalWrite(ledalarm, LOW);
    }
    else
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            previousMillis = currentMillis;
            if (ledalarmState == LOW)
                ledalarmState = HIGH;
            else
                ledalarmState = LOW;
            digitalWrite(ledalarm, ledalarmState);
        }
        buzz(600, 2920);
        delay(600);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Activated");
        lcd.setCursor(10, 0);
        lcd.print("alarm3");
        lcd.setCursor(0, 1);
        lcd.print("(flood)!");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        delay(500);
    }
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);
    // determine alarm status
    if (sensorValue2 >= 760)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            // save the last time you blinked the LED
            previousMillis = currentMillis;
            // if the LED is off turn it on and vice-versa:
            if (ledalarmState == LOW)
                ledalarmState = HIGH;
            else
                ledalarmState = LOW;
            // set the LED with the ledState of the variable:
            digitalWrite(ledalarm, ledalarmState);
        }
        buzz(600, 2920);
        delay(600);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Activated");
        lcd.setCursor(10, 0);
        lcd.print("alarm2");
        lcd.setCursor(0, 1);
        lcd.print("(MQ-7)!");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        delay(500);
    }
    else
    {
        digitalWrite(ledalarm, LOW);
    }
    if (sensorValue1 >= 760)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            // save the last time you blinked the LED
            previousMillis = currentMillis;
            // if the LED is off turn it on and vice-versa:
            if (ledalarmState == LOW)
                ledalarmState = HIGH;
            else
                ledalarmState = LOW;
            // set the LED with the ledState of the variable:
            digitalWrite(ledalarm, ledalarmState);
        }
        buzz(600, 2920);
        delay(600);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Activated");
        lcd.setCursor(10, 0);
        lcd.print("alarm1");
        lcd.setCursor(0, 1);
        lcd.print("(MQ-6)!");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        delay(500);
    }
    else
    {
        digitalWrite(ledalarm, LOW);
    }
    if (irrecv.decode(&results))
    { // if an IR signal is obtained from IR receiver
        if (results.value == 0xFD30CF)
        {
            dht.begin();
            float h = dht.readHumidity();
            float t = dht.readTemperature();
            // check if returns are valid, if they are NaN (not a number) then something went wrong!
            if (isnan(t) || isnan(h))
            {
                lcd.setCursor(0, 0);
                lcd.print("Failed to read from DHT");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Humidity:");
                lcd.setCursor(4, 1);
                lcd.print(h);
                lcd.print(" %");
                delay(2000);
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Temperature:");
                lcd.setCursor(4, 1);
                lcd.print(t);
                lcd.setCursor(10, 1);
                lcd.print((char)223);
                lcd.print("C");
                delay(2000);
                lcd.clear();
                menu.toRoot();
            }
        }

        // When Centre button is pressed
        if (results.value == 0xFD08F7)
        {
            brightness1 = 100;
            if (centreButtonState1 == LOW)
            {                              // if previously LOW
                centreButtonState1 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(4, 0);
                lcd.print("Led1 on!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState1 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Led1 off!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD8877)
        {
            brightness2 = 100;
            if (centreButtonState2 == LOW)
            {                              // if previously LOW
                centreButtonState2 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(4, 0);
                lcd.print("Led2 on!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState2 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Led2 off!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD48B7)
        {
            brightness3 = 100;
            if (centreButtonState3 == LOW)
            {                              // if previously LOW
                centreButtonState3 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(4, 0);
                lcd.print("Led3 on!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState3 = LOW; // now make LOW
                led3Status = LOW;
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Led3 off!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD28D7)
        {
            brightness4 = 100;
            if (centreButtonState4 == LOW)
            {                              // if previously LOW
                centreButtonState4 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(4, 0);
                lcd.print("Led4 on!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState4 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(3, 0);
                lcd.print("Led4 off!");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFDA857)
        { //button 5
            temp = 24;
            vel = 210;
            if (centreButtonState5 == LOW)
            {                              // if previously LOW
                centreButtonState5 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Active temp");
                lcd.setCursor(3, 1);
                lcd.print("and speed");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState5 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Standby temp");
                lcd.setCursor(3, 1);
                lcd.print("and speed");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD6897)
        {
            if (centreButtonState6 == LOW)
            {                              // if previously LOW
                centreButtonState6 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Active door");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState6 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Standby door");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD18E7)
        {
            if (centreButtonState7 == LOW)
            {                              // if previously LOW
                centreButtonState7 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Active Shutters");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState7 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Standby Shutters");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        if (results.value == 0xFD9867)
        { //button 8
            if (centreButtonState8 == LOW)
            {                              // if previously LOW
                centreButtonState8 = HIGH; // now make HIGH
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Active clap");
                lcd.setCursor(4, 1);
                lcd.print("clap led");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
            else
            {                             // if already HIGH
                centreButtonState8 = LOW; // now make LOW
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Standby clap");
                lcd.setCursor(4, 1);
                lcd.print("clap led");
                delay(700);
                lcd.clear();
                menu.toRoot();
            }
        }
        // When previous '<<' button pressed
        if (results.value == 0xFD20DF)
        {
            if (mode > 1)
            {
                mode = mode - 1;
            }
            else
            {
                mode = 8;
            }
            lcd.clear();
            lcd.setCursor(6, 0);
            lcd.print("Mode");
            lcd.print(mode);
            if (mode == 1)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led1");
            }
            if (mode == 2)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led2");
            }
            if (mode == 3)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led3");
            }
            if (mode == 4)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led4");
            }
            if (mode == 5)
            {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Temperature");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 6)
            {
                lcd.clear();
                lcd.setCursor(6, 0);
                lcd.print("Door");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 7)
            {
                lcd.clear();
                lcd.setCursor(5, 0);
                lcd.print("Shutters");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 8)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("clap clap led");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
        }
        // When next '>>' button pressed
        if (results.value == 0xFD609F)
        {
            if (mode < 8)
            {
                mode = mode + 1;
            }
            else
            {
                mode = 1;
            }
            lcd.clear();
            lcd.setCursor(6, 0);
            lcd.print("Mode");
            lcd.print(mode);
            if (mode == 1)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led1");
            }
            if (mode == 2)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led2");
            }
            if (mode == 3)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led3");
            }
            if (mode == 4)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("Brightnes led4");
            }
            if (mode == 5)
            {
                lcd.clear();
                lcd.setCursor(2, 0);
                lcd.print("Temperature");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 6)
            {
                lcd.clear();
                lcd.setCursor(5, 0);
                lcd.print("Door");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 7)
            {
                lcd.clear();
                lcd.setCursor(5, 0);
                lcd.print("Shutters");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
            if (mode == 8)
            {
                lcd.clear();
                lcd.setCursor(1, 0);
                lcd.print("clap clap led");
                lcd.setCursor(4, 1);
                lcd.print("control");
            }
        }
        if (results.value == 0xFD00FF)
        {
            lcd.clear();
            menu.toRoot();
        }
        irrecv.resume(); // Receive the next value
    }
    if (centreButtonState1 == HIGH)
    {
        analogWrite(led1, brightness1);
    }
    else
    {
        analogWrite(led1, 0);
    }
    if (centreButtonState2 == HIGH)
    {
        analogWrite(led2, brightness2);
    }
    else
    {
        analogWrite(led2, 0);
    }
    if (centreButtonState3 == HIGH)
    {
        led3Status = HIGH;
        analogWrite(led3, brightness3);
    }
    else
    {
        led3Status = LOW;
        analogWrite(led3, 0);
    }
    if (centreButtonState4 == HIGH)
    {
        analogWrite(led4, brightness4);
    }
    else
    {
        analogWrite(led4, 0);
    }
    if (centreButtonState9 == HIGH || (centreButtonState12 == HIGH && centreButtonState9 == HIGH))
    {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
    }

    buttonStatestop1 = digitalRead(buttonPinstop1);
    buttonStatestop2 = digitalRead(buttonPinstop2);

    if (centreButtonState9 == HIGH && buttonStatestop1 == HIGH)
    {
        centreButtonState9 = LOW;
    }
    if (centreButtonState10 == HIGH && buttonStatestop2 == HIGH)
    {
        centreButtonState10 = LOW;
    }
    if (centreButtonState11 == HIGH && buttonStatestop2 == HIGH)
    {
        centreButtonState10 = LOW;
    }
    if (centreButtonState10 == HIGH || (centreButtonState12 == HIGH && centreButtonState10 == HIGH))
    {
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, HIGH);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, LOW);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, HIGH);
        delay(motorDelay);
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        digitalWrite(motorPin3, HIGH);
        digitalWrite(motorPin4, LOW);
        delay(motorDelay);
    }
    if (centreButtonState11 == HIGH)
    {
        centreButtonState12 == HIGH;
        centreButtonState9 = LOW;
        centreButtonState10 = LOW;
    }
    if (centreButtonState13 == HIGH)
    {
        delay(500);
        digitalWrite(ledPower, LOW); // power on the LED
        delayMicroseconds(delayTime);
        dustVal = analogRead(dustPin); // read the dust value via
        delayMicroseconds(delayTime2);
        digitalWrite(ledPower, HIGH); // turn the LED off
        delayMicroseconds(offTime);
        delay(300);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("dust:");
        lcd.write(4);
        lcd.setCursor(6, 0);
        lcd.print(dustVal);
        delay(400);
        centreButtonState13 = HIGH;
    }
    switch (mode)
    { // Mode Management
    case 1:
        if (centreButtonState1 == HIGH)
        {
            lednext1();
        }
        break;
    case 2:
        if (centreButtonState2 == HIGH)
        {
            lednext2();
        }
        break;
    case 3:
        if (centreButtonState3 == HIGH)
        {
            lednext3();
        }
        break;
    case 4:
        if (centreButtonState4 == HIGH)
        {
            lednext4();
        }
        break;
    case 5:
        if (centreButtonState5 == HIGH)
        {
            nexttemp();
        }
        break;
    case 6:
        if (centreButtonState6 == HIGH)
        {
            nextdoor();
        }
        break;
    case 7:
        if (centreButtonState7 == HIGH)
        {
            nextwindow();
        }
        break;
    case 8:
        if (centreButtonState8 == HIGH)
        {
            nextclapclapled();
        }
        break;
    }
    readButtons();   //I splitted button reading and navigation in two procedures because
    navigateMenus(); //in some situations I want to use the button for other purpose (eg. to change some settings)
} //loop()...
void menuChanged(MenuChangeEvent changed)
{
    MenuItem newMenuItem = changed.to; //get the destination menu
    lcd.setCursor(3, 0);               //set the start position for lcd printing to the second row
    if (newMenuItem.getName() == menu.getRoot())
    {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Menu of Smart");
        lcd.setCursor(1, 1);
        lcd.print("Home");
        lcd.setCursor(7, 1);
        lcd.print("[enter]");
        if (lastButtonEnterState || lastButtonEscState == HIGH)
        {
            buzz(50, 650);
        }
    }
    else if (newMenuItem.getName() == "Item1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("1.TiH");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item1SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        dht.begin();
        float h = dht.readHumidity();
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("temp [");
        lcd.write(4);
        lcd.setCursor(11, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(50, 650);
            delay(55);
            centreButtonState5 = LOW;
            if (centreButtonState5 == LOW)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("[");
                lcd.write(4);
                lcd.setCursor(2, 0);
                lcd.print("]temp");
                lcd.setCursor(1, 1);
                lcd.setCursor(10, 0);
                lcd.print("[menu]");
                lcd.setCursor(1, 1);
                lcd.print("humid:");
                lcd.setCursor(8, 1);
                lcd.print(h);
                lcd.print(" %");
            }
        }
    }
    else if (newMenuItem.getName() == "Item1SubItem2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        dht.begin();
        float t = dht.readTemperature();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("]humid");
        lcd.setCursor(10, 0);
        lcd.print("reg[");
        lcd.write(4);
        lcd.setCursor(15, 0);
        lcd.print("]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
            centreButtonState5 = HIGH;
            if (centreButtonState5 == HIGH)
            {
                lcd.setCursor(1, 1);
                lcd.print("temp:");
                lcd.setCursor(7, 1);
                lcd.print(t);
                lcd.setCursor(12, 1);
                lcd.print((char)223);
                lcd.print("C");
                if (isnan(t))
                {
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print("Failed to read");
                    lcd.setCursor(4, 1);
                    lcd.print("from DHT");
                    delay(700);
                    lcd.clear();
                    menu.toRoot();
                }
            }
        }
    }
    else if (newMenuItem.getName() == "Item1SubItem3")
    {
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("vel reg [");
        lcd.write(4);
        lcd.setCursor(15, 0);
        lcd.print("]");
        lcd.setCursor(3, 1);
        lcd.print("temp reg [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(15, 1);
        lcd.print("]");
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && temp < 32)
        {
            temp = temp + 1; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 0);
            lcd.print("]");
            lcd.setCursor(4, 1);
            lcd.print("t reg:");
            lcd.setCursor(5, 0);
            lcd.print("t:");
            delay(500);
            float t = dht.readTemperature();
            lcd.setCursor(11, 1);
            lcd.print(temp);
            lcd.setCursor(14, 1);
            lcd.print((char)223);
            lcd.print("C");
            lcd.setCursor(8, 0);
            lcd.print(t);
            lcd.setCursor(14, 0);
            lcd.print((char)223);
            lcd.print("C");
            if (t > temp)
            {
                motor.setSpeed(vel);
                motor.run(FORWARD);
            }
            if (t <= temp)
            {
                motor.setSpeed(0);
                motor.run(RELEASE);
            }
        }
        if (lastButtonBrig2State == HIGH && temp > 20)
        {
            temp = temp - 1;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 0);
            lcd.print("]");
            lcd.setCursor(4, 1);
            lcd.print("t reg:");
            lcd.setCursor(5, 0);
            lcd.print("t:");
            delay(500);
            float t = dht.readTemperature();
            lcd.setCursor(11, 1);
            lcd.print(temp);
            lcd.setCursor(14, 1);
            lcd.print((char)223);
            lcd.print("C");
            lcd.setCursor(8, 0);
            lcd.print(t);
            lcd.setCursor(14, 0);
            lcd.print((char)223);
            lcd.print("C");
            if (t > temp)
            {
                motor.setSpeed(vel);
                motor.run(FORWARD);
            }
            if (t <= temp)
            {
                motor.setSpeed(0);
                motor.run(RELEASE);
            }
        }
    }
    else if (newMenuItem.getName() == "Item1SubItem5")
    {
        float t = dht.readTemperature();
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("speed");
        lcd.setCursor(4, 1);
        lcd.print("control [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(15, 1);
        lcd.print("]");
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && t > temp)
        {
            if (vel < 255)
            {
                vel = vel + 15;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("[");
                lcd.write(3);
                lcd.setCursor(2, 0);
                lcd.print("]");
                lcd.setCursor(5, 0);
                lcd.print("speed reg:");
                delay(500);
                lcd.setCursor(6, 1);
                lcd.print(vel);
                if (t > temp)
                {
                    motor.setSpeed(vel);
                }
                if (t <= temp)
                {
                    motor.setSpeed(0);
                    motor.run(RELEASE);
                }
            }
        }
        if (lastButtonBrig2State == HIGH && t > temp)
        {
            if (vel > 0)
            {
                vel = vel - 15;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("[");
                lcd.write(3);
                lcd.setCursor(2, 0);
                lcd.print("]");
                lcd.setCursor(5, 0);
                lcd.print("speed reg:");
                delay(500);
                lcd.setCursor(6, 1);
                lcd.print(vel);
                if (t > temp)
                {
                    motor.setSpeed(vel);
                }
                if (t <= temp)
                {
                    motor.setSpeed(0);
                    motor.run(RELEASE);
                }
            }
        }
    }
    else if (newMenuItem.getName() == "Item2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(50, 650);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("2.Led1");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item2SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("on [");
        lcd.write(4);
        lcd.setCursor(10, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(50, 650);
            centreButtonState1 = LOW;
            if (centreButtonState1 == LOW)
            {
                analogWrite(led1, 0);
            }
        }
    }
    else if (newMenuItem.getName() == "Item2SubItem2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("] off ");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(4);
        lcd.setCursor(2, 1);
        lcd.print("] Brightness");
        lcd.setCursor(10, 0);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
            brightness1 = 100;
            centreButtonState1 = HIGH;
            if (centreButtonState1 == HIGH)
            {
                analogWrite(led1, brightness1);
            }
        }
    }
    else if (newMenuItem.getName() == "Item2SubItem3")
    {
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Brightness [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(14, 0);
        lcd.print("]");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 1);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && brightness1 < 240)
        {
            brightness1 = brightness1 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness1);
            delay(305);
        }
        if (lastButtonBrig2State == HIGH && brightness1 > 0)
        {
            brightness1 = brightness1 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness1);
            delay(305);
        }
    }
    else if (newMenuItem.getName() == "Item3")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("3.Led2");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item3SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("on [");
        lcd.write(4);
        lcd.setCursor(10, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            centreButtonState2 = LOW;
            if (centreButtonState2 == LOW)
            {
                analogWrite(led2, 0);
            }
        }
    }
    else if (newMenuItem.getName() == "Item3SubItem2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("] off ");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(4);
        lcd.setCursor(2, 1);
        lcd.print("] Brightness");
        lcd.setCursor(10, 0);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            brightness1 = 100;
            centreButtonState2 = HIGH;
            if (centreButtonState2 == HIGH)
            {
                analogWrite(led2, brightness2);
            }
        }
    }
    else if (newMenuItem.getName() == "Item3SubItem3")
    {
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Brightness [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(14, 0);
        lcd.print("]");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 1);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && brightness2 < 240)
        {
            brightness2 = brightness2 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness2);
            delay(305);
        }
        if (lastButtonBrig2State == HIGH && brightness2 > 0)
        {
            brightness2 = brightness2 - 20;
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness2);
            delay(305);
        }
    }
    else if (newMenuItem.getName() == "Item4")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("4.Led3");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item4SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("on [");
        lcd.write(4);
        lcd.setCursor(10, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            centreButtonState3 = LOW;
            if (centreButtonState3 == LOW)
            {
                analogWrite(led3, 0);
            }
        }
    }
    else if (newMenuItem.getName() == "Item4SubItem2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("] off ");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(4);
        lcd.setCursor(2, 1);
        lcd.print("] Brightness");
        lcd.setCursor(10, 0);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            brightness3 = 100;
            centreButtonState3 = HIGH;
            if (centreButtonState3 == HIGH)
            {
                analogWrite(led3, brightness3);
            }
        }
    }
    else if (newMenuItem.getName() == "Item4SubItem3")
    {
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Brightness [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(14, 0);
        lcd.print("]");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 1);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && brightness3 < 240)
        {
            brightness3 = brightness3 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness3);
            delay(305);
        }
        if (lastButtonBrig2State == HIGH && brightness3 > 0)
        {
            brightness3 = brightness3 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness3);
            delay(305);
        }
    }
    else if (newMenuItem.getName() == "Item5")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(50, 650);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("5.Led4");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item5SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
        }
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("on [");
        lcd.write(4);
        lcd.setCursor(10, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(50, 650);
            centreButtonState4 = LOW;
            if (centreButtonState4 == LOW)
            {
                analogWrite(led4, 0);
            }
        }
    }
    else if (newMenuItem.getName() == "Item5SubItem2")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(50, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("] off ");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(4);
        lcd.setCursor(2, 1);
        lcd.print("] Brightness");
        lcd.setCursor(10, 0);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(50, 650);
            delay(55);
            brightness4 = 100;
            centreButtonState4 = HIGH;
            if (centreButtonState4 == HIGH)
            {
                analogWrite(led4, brightness4);
            }
        }
    }
    else if (newMenuItem.getName() == "Item5SubItem3")
    {
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Brightness [");
        lcd.write(2);
        lcd.write(1);
        lcd.setCursor(14, 0);
        lcd.print("]");
        lcd.setCursor(10, 1);
        lcd.print("[menu]");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 1);
        lcd.print("]");
        if (lastButtonBrig1State == HIGH && brightness4 < 240)
        {
            brightness4 = brightness4 + 20; // add +20 to brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness4);
            delay(305);
        }
        if (lastButtonBrig2State == HIGH && brightness4 > 0)
        {
            brightness4 = brightness4 - 20; // subtract -20 from brightness val
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("[");
            lcd.write(3);
            lcd.setCursor(2, 1);
            lcd.print("]");
            lcd.setCursor(0, 0);
            lcd.print("Brightness:");
            delay(500);
            lcd.setCursor(12, 0);
            lcd.print(brightness4);
            delay(305);
        }
    }
    else if (newMenuItem.getName() == "Item6")
    {
        if (lastButtonEnterState || lastButtonEscState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("6.Door");
        lcd.setCursor(8, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item6SubItem1")
    {
        if (lastButtonEscState || lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("open [");
        lcd.write(4);
        lcd.setCursor(11, 0);
        lcd.print("]");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            sensorValue1 = 0;
            sensorValue2 = 0;
            buzz(55, 650);
            delay(55);
            for (pos = 45; pos < 180; pos += 3)
            {
                myservo.write(pos);
                delay(20);
            }
        }
    }
    else if (newMenuItem.getName() == "Item6SubItem2")
    {
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(5, 0);
        lcd.print("] closed ");
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            sensorValue1 = 0;
            sensorValue2 = 0;
            buzz(55, 650);
            delay(55);
            for (pos = 180; pos >= 45; pos -= 10)
            {
                myservo.write(pos); // tell servo to go to position in variable 'pos'
                delay(20);
            }
        }
    }
    else if (newMenuItem.getName() == "Item7")
    {
        if (lastButtonEnterState || lastButtonEscState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("7.Shutters");
        lcd.setCursor(9, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(15, 1);
        lcd.write(4);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item7SubItem1")
    {
        if (lastButtonEnterState || lastButtonEscState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("up [");
        lcd.write(4);
        lcd.setCursor(6, 0);
        lcd.print("]");
        lcd.setCursor(1, 1);
        lcd.print("stop [");
        lcd.write(2);
        lcd.setCursor(8, 1);
        lcd.print("]");
        lcd.setCursor(9, 0);
        lcd.print("[menu]");
        if (lastButtonRightState || lastButtonLeftState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            centreButtonState10 = HIGH;
            centreButtonState11 = LOW;
        }
        if (lastButtonBrig1State == HIGH)
        {
            centreButtonState11 = HIGH;
        }
    }
    else if (newMenuItem.getName() == "Item7SubItem2")
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[");
        lcd.write(3);
        lcd.setCursor(2, 0);
        lcd.print("] down");
        lcd.setCursor(0, 1);
        lcd.print("[");
        lcd.write(1);
        lcd.setCursor(2, 1);
        lcd.print("] stop");
        lcd.setCursor(10, 0);
        lcd.print("[menu]");
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
            centreButtonState9 = HIGH;
            centreButtonState11 = LOW;
        }
        if (lastButtonBrig2State == HIGH)
        {
            centreButtonState11 = HIGH;
        }
    }
    else if (newMenuItem.getName() == "Item8")
    {
        if (lastButtonEnterState || lastButtonEscState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        if (lastButtonLeftState || lastButtonRightState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("8.Dust");
        lcd.setCursor(9, 0);
        lcd.print("[enter]");
        lcd.setCursor(0, 1);
        lcd.write(3);
        lcd.setCursor(5, 1);
        lcd.print("[menu]");
    }
    else if (newMenuItem.getName() == "Item8SubItem1")
    {
        if (lastButtonEnterState == HIGH)
        {
            buzz(55, 650);
            delay(55);
        }
        centreButtonState13 = HIGH;
    }
    if (lastButtonEscState == HIGH)
    {
        centreButtonState13 = LOW;
    }
}

void menuUsed(MenuUseEvent used) {}

void buzz(long duration, int freq)
{
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration)
    {
        digitalWrite(pinSpeaker, HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

void readButtons()
{ //read buttons status
    int reading;
    int buttonEnterState = LOW;
    int buttonEscState = LOW;
    int buttonLeftState = LOW;
    int buttonRightState = LOW;
    int buttonBrig1State = LOW;
    int buttonBrig2State = LOW;
    //Enter button
    reading = digitalRead(buttonPinEnter);
    if (reading != lastButtonEnterState)
    {
        lastEnterDebounceTime = millis();
    }
    if ((millis() - lastEnterDebounceTime) > debounceDelay)
    {
        buttonEnterState = reading;
        lastEnterDebounceTime = millis();
    }
    lastButtonEnterState = reading;
    //Esc button
    reading = digitalRead(buttonPinEsc);
    if (reading != lastButtonEscState)
    {
        lastEscDebounceTime = millis();
    }
    if ((millis() - lastEscDebounceTime) > debounceDelay)
    {
        buttonEscState = reading;
        lastEscDebounceTime = millis();
    }
    lastButtonEscState = reading;
    //Down button
    reading = digitalRead(buttonPinRight);
    if (reading != lastButtonRightState)
    {
        // reset the debouncing timer
        lastRightDebounceTime = millis();
    }
    if ((millis() - lastRightDebounceTime) > debounceDelay)
    {
        buttonRightState = reading;
        lastRightDebounceTime = millis();
    }
    lastButtonRightState = reading;
    //Up button
    reading = digitalRead(buttonPinLeft);
    if (reading != lastButtonLeftState)
    {
        lastLeftDebounceTime = millis();
    }
    if ((millis() - lastLeftDebounceTime) > debounceDelay)
    {
        buttonLeftState = reading;
        lastLeftDebounceTime = millis();
        ;
    }
    lastButtonLeftState = reading;
    //Brig1 button
    reading = digitalRead(buttonPinBrig1);
    if (reading != lastButtonBrig1State)
    {
        // reset the debouncing timer
        lastBrig1DebounceTime = millis();
    }
    if ((millis() - lastBrig1DebounceTime) > debounceDelay)
    {
        buttonBrig1State = reading;
        lastBrig1DebounceTime = millis();
        ;
    }
    lastButtonBrig1State = reading;
    //Brig2 button
    reading = digitalRead(buttonPinBrig2);
    if (reading != lastButtonBrig2State)
    {
        lastBrig2DebounceTime = millis();
    }
    if ((millis() - lastBrig2DebounceTime) > debounceDelay)
    {
        buttonBrig2State = reading;
        lastBrig2DebounceTime = millis();
        ;
    }
    lastButtonBrig2State = reading;
    if (buttonEnterState == HIGH)
    {
        lastButtonPushed = buttonPinEnter;
    }
    else if (buttonEscState == HIGH)
    {
        lastButtonPushed = buttonPinEsc;
    }
    else if (buttonRightState == HIGH)
    {
        lastButtonPushed = buttonPinRight;
    }
    else if (buttonLeftState == HIGH)
    {
        lastButtonPushed = buttonPinLeft;
    }
    else if (buttonBrig1State == HIGH)
    {
        lastButtonPushed = buttonPinBrig1;
    }
    else if (buttonBrig2State == HIGH)
    {
        lastButtonPushed = buttonPinBrig2;
    }
    else
    {
        lastButtonPushed = 0;
    }
}
void navigateMenus()
{
    MenuItem currentMenu = menu.getCurrent();
    switch (lastButtonPushed)
    {
    case buttonPinEnter:
        if (!(currentMenu.moveDown()))
        {
            menu.use();
        }
        else
        {
            menu.moveDown();
        }
        break;
    case buttonPinEsc:
        menu.toRoot(); //back to main menu
        break;
    case buttonPinRight:
        menu.moveRight();
        break;
    case buttonPinLeft:
        menu.moveLeft();
        break;
    case buttonPinBrig1:
        menu.moveRight();
        menu.moveLeft();
        break;
    case buttonPinBrig2:
        menu.moveLeft();
        menu.moveRight();
        break;
    }
    lastButtonPushed = 0; //reset the lastButtonPushed variable
}
